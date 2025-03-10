//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "alarm.h"
#include "gas_sensor.h"
#include "lcd.h"
#include "pc_serial_com.h"
#include "temperature_sensor.h"
#include "timer.h"
#include "user_interface.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

// runs all initializations
void toasterAlertSystemInit() {
  InputsInit();
  alarmSystemInit();
  temperatureSensorInit();
  gasSensorInit();
  timerInit();
}

// runs all updates
void toasterAlertSystemUpdate() {
  user_InterfaceUpdate();
  alarmUpdate();
  gasSensorUpdate();
  temperatureSensorUpdate();
  timerUpdate();
}
