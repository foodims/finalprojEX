//=====[Libraries]=============================================================

#include "alarm.h"
#include "lcd.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "timer.h"
#include "user_interface.h"
#include "lcd.h"

//=====[Declaration of private defines]========================================

// defines potentiometer levels
#define light 0.3
#define dark 0.7
//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn Button(D14, PullDown);
DigitalIn Switch(D15, PullDown);
AnalogIn Potentiometer(A1);

DigitalOut green_LED(D12);
DigitalOut red_LED(D13);
DigitalOut alarmBuzzer(PE_10);

UnbufferedSerial uartUsb( USBTX, USBRX, 115200 );

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

bool toasterReady = false;
bool toasterOn = false;
bool printOnce = false;
int toastLevel = 0;

// Helper function to calculate string length
size_t getStringLength(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void printMessage(const char* message) {
    uartUsb.write( message, getStringLength(message) );
}

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

// button configurations and initializations 
void InputsInit() {
Button.mode(PullDown);
Switch.mode(PullDown);
}

void outputsInit() {
    green_LED = OFF;
    red_LED = OFF;
    alarmBuzzer = ON;
}

// determines if food is in toaster
void Food_In() {
if (Button && Switch) {
    toasterReady = true;
    toasterOn = true;
    green_LED = ON;
if (printOnce == false) {
    printMessage("Food has been inserted in toaster and toaster is on");
    printOnce = true;
}
}
else {
    toasterReady = false;
    toasterOn = false;
    printMessage("Food is not in toaster, DO NOT start");
}
}



// determines desired darkness level of toast 
// corresponds with timer
int Dark_Level() {   
if (toasterOn == true) {
    float levelselect = Potentiometer.read();
    if (levelselect < light) {
       return 1;
    }
    if ((levelselect > light) && (levelselect < dark)) {
        return  2;
    }
    if (levelselect > dark) {
        return 3;
    }
    else {
        return 0;
    }
}
else {
    return 0;
}
}

//updates interface based on inputs
//updates display 
void user_InterfaceUpdate() {
Food_In();
//Toast_On();
Dark_Level();

displayModeWrite(DISPLAY_MODE_CHAR);
displayClear();

displayCharPositionWrite ( 0,0 );
displayStringWrite( "Level:" );


if (toasterOn && toasterReady) {
    char levelString[2] = "";
    displayCharPositionWrite( 8,0 );
    if (toastLevel == 1) {
        sprintf(levelString, "%d", Dark_Level());
}
    if (toastLevel == 2) {
        sprintf(levelString, "%d", Dark_Level());
}
    if (toastLevel == 3) {
        sprintf(levelString, "%d", Dark_Level());
}
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Time:" );
    char timeRemaining[2] = "";
    displayCharPositionWrite( 8,1 );
    sprintf(timeRemaining, "%d", getTimeRemaining());



    if (&alarmState){
        displayCharPositionWrite ( 10,1 );
        displayStringWrite( "DANGER" );
}
    else {
        displayCharPositionWrite ( 10,1 );
        displayStringWrite( "SAFE" );
}
}
}