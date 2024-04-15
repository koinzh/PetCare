#ifndef SMARTPET_H
#define SMARTPET_H

#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"
#include "aiot_mqtt_api.h"
#include "aiot_dm_api.h"
#include <cstddef>



class IOTConnect {
public:
    IOTConnect();
    
    void *mqtt_handle = NULL;
    void *dm_handle = NULL;
    int weight1 = 300;
     ~IOTConnect();

    void initializeIotSdk(); 
    void deinitializeIotSdk(); 
    void reportDistance(float distance, int weight); 


};

#endif // SMARTPET_H
