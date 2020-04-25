#ifndef GLOBALS_H
#define GLOBALS_H

//IRM Arduino workaround for GCC compilation in x86
#ifndef ARDUINO_H
    #define byte char 
#endif


/*
=======================
Control-related Globals
=======================
*/


//IRM PID-specific parameters. Do NOT change unless you know what you're doing
#define KP 1.0
#define KI 0.3
#define KD 0.0

//Set the actuator's output limits here
#define MOTOR_MIN_OUT -255
#define MOTOR_MAX_OUT 255

//Discrete PID update period (seconds)
#define DT 0.004 //4 miliseconds (250 Hz)

//Actuator output reduction factor when max pressure is reached
#define OUTPUT_REDUCTION_FACTOR 31.0/32.0 //Reduce output speed in 1/32 of current value











#endif