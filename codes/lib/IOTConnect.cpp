#include "IOTConnect.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <nlohmann/json.hpp>

#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"
#include "aiot_mqtt_api.h"
#include "aiot_dm_api.h"

const char *product_key = "k0txi2jzZL9";
const char *device_name = "raspberry_4b";
const char *device_secret = "6e0f2762dba515a35eb098b138d90405";
const char *region_id = "cn-shanghai";

const char  *mqtt_host = "iot-06z00ecae6zqnin.mqtt.iothub.aliyuncs.com";
using json = nlohmann::json; // Referencing libraries directly in code using json
/* 
   Port: 1883/443, corresponding to the certificate (GlobalSign R1), expires in January 2028, which may cause the device to fail to establish a connection.
    (Recommended) New port: 8883, will carry a new certificate, self-signed by Aliyun IoT platform, expires in July 2053.
*/
const uint16_t port = 8883;

/* A collection of system adaptation functions in the portfiles/aiot_port folder. */
extern aiot_sysdep_portfile_t g_aiot_sysdep_portfile;

/* Server certificate located in external/ali_ca_cert.c */
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

/* core/aiot_mqtt_api.h MQTT event callback function, triggered when network is connected/reconnected/disconnected, see core/aiot_mqtt_api.h for event definition*/
void demo_mqtt_event_handler(void *handle, const aiot_mqtt_event_t *event, void *userdata)
{
    switch (event->type) {
        
        case AIOT_MQTTEVT_CONNECT: {
            printf("AIOT_MQTTEVT_CONNECT\n");
        }
        break;

        case AIOT_MQTTEVT_RECONNECT: {
            printf("AIOT_MQTTEVT_RECONNECT\n");
        }
        break;

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
           
           
    IOTConnect *iotConnect = static_cast<IOTConnect*>(userdata);

    // Parsing JSON strings to find properties
    const char *params = recv->data.property_set.params;
    int weightValue;
    if (sscanf(params, "{\"Weightthreshold\":%d}", &weightValue) == 1) {
    iotConnect -> weight1 = weightValue;  
    printf("weightvalue: %d/n", weightValue);
    }
   
    /* TODO: The following code demonstrates how to respond to property setting commands from the cloud platform, users can uncomment to see the effect of the demo */
    
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
    
}

static void demo_dm_recv_async_service_invoke(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_async_service_invoke msg_id = %ld, service_id = %s, params = %.*s\r\n",
           (unsigned long)recv->data.async_service_invoke.msg_id,
           recv->data.async_service_invoke.service_id,
           recv->data.async_service_invoke.params_len,
           recv->data.async_service_invoke.params);

    
}

static void demo_dm_recv_sync_service_invoke(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_sync_service_invoke msg_id = %ld, rrpc_id = %s, service_id = %s, params = %.*s\r\n",
           (unsigned long)recv->data.sync_service_invoke.msg_id,
           recv->data.sync_service_invoke.rrpc_id,
           recv->data.sync_service_invoke.service_id,
           recv->data.sync_service_invoke.params_len,
           recv->data.sync_service_invoke.params);

   
}

static void demo_dm_recv_raw_data(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_raw_data raw data len = %d\r\n", recv->data.raw_data.data_len);
    
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
    
}



/* User Data Receiving Processing Callback Functions */
static void demo_dm_recv_handler(void *dm_handle, const aiot_dm_recv_t *recv, void *userdata)
{
    printf("demo_dm_recv_handler, type = %d\r\n", recv->type);

    switch (recv->type) {

        /* Attribute Reporting, Event Reporting, Answer to get desired attribute value or delete desired attribute value */
        case AIOT_DMRECV_GENERIC_REPLY: {
            demo_dm_recv_generic_reply(dm_handle, recv, userdata);
        }
        break;

        /* Property Settings */
        case AIOT_DMRECV_PROPERTY_SET: {
            demo_dm_recv_property_set(dm_handle, recv, userdata);
        }
        break;

        /* asynchronous service call */
        case AIOT_DMRECV_ASYNC_SERVICE_INVOKE: {
            demo_dm_recv_async_service_invoke(dm_handle, recv, userdata);
        }
        break;

        /* Synchronised Service Calls */
        case AIOT_DMRECV_SYNC_SERVICE_INVOKE: {
            demo_dm_recv_sync_service_invoke(dm_handle, recv, userdata);
        }
        break;

        /*downlink binary data */
        case AIOT_DMRECV_RAW_DATA: {
            demo_dm_recv_raw_data(dm_handle, recv, userdata);
        }
        break;

        /* Synchronised service call in binary format, with an additional rrpc_id than a simple binary data message  */
        case AIOT_DMRECV_RAW_SYNC_SERVICE_INVOKE: {
            demo_dm_recv_raw_sync_service_invoke(dm_handle, recv, userdata);
        }
        break;

        /* After uploading the binary data, the reply message from the cloud */
        case AIOT_DMRECV_RAW_DATA_REPLY: {
            demo_dm_recv_raw_data_reply(dm_handle, recv, userdata);
        }
        break;

        default:
            break;
    }
}

/* The thread that executes aiot_mqtt_recv, including automatic network reconnection and receiving MQTT messages from the server. */
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

/* Threads executing aiot_mqtt_process, including heartbeat sending and QoS1 message retransmission */
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


// Constructor, initialising member variables
IOTConnect::IOTConnect(){
    initializeIotSdk();
}





void IOTConnect::initializeIotSdk() {
    int32_t     res = STATE_SUCCESS;
    aiot_sysdep_network_cred_t cred; /* Security credentials structure, if you want to use TLS, this structure is configured with parameters such as CA certificate. */
    uint8_t post_reply = 1;


    /* Configuring the SDK's underlying dependencies*/
    aiot_sysdep_set_portfile(&g_aiot_sysdep_portfile);
    /*  Configure the SDK log output */
    aiot_state_set_logcb(demo_state_logcb);

    /* Creates security credentials for the SDK, which are used to establish a TLS connection. */
    memset(&cred, 0, sizeof(aiot_sysdep_network_cred_t));
    cred.option = AIOT_SYSDEP_NETWORK_CRED_SVRCERT_CA;  
    cred.max_tls_fragment = 16384; 
    cred.sni_enabled = 1;                             
    cred.x509_server_cert = ali_ca_cert;                 
    cred.x509_server_cert_len = strlen(ali_ca_cert);     

    /* Create 1 instance of MQTT client and initialise default parameters internally */
    mqtt_handle = aiot_mqtt_init();
    if (mqtt_handle == NULL) {
        std::cout << "aiot_mqtt_init failed"<<std::endl;
        return;}


    /* Configuring the MQTT Server Address */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_HOST, (void *)mqtt_host);
    /* Configuring the MQTT Server Port */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PORT, (void *)&port);
    /* productKey */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_PRODUCT_KEY, (void *)product_key);
    /* deviceName */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_NAME, (void *)device_name);
    /* deviceSecret */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_DEVICE_SECRET, (void *)device_secret);
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_NETWORK_CRED, (void *)&cred);
    /* Configuring MQTT Event Callback Functions  */
    aiot_mqtt_setopt(mqtt_handle, AIOT_MQTTOPT_EVENT_HANDLER, (void *)demo_mqtt_event_handler);


    /* Creating a DATA-MODEL instance */
    dm_handle = aiot_dm_init();
    if (dm_handle == NULL) {
        printf("aiot_dm_init failed");
        return;
    }
    /* Configuring MQTT Instance Handles */
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_MQTT_HANDLE, mqtt_handle);
    /* Configuring Message Receiving Processing Callback Functions */
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_RECV_HANDLER, (void *)demo_dm_recv_handler);
    
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_USERDATA, (void *)this); 
    aiot_dm_setopt(dm_handle, AIOT_DMOPT_RECV_HANDLER, (void *)demo_dm_recv_handler);

    aiot_dm_setopt(dm_handle, AIOT_DMOPT_POST_REPLY, (void *)&post_reply);

    /* Server establishes MQTT connection */
    res = aiot_mqtt_connect(mqtt_handle);
    if (res < STATE_SUCCESS) {
        aiot_dm_deinit(&dm_handle);
        aiot_mqtt_deinit(&mqtt_handle);
        printf("aiot_mqtt_connect failed: -0x%04X\n\r\n", -res);
        printf("please check variables like mqtt_host, produt_key, device_name, device_secret in demo\r\n");
        return;
    }

  
    /* Create a separate thread dedicated to the execution of aiot_mqtt_process, which automatically sends out heartbeat keepalives and retransmits QoS1 unanswered messages. */
    g_mqtt_process_thread_running = 1;
    res = pthread_create(&g_mqtt_process_thread, NULL, demo_mqtt_process_thread, mqtt_handle);
    if (res < 0) {
        printf("pthread_create demo_mqtt_process_thread failed: %d\n", res);
        aiot_dm_deinit(&dm_handle);
        aiot_mqtt_deinit(&mqtt_handle);
        return;
    }

    /* Create a separate thread to execute aiot_mqtt_recv, which will loop through the MQTT messages sent by the server and automatically reconnect when disconnected. */
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
    // Check if the Device Management (DM) instance is initialised, and if so, counter-initialise it
    if (dm_handle != NULL) {
        aiot_dm_deinit(&dm_handle);
        dm_handle = NULL; 
        std::cout << "Device Management (DM) instance deinitialized." << std::endl;
    }

    // Check if the MQTT instance is initialised, if so, disconnect and reverse initialisation
    if (mqtt_handle != NULL) {
        // Disconnecting MQTT
        int32_t res = aiot_mqtt_disconnect(mqtt_handle);
        if (res < 0) {
            std::cout << "aiot_mqtt_disconnect failed: -0x" << std::hex << -res << std::endl;
        } else {
            std::cout << "MQTT disconnected." << std::endl;
        }

        
        aiot_mqtt_deinit(&mqtt_handle);
        mqtt_handle = NULL; 
        std::cout << "MQTT instance deinitialized." << std::endl;
    }

    
}

IOTConnect::~IOTConnect() {
    deinitializeIotSdk();

}

void IOTConnect::reportDistance(float distance, int weight) {
    
    if (dm_handle == nullptr) {
        // DM handle is not initialized
        std::cerr << "DM handle is not initialized." << std::endl;
        return;
    }

    // Constructing the reported JSON string
    char payload[128];
    snprintf(payload, sizeof(payload), "{\"Distance\": %.2f, \"Weight\": %d}", distance, weight);

    // Message ready to send
    aiot_dm_msg_t msg;
    memset(&msg, 0, sizeof(aiot_dm_msg_t));
    msg.type = AIOT_DMMSG_PROPERTY_POST; // Set the message type to Attribute Up
    msg.data.property_post.params = payload; // Setting the message content

    // send
    int32_t res = aiot_dm_send(dm_handle, &msg);
    if (res < 0) {
        // failed
        std::cerr << "Send distance property failed, code: " << res << std::endl;
    } else {
        std::cout << "Distance property reported successfully." << std::endl;
    }
}
