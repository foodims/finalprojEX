//=====[Libraries]=============================================================

#include "toaster_alert_system.h"
//=====[Main function, the program entry point after power on or reset]========

int main()
{
    toasterAlertSystemInit();
    while (true) {
        toasterAlertSystemUpdate();
    }
}