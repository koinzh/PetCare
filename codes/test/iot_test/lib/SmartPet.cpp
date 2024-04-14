#include "SmartPet.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"
#include "aiot_mqtt_api.h"
#include "aiot_dm_api.h"

const char *product_key = "k0txi2jzZL9";
const char *device_name = "raspberry_4b";
const char *device_secret = "6e0f2762dba515a35eb098b138d90405";
const char *region_id = "cn-shanghai";

const char  *mqtt_host = "iot-06z00ecae6zqnin.mqtt.iothub.aliyuncs.com";
/* 
    原端口：1883/443，对应的证书(GlobalSign R1),于2028年1月过期，届时可能会导致设备不能建连。
    (推荐)新端口：8883，将搭载新证书，由阿里云物联网平台自签证书，于2053年7月过期。
*/
const uint16_t port = 8883;

/* 位于portfiles/aiot_port文件夹下的系统适配函数集合 */
extern aiot_sysdep_portfile_t g_aiot_sysdep_portfile;

/* 位于external/ali_ca_cert.c中的服务器证书 */
extern const char *ali_ca_cert;

static pthread_t g_mqtt_process_thread;
static pthread_t g_mqtt_recv_thread;
static uint8_t g_mqtt_process_thread_running = 0;
static uint8_t g_mqtt_recv_thread_running = 0;

int32_t demo_state_logcb(int32_t code, char *message)
{
    printf("%s", message);
    return 0;
}

/* MQTT事件回调函数, 当网络连接/重连/断开时被触发, 事件定义见core/aiot_mqtt_api.h */
void demo_mqtt_event_handler(void *handle, const aiot_mqtt_event_t *event, void *userdata)
{
    switch (event->type) {
        /* SDK因为用户调用了aiot_mqtt_connect()接口, 与mqtt服务器建立连接已成功 */
        case AIOT_MQTTEVT_CONNECT: {
            printf("AIOT_MQTTEVT_CONNECT\n");
        }
        break;

        /* SDK因为网络状况被动断连后, 自动发起重连已成功 */
        case AIOT_MQTTEVT_RECONNECT: {
            printf("AIOT_MQTTEVT_RECONNECT\n");
        }
        break;

        /* SDK因为网络的状况而被动断开了连接, network是底层读写失败, heartbeat是没有按预期得到服务端心跳应答 */
        case AIOT_MQTTEVT_DISCONNECT: {
            const char *cause = (event->data.disconnect == AIOT_MQTTDISCONNEVT_NETWORK_DISCONNECT) ? ("network disconnect") :
                          ("heartbeat disconnect");
            printf("AIOT_MQTTEVT_DISCONNECT: %s\n", cause);
        }
        break;

        default: {

        }
    }
}

static void demo_dm_recv_generic_reply(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_generic_reply msg_id = %d, code = %d, data = %.*s, message = %.*s\r\n",
           recv->data.generic_reply.msg_id,
           recv->data.generic_reply.code,
           recv->data.generic_reply.data_len,
           recv->data.generic_reply.data,
           recv->data.generic_reply.message_len,
           recv->data.generic_reply.message);
}

static void demo_dm_recv_property_set(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_property_set msg_id = %ld, params = %.*s\r\n",
           (unsigned long)recv->data.property_set.msg_id,
           recv->data.property_set.params_len,
           recv->data.property_set.params);

    /* TODO: 以下代码演示如何对来自云平台的属性设置指令进行应答, 用户可取消注释查看演示效果 */
    /*
    {
        aiot_dm_msg_t msg;

        memset(&msg, 0, sizeof(aiot_dm_msg_t));
        msg.type = AIOT_DMMSG_PROPERTY_SET_REPLY;
        msg.data.property_set_reply.msg_id = recv->data.property_set.msg_id;
        msg.data.property_set_reply.code = 200;
        msg.data.property_set_reply.data = "{}";
        int32_t res = aiot_dm_send(dm_handle, &msg);
        if (res < 0) {
            printf("aiot_dm_send failed\r\n");
        }
    }
    */
}

static void demo_dm_recv_async_service_invoke(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_async_service_invoke msg_id = %ld, service_id = %s, params = %.*s\r\n",
           (unsigned long)recv->data.async_service_invoke.msg_id,
           recv->data.async_service_invoke.service_id,
           recv->data.async_service_invoke.params_len,
           recv->data.async_service_invoke.params);

    /* TODO: 以下代码演示如何对来自云平台的异步服务调用进行应答, 用户可取消注释查看演示效果
        *
        * 注意: 如果用户在回调函数外进行应答, 需要自行保存msg_id, 因为回调函数入参在退出回调函数后将被SDK销毁, 不可以再访问到
        */

    /*
    {
        aiot_dm_msg_t msg;

        memset(&msg, 0, sizeof(aiot_dm_msg_t));
        msg.type = AIOT_DMMSG_ASYNC_SERVICE_REPLY;
        msg.data.async_service_reply.msg_id = recv->data.async_service_invoke.msg_id;
        msg.data.async_service_reply.code = 200;
        msg.data.async_service_reply.service_id = "ToggleLightSwitch";
        msg.data.async_service_reply.data = "{\"dataA\": 20}";
        int32_t res = aiot_dm_send(dm_handle, &msg);
        if (res < 0) {
            printf("aiot_dm_send failed\r\n");
        }
    }
    */
}

static void demo_dm_recv_sync_service_invoke(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_sync_service_invoke msg_id = %ld, rrpc_id = %s, service_id = %s, params = %.*s\r\n",
           (unsigned long)recv->data.sync_service_invoke.msg_id,
           recv->data.sync_service_invoke.rrpc_id,
           recv->data.sync_service_invoke.service_id,
           recv->data.sync_service_invoke.params_len,
           recv->data.sync_service_invoke.params);

    /* TODO: 以下代码演示如何对来自云平台的同步服务调用进行应答, 用户可取消注释查看演示效果
        *
        * 注意: 如果用户在回调函数外进行应答, 需要自行保存msg_id和rrpc_id字符串, 因为回调函数入参在退出回调函数后将被SDK销毁, 不可以再访问到
        */

    /*
    {
        aiot_dm_msg_t msg;

        memset(&msg, 0, sizeof(aiot_dm_msg_t));
        msg.type = AIOT_DMMSG_SYNC_SERVICE_REPLY;
        msg.data.sync_service_reply.rrpc_id = recv->data.sync_service_invoke.rrpc_id;
        msg.data.sync_service_reply.msg_id = recv->data.sync_service_invoke.msg_id;
        msg.data.sync_service_reply.code = 200;
        msg.data.sync_service_reply.service_id = "SetLightSwitchTimer";
        msg.data.sync_service_reply.data = "{}";
        int32_t res = aiot_dm_send(dm_handle, &msg);
        if (res < 0) {
            printf("aiot_dm_send failed\r\n");
        }
    }
    */
}

static void demo_dm_recv_raw_data(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_raw_data raw data len = %d\r\n", recv->data.raw_data.data_len);
    /* TODO: 以下代码演示如何发送二进制格式数据, 若使用需要有相应的数据透传脚本部署在云端 */
    /*
    {
        aiot_dm_msg_t msg;
        uint8_t raw_data[] = {0x01, 0x02};

        memset(&msg, 0, sizeof(aiot_dm_msg_t));
        msg.type = AIOT_DMMSG_RAW_DATA;
        msg.data.raw_data.data = raw_data;
        msg.data.raw_data.data_len = sizeof(raw_data);
        aiot_dm_send(dm_handle, &msg);
    }
    */
}

static void demo_dm_recv_raw_sync_service_invoke(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_raw_sync_service_invoke raw sync service rrpc_id = %s, data_len = %d\r\n",
           recv->data.raw_service_invoke.rrpc_id,
           recv->data.raw_service_invoke.data_len);
}

static void demo_dm_recv_raw_data_reply(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_raw_data_reply receive reply for up_raw msg, data len = %d\r\n", recv->data.raw_data.data_len);
    /* TODO: 用户处理下行的二进制数据, 位于recv->data.raw_data.data中 */
}



/* 用户数据接收处理回调函数 */
static void demo_dm_recv_handler(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_handler, type = %d\r\n", recv->type);

    switch (recv->type) {

        /* 属性上报, 事件上报, 获取期望属性值或者删除期望属性值的应答 */
        case AIOT_DMRECV_GENERIC_REPLY: {
            demo_dm_recv_generic_reply(dm_handle, recv, userdata);
        }
        break;

        /* 属性设置 */
        case AIOT_DMRECV_PROPERTY_SET: {
            demo_dm_recv_property_set(dm_handle, recv, userdata);
        }
        break;

        /* 异步服务调用 */
        case AIOT_DMRECV_ASYNC_SERVICE_INVOKE: {
            demo_dm_recv_async_service_invoke(dm_handle, recv, userdata);
        }
        break;

        /* 同步服务调用 */
        case AIOT_DMRECV_SYNC_SERVICE_INVOKE: {
            demo_dm_recv_sync_service_invoke(dm_handle, recv, userdata);
        }
        break;

        /* 下行二进制数据 */
        case AIOT_DMRECV_RAW_DATA: {
            demo_dm_recv_raw_data(dm_handle, recv, userdata);
        }
        break;

        /* 二进制格式的同步服务调用, 比单纯的二进制数据消息多了个rrpc_id */
        case AIOT_DMRECV_RAW_SYNC_SERVICE_INVOKE: {
            demo_dm_recv_raw_sync_service_invoke(dm_handle, recv, userdata);
        }
        break;

        /* 上行二进制数据后, 云端的回复报文 */
        case AIOT_DMRECV_RAW_DATA_REPLY: {
            demo_dm_recv_raw_data_reply(dm_handle, recv, userdata);
        }
        break;

        default:
            break;
    }
}

/* 执行aiot_mqtt_recv的线程, 包含网络自动重连和从服务器收取MQTT消息 */
void *demo_mqtt_recv_thread(void *args)
{
    int32_t res = STATE_SUCCESS;

    while (g_mqtt_recv_thread_running) {
        res = aiot_mqtt_recv(args);
        if (res < STATE_SUCCESS) {
            if (res == STATE_USER_INPUT_EXEC_DISABLED) {
                break;
            }
            sleep(1);
        }
    }
    return NULL;
}

/* 执行aiot_mqtt_process的线程, 包含心跳发送和QoS1消息重发 */
void *demo_mqtt_process_thread(void *args)
{
    int32_t res = STATE_SUCCESS;

    while (g_mqtt_process_thread_running) {
        res = aiot_mqtt_process(args);
        if (res == STATE_USER_INPUT_EXEC_DISABLED) {
            break;
        }
        sleep(1);
    }
    return NULL;
}


// 构造函数，初始化成员变量
IOTConnect::IOTConnect(){
    initializeIotSdk();
}





void IOTConnect::initializeIotSdk() {
    int32_t     res = STATE_SUCCESS;
    aiot_sysdep_network_cred_t cred; /* 安全凭据结构体, 如果要用TLS, 这个结构体中配置CA证书等参数 */
    uint8_t post_reply = 1;


    /* 配置SDK的底层依赖 */
    aiot_sysdep_set_portfile(&g_aiot_sysdep_portfile);
    /* 配置SDK的日志输出 */
    aiot_state_set_logcb(demo_state_logcb);

    /* 创建SDK的安全凭据, 用于建立TLS连接 */
    memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
    cred.option = AIOT_SYSDEP_NETWORK_CRED_SVRCERT_CA;  /* 使用RSA证书校验MQTT服务端 */
    cred.max_tls_fragment = 16384; /* 最大的分片长度为16K, 其它可选值还有4K, 2K, 1K, 0.5K */
    cred.sni_enabled = 1;                               /* TLS建连时, 支持Server Name Indicator */
    cred.x509_server_cert = ali_ca_cert;                 /* 用来验证MQTT服务端的RSA根证书 */
    cred.x509_server_cert_len = strlen(ali_ca_cert);     /* 用来验证MQTT服务端的RSA根证书长度 */

    /* 创建1个MQTT客户端实例并内部初始化默认参数 */
    mqtt_handle = aiot_mqtt_init();
    if (mqtt_handle == NULL) {
        std::cout << "aiot_mqtt_init failed"<<std::endl;
        return;}


    /* 配置MQTT服务器地址 */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_HOST, (void *)mqtt_host);
    /* 配置MQTT服务器端口 */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PORT, (void *)&port);
    /* 配置设备productKey */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PRODUCT_KEY, (void *)product_key);
    /* 配置设备deviceName */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_NAME, (void *)device_name);
    /* 配置设备deviceSecret */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_SECRET, (void *)device_secret);
    /* 配置网络连接的安全凭据, 上面已经创建好了 */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_NETWORK_CRED, (void *)&cred);
    /* 配置MQTT事件回调函数 */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_EVENT_HANDLER, (void *)demo_mqtt_event_handler);


    /* 创建DATA-MODEL实例 */
    dm_handle = aiot_dm_init();
    if (dm_handle == NULL) {
        printf("aiot_dm_init failed");
        return;
    }
    /* 配置MQTT实例句柄 */
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_MQTT_HANDLE, mqtt_handle);
    /* 配置消息接收处理回调函数 */
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_RECV_HANDLER, (void *)demo_dm_recv_handler);

    /* 配置是云端否需要回复post_reply给设备. 如果为1, 表示需要云端回复, 否则表示不回复 */
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_POST_REPLY, (void *)&post_reply);

    /* 与服务器建立MQTT连接 */
    res = aiot_mqtt_connect(mqtt_handle);
    if (res < STATE_SUCCESS) {
        /* 尝试建立连接失败, 销毁MQTT实例, 回收资源 */
        aiot_dm_deinit(&dm_handle);
        aiot_mqtt_deinit(&mqtt_handle);
        printf("aiot_mqtt_connect failed: -0x%04X\n\r\n", -res);
        printf("please check variables like mqtt_host, produt_key, device_name, device_secret in demo\r\n");
        return;
    }

  
    /* 创建一个单独的线程, 专用于执行aiot_mqtt_process, 它会自动发送心跳保活, 以及重发QoS1的未应答报文 */
    g_mqtt_process_thread_running = 1;
    res = pthread_create(&g_mqtt_process_thread, NULL, demo_mqtt_process_thread, mqtt_handle);
    if (res < 0) {
        printf("pthread_create demo_mqtt_process_thread failed: %d\n", res);
        aiot_dm_deinit(&dm_handle);
        aiot_mqtt_deinit(&mqtt_handle);
        return;
    }

    /* 创建一个单独的线程用于执行aiot_mqtt_recv, 它会循环收取服务器下发的MQTT消息, 并在断线时自动重连 */
    g_mqtt_recv_thread_running = 1;
    res = pthread_create(&g_mqtt_recv_thread, NULL, demo_mqtt_recv_thread, mqtt_handle);
    if (res < 0) {
        printf("pthread_create demo_mqtt_recv_thread failed: %d\n", res);
        aiot_dm_deinit(&dm_handle);
        aiot_mqtt_deinit(&mqtt_handle);
        return;
    }


}

void IOTConnect::deinitializeIotSdk() {
    // 检查设备管理（DM）实例是否已初始化，如果是，则反初始化
    if (dm_handle != NULL) {
        aiot_dm_deinit(&dm_handle);
        dm_handle = NULL; // 确保指针被置空，避免悬挂指针
        std::cout << "Device Management (DM) instance deinitialized." << std::endl;
    }

    // 检查MQTT实例是否已初始化，如果是，则断开连接并反初始化
    if (mqtt_handle != NULL) {
        // 断开MQTT连接
        int32_t res = aiot_mqtt_disconnect(mqtt_handle);
        if (res < 0) {
            std::cout << "aiot_mqtt_disconnect failed: -0x" << std::hex << -res << std::endl;
        } else {
            std::cout << "MQTT disconnected." << std::endl;
        }

        // 反初始化MQTT实例
        aiot_mqtt_deinit(&mqtt_handle);
        mqtt_handle = NULL; // 确保指针被置空，避免悬挂指针
        std::cout << "MQTT instance deinitialized." << std::endl;
    }

    // 在这里执行任何其他清理工作，例如释放分配的内存等
}

IOTConnect::~IOTConnect() {
    deinitializeIotSdk();

    // 析构函数其他代码...
}

void IOTConnect::reportDistance(float distance) {
    // 确保dmHandle已经初始化并配置好
    if (dm_handle == nullptr) {
        // 错误处理: DM句柄未初始化
        std::cerr << "DM handle is not initialized." << std::endl;
        return;
    }

    // 构造上报的JSON字符串
    char payload[128];
    snprintf(payload, sizeof(payload), "{\"Distance\": %.2f}", distance);

    // 准备发送的消息
    aiot_dm_msg_t msg;
    memset(&msg, 0, sizeof(aiot_dm_msg_t));
    msg.type = AIOT_DMMSG_PROPERTY_POST; // 设置消息类型为属性上报
    msg.data.property_post.params = payload; // 设置消息内容

    // 发送消息
    int32_t res = aiot_dm_send(dm_handle, &msg);
    if (res < 0) {
        // 错误处理: 发送失败
        std::cerr << "Send distance property failed, code: " << res << std::endl;
    } else {
        std::cout << "Distance property reported successfully." << std::endl;
    }
}
