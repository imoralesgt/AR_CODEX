#include "globals.h"

#ifndef PINOUT_H
#define PINOUT_H


#define TOTAL_MOTORS MOTORS

#define PIN_MOTOR0 9
#define PIN_MOTOR1 8
#define PIN_MOTOR2 7
#define PIN_DIRECTION 2


#define PIN_ENDSTOP0 10
#define PIN_ENDSTOP1 11
#define PIN_ENDSTOP2 12
#define PIN_ENDSTOP3 15

#define DEBUG_AMBU_DIRECTION 4


const int MOTOR[] = {PIN_MOTOR0, PIN_MOTOR1};
const int START_ENDSTOP[] = {PIN_ENDSTOP0, PIN_ENDSTOP1};
const int END_ENDSTOP[] = {PIN_ENDSTOP2, PIN_ENDSTOP3};




#endif