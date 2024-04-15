#include "SmartPet.h"
#include <unistd.h>


int main() {
    


    IOTConnect pet;
    while (1) {
        
        pet.reportDistance(7.7);
        //demo_send_event_post(dm_handle, "Error", "{\"ErrorCode\": 0}");

        sleep(10);
    }
    
   // pet.reportDistance(7.7);

    return 0;
}
