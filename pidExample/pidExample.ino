/*
++++++++++++++++++++++++++++
      ARDUINO EXAMPLE
++++++++++++++++++++++++++++
    USAGE:
    1) Create a new Pid object and initialize it with the parameters required
       1.1) Parameters:
            (float) [p]    : Kp (proportional) PID constant
            (float) [i]    : Ki (integral) PID constant
            (float) [d]    : Kd (derivative) PID constant
            (float) [minO] : Minimum actuator output (e.g. PWM value = 0, servo angle = 40, temperature = 25, etc)
            (float) [maxO] : Maximum actuator output (e.g. PWM value = 255, servo angle = 120, temperature = 100, etc)

        1.2) Returns:
            Nothing



    2) Establish set-point value by calling pidSetPoint(sp)
      2.1) Parameters:
           (float) [sp] : Desired PID set-point value
      
      2.2) Set point updatability:
           Set-point can be tuned in run-time, causing no output spikes nor undesirable effects. i.e. you can
           run pidSetPoint(sp) anywhere in the code if required to update the desired set-point.
      
      2.3) Returns:
           Nothing



    3) Periodically call pidUpdate(currentValue)
       3.1) Run pidUpdate periodic calls form a timer, or check time deltas periodicaly. 
       Avoid using "delays" as much as possible, as it may lead to undesirable conditions.
       
       3.2) Parameters:
            (float) [currentValue] : current sensor value. Must be in the same units than output actuator

       3.3) Returns:
            (float) [pidUpdate] : updated actuator value
++++++++++++++++++++++++++++
*/

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Arduino example: control temperature using only a cooling device (such as a fan).
Heating element not available.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GPIO Pinout:
A0 <- Analog Input 0 to read LM35 temperature sensor
13 <- Digital Output 13 to set the fan speed via PWM

Note: Fan isn't directly driven by Arduino, use a MOSFET or a L293/L298 to drive it
*/


#include <Pid.h>
#include <time.h>

//Set your own PID constants here

//These values are specificaly tunned for the temperature control system
#define KP 30.0
#define KI 8.0
#define KD 0.5

//Set the actuator's output limits here
#define MIN_OUT 0 //There's no reverse (heating) fan Mode
#define MAX_OUT 255 //Fan Max Speed

//Set the sampling frequency that accomplish the PID requirements
#define SAMPLING_FREQUENCY 1000 //Set value in Hz 


//Do NOT modify this
#define SAMPLING_PERIOD 1.0/SAMPLING_FRECUENCY 
#define SAMPLING_MICROS (unsigned long) SAMPLING_PERIOD * US_IN_SECONDS
//Do NOT modify this



//Arduino pinout definitions (check above comments for explanation)
#define SENSOR_PIN A0
#define FAN_PIN    13 


//Define your set-point here. Can be modified anytime later
float setP = 22.0; //22 Celsius degrees sounds nice for a starting point.
                   //Notice that set-point must be smaller than ambient temperature
                   //as there is no heating device in this system.


//PID object creation and initialization
Pid controller(KP, KI, KD, MIN_OUT, MAX_OUT);


void setup(void){
  //Establishing PID set-point value
  controller.pidSetPoint(setP);

  //Add yor first-run setup code here if needed
  //GPIO Initialization
  pinMode(SENSOR_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);

}


//Put your sensor measurement code/driver here
float readSensor(void){
  //Compute sensor value and return it
  float temp = analogRead(SENSOR_PIN);
  temp = temp * 25 / 100; //Analog voltage to temperature (celsius) conversion
  return temp; 
}

void updateActuator(float output){
  //Put your actuator driver code here
  //Fan is only one direction, so only positive values (between 0 and 255) are valid
  analogWrite(FAN_PIN, output); 
}

//Main loop
void loop(void){
  long lastTime;
  long currentTime = lastTime;
  float myOutput; //Output variable to control actuator
  float myFeedback; //Feedback variable with sensor's measurement
  
  //Read sensor and store value in "myFeedback" variable
  myFeedback = readSensor();


  //Update output value and feed PID for next update
  myOutput = controller.pidUpdate(myFeedback);


  //Pause without delay: better accuracy
  do{
      currentTime = micros();
  }while((currentTime - lastTime) < SAMPLING_MICROS);

  //Update actuator output value with "myOutput" variable
  updateActuator(myOutput);
  
  lastTime = micros(); //Update last computed time for next loop
}
