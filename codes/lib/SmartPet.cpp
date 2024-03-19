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

// 假设您的产品信息如下（需替换为您自己的）
const char *product_key = "a1X2bEnP82z";
const char *device_name = "testDeviceName";
const char *device_secret = "testDeviceSecret";
const char *region_id = "cn-shanghai";

const char  *mqtt_host = "${YourInstanceId}.mqtt.iothub.aliyuncs.com";
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
            char *cause = (event->data.disconnect == AIOT_MQTTDISCONNEVT_NETWORK_DISCONNECT) ? ("network disconnect") :
                          ("heartbeat disconnect");
            printf("AIOT_MQTTEVT_DISCONNECT: %s\n", cause);
        }
        break;

        default: {

        }
    }
}


// 构造函数，初始化成员变量
SmartPet::SmartPet(int trigPin, int echoPin, int in1, int in2, int in3, int in4, int SCK, int SDA)
: sensor(trigPin, echoPin), motor(in1, in2, in3, in4), motorRunning(false), shouldOperateMotor(false) 
{
    weightArgs.SCK = SCK; // 设置SCK引脚
    weightArgs.SDA = SDA; // 设置SDA引脚
    WeightSensor::setup(&weightArgs); // 使用新引脚初始化重量传感器
    initializeIotSdk();


}


// 主运行循环。
void SmartPet::run() {
    std::cout << "SmartPet operational." << std::endl;
    sensor.measureDistanceAsync([this](float distance) { // 异步测量距离并使用回调函数处理结果
        this->operateMotorBasedOnDistance(distance);
    });

    while (true) {
        checkWeightAndOperateMotor(); // 检查重量并根据重量操作电机
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 根据传感器测量的距离控制电机。
void SmartPet::operateMotorBasedOnDistance(float distance) {
    std::cout << "Distance: " << distance << " cm" << std::endl;
    if (distance < 10 && !motorRunning) {
        std::cout << "Object detected within 10cm. Operating motor..." << std::endl;
        motor.forward(2, 100); // 
        motorRunning = true;
    }
}

// 检查重量并根据重量操作电机。
void SmartPet::checkWeightAndOperateMotor() {
    WeightSensor::start(&weightArgs); // 开始承重传感器的测量
    if (weightArgs.weight >= 150 && motorRunning) { // 如果重量达到150g并且电机正在运行
        std::cout << "Target weight reached. Rolling back motor..." << std::endl;
        motor.rollback(2, 100); // 
        motorRunning = false;
    }
}

void SmartPet::initializeIotSdk() {
    // 初始化系统依赖库
    aiot_sysdep_set_portfile(&g_aiot_sysdep_portfile);
    // 初始化日志回调，可以根据需要调整日志级别
    aiot_state_set_logcb(demo_state_logcb);

    // 创建MQTT句柄并进行初始化
    mqtt_handle = aiot_mqtt_init();
    if (mqtt_handle == NULL) {
        std::cout << "aiot_mqtt_init failed" << std::endl;
        return;
    }

    // 配置MQTT服务器地址
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_HOST, (void *)mqtt_host);
    // 配置MQTT服务器端口，8883为默认TLS端口
    uint16_t port = 8883;
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PORT, (void *)&port);
    // 配置设备三元组
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PRODUCT_KEY, (void *)product_key);
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_NAME, (void *)device_name);
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_SECRET, (void *)device_secret);

    // 配置MQTT连接的安全选项，使用TLS连接
    aiot_sysdep_network_cred_t cred;
    memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
    cred.option = AIOT_SYSDEP_NETWORK_CRED_SVRCERT_CA;
    cred.x509_server_cert = ali_ca_cert; // ali_ca_cert为CA证书内容
    cred.x509_server_cert_len = strlen(ali_ca_cert);
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_NETWORK_CRED, &cred);

    // 设置MQTT事件回调，处理连接、断开等事件
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_EVENT_HANDLER, demo_mqtt_event_handler);

    // 连接到MQTT服务器
    int32_t res = aiot_mqtt_connect(mqtt_handle);
    if (res < 0) {
        std::cout << "aiot_mqtt_connect failed: " << res << std::endl;
        aiot_mqtt_deinit(&mqtt_handle);
        mqtt_handle = NULL;
        return;
    }

    // 创建DATA-MODEL实例并进行配置，以便发送和接收物模型消息
    dm_handle = aiot_dm_init();
    if (dm_handle == NULL) {
        std::cout << "aiot_dm_init failed" << std::endl;
        return;
    }
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_MQTT_HANDLE, mqtt_handle);
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_RECV_HANDLER, demo_dm_recv_handler);

    // 可以在这里进行更多配置，例如订阅特定主题等
}
