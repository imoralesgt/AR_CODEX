#include "globals.h"

#ifndef PINOUT_H
#define PINOUT_H



//GPIO PIN DEFINITIONS

#define PIN_MOTOR0 3 //PD3
#define PIN_MOTOR1 6 //PD6
#define PIN_MOTOR2 7 //PD7
#define PIN_DIRECTION 4 //PD4


#define PIN_ENDSTOP0 2  //PD2
#define PIN_ENDSTOP1 5  //PD5
#define PIN_ENDSTOP2 14 //PC0 (A0)
#define PIN_ENDSTOP3 15 //PC1 (A1)

#define DEBUG_AMBU_DIRECTION 7 //PD7

#define SOFT_I2C_SDA 16 //PC2 (A2) 
#define SOFT_I2C_SCL 17 //PC3 (A3)
#define SOFT_I2C_PORT PORTC
#define SOFT_I2C_PORT_SDA 2
#define SOFT_I2C_PORT_SCL 3

#define VALVE0_OUTPUT 9  //PB1
#define VALVE1_OUTPUT 10 //PB2
#define VALVE2_OUTPUT 11 //PB3

//Unused pins:
/*
    PD8(8)
    PB4(12)
    PB5(13) (shared with BUILTIN_LED)
    A6 (ANALOG INPUT-ONLY PIN)
    A7 (ANALOG INPUT-ONLY PIN)
*/



//Other GPIO-related definitions

#define TOTAL_MOTORS MOTORS

const int MOTOR[] = {PIN_MOTOR0, PIN_MOTOR1};
const int START_ENDSTOP[] = {PIN_ENDSTOP0, PIN_ENDSTOP1};
const int END_ENDSTOP[] = {PIN_ENDSTOP2, PIN_ENDSTOP3};




#endif