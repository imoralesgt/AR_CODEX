#ifndef GLOBALS_H
#define GLOBALS_H

//IRM Arduino workaround for GCC compilation in x86
#ifndef ARDUINO
    #define byte char 
#endif


#define MOTORS 2 //How many motors will be available


/*
===================================
Top module global wrapper variables
===================================

Variables are named according to their
corresponding output module name
*/

//Buffer output (control/gui input)
extern volatile float bufferPressure;
extern volatile float bufferAirFlow;
extern volatile float bufferAlarm; //Future implementation

//Sensors output (buffer input)
extern volatile float sensorsPressure;
extern volatile float sensorsAirFlow;

//GUI output (control input)
extern volatile float guiRPM;
extern volatile float guiIEratio;
extern volatile float guiMaxPressure;
extern volatile float guiMinVol;
extern volatile float guiMaxVol;

//EndStop switches output (control/motors input)


//Control output (motors/sensors/gui input)








/*
=======================
Control-related Globals
=======================
*/


//IRM PID-specific parameters. Do NOT change unless you know what you're doing
#define KP 5.0/10000.0
#define KI 6.0/10000.0
#define KD 0.0

//Set the actuator's output limits here
#define MOTOR_MIN_OUT -100
#define MOTOR_MAX_OUT 100
#define SPEED_HYSTERESIS 5

//Discrete PID update period (seconds)
#define DT 0.004 //4 miliseconds (250 Hz)

//Actuator output reduction factor when max pressure is reached
#define OUTPUT_REDUCTION_FACTOR 31.0/32.0 //Reduce output speed in 1/32 of current value
















#endif