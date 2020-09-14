#ifndef GLOBALS_H
#define GLOBALS_H

//#define DEBUG_MODE 1


/*
DEFALT CONTROL UNITS:

Volume = mililiters (ml)
Pressure = cmH2O
RPM = Respirations per minute (1/minute)
IERatio = Dimensionless
Flow = mililiters per second (ml/s)
*/

//Conversion factors for incoming sensor data units
#define DECIPASCALS_TO_CMH20 0.00101972 //1 dPa = 0.00101972 cmH2O
#define PASCALS_TO_CMH20 0.0101972 //1 Pa = 0.0101972 cmH2O
#define DECILITERS_PER_MIN_TO_MILILITERS_PER_MINUTE 100.0 //1 dL/min = 100 mL/min
#define MILILITERS_PER_MIN_TO_MILILITERS_PER_MINUTE 1.0 //1 mL/min = 1 mL/min
#define MILILITERS_PER_MIN_TO_MILILITERS_PER_SECOND 1.0/60.0 //1 mL/min = 1/60 mL/sec
#define FLOW_OFFSET 0 //Zero offset equals to 1.6V from sensors board
#define PRESS_OFFSET 0 //Zero offset for pressure

//Conversion factors for incoming GUI set points
#define GUI_MAX_VOLUME_TO_MILILITERS 10.0
#define GUI_MAX_PRESSURE 1.0
#define GUI_RESPIRATION_RATIO 1.0
#define GUI_IE_RATIO_NORMALIZATION 0.1

//IRM Arduino workaround for GCC compilation in x86
#ifndef ARDUINO
    #define byte char 
#endif


#define MOTORS 2 //How many motors will be working simultaneously


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

//Sensor data after conversion factors applied
extern volatile float sensorsConvertedPressure;
extern volatile float sensorsConvertedAirFlow;


//GUI output (control input)
extern volatile float guiRPM;
extern volatile float guiIEratio;
extern volatile float guiMaxPressure;
extern volatile float guiMinVol;
extern volatile float guiMaxVol;


/*
=======================
Motor-related Globals
=======================
*/
#define MIN_MOTOR_TIMER 74 //Reducing this value, decreases torque and increases glitch occurences.
#define MAX_MOTOR_TIMER 139




/*
=======================
Control-related Globals
=======================
*/

//IRM PID-specific parameters. Do NOT change unless you know what you're doing
#define KP 5.0/1000.0
#define KI 1.5/1000.0
#define KD 0.1/1000.0

//Set the actuator's output limits here
#define MOTOR_MIN_OUT -100
#define MOTOR_MAX_OUT 100
#define SPEED_HYSTERESIS 2

//Discrete PID update period (seconds)
#define DT 0.004 //4 miliseconds (250 Hz)
// #define DT 0.016 //16 miliseconds (62.5 Hz)

//Actuator output reduction factor when max pressure is reached
#define OUTPUT_REDUCTION_FACTOR 31.0/32.0 //Reduce output speed in 1/32 of current value

#define MIN_MAX_OUTPUT 5 //Minimum MAX Speed Output when overpressure reached

#define MAX_OVERPRESSURE_CYCLES 10 //Switch back to expiration if MAX overpressure cycles exceeded

#define MAX_INSPIRATION_CYCLES_OVERLOAD_RATIO 10.0 //If inspiration takes more than 1.5 times, go back to expiration immediately

//Default IE Ratio if not sent from GUI
#define DEFAULT_IE_RATIO 0.4/GUI_IE_RATIO_NORMALIZATION



#endif