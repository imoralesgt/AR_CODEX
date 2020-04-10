/*
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


#include "Pid.h"
#include <time.h>

//Set your own PID constants here
#define KP 1.0
#define KI 1.0
#define KD 1.0

//Set the actuator's output limits here
#define MIN_OUT -255
#define MAX_OUT 255


//Define your set-point here. Can be modified anytime later
float setP = 5.0;


//PID object creation and initialization
Pid controller(KP, KI, KD, MIN_OUT, MAX_OUT);


void setup(void){
  //Establishing PID set-point value
  controller.pidSetPoint(setP);

  //Add yor first-run setup code here if needed

}


//Put your sensor measurement code/driver here
float readSensor(void){
  //Return your sensor value (change the constant "1" value set here)
  return 1; 
}

void updateActuator(float output){
  //Put your actuator driver code here
  ; 
}

//Main loop
void loop(void){
  float myOutput; //Output variable to control actuator
  float myFeedback; //Feedback variable with sensor's measurement
  
  //Read sensor and store value in "myFeedback" variable
  myFeedback = readSensor();


  //Update output value and feed PID for next update
  myOutput = controller.pidUpdate(myFeedback);


  //Update actuator output value with "myOutput" variable
  updateActuator(myOutput);
}



//Workaround for multiplatform compilation. Don't modifiy this code block
#ifndef ARDUINO_H
  int main(void){
    //Run initializaiton
    setup();
    while(1){
      loop();
    }
    return 0;
  }
#endif
