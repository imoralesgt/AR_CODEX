#include "arcontrol.h"
#include "pinout.h"
#include "globals.h"
#include "Pid.h"


/*
==========================================================================================================
- Inspiration and expiration slope computation methods done
- Initialization (at constructor) of PID & Motor variables done
- Preliminar version of control strategy done (controlFlow method)

ToDo:
    - Create interconnection methods for external modules
    - Instantiate modules into top module (Control.ino)
    - Interconnect modules into top module (Control.ino)
    - Test control system
==========================================================================================================
*/






//PID Instantiation
Pid pp(KP, KI, KD, MOTOR_MIN_OUT, MOTOR_MAX_OUT);

/*
======================
Constructor/Destructor
======================
*/

arcontrol::arcontrol(){
    this -> __resetInitParametersFlag(); //IRM initialization from GUI not done yet.
    this -> controlSetPoint = 0.0; //IRM Airflow set-point value

}

//IRM Destructor: do nothing
arcontrol::~arcontrol(){
    ;
}




/*
==============
Public methods
==============
*/

//IRM Gets init parameters from GUI I2C controller block, which are set as working set-points.
//Returns 0 if everything ok. Call this method from an external module function
int arcontrol::setInitParameters(float pressure, float minVol, float maxVol, float rpm, float ieRatio){
    this -> __setSpPressure(pressure);
    this -> __setSpRPM(rpm);
    this -> __setSpIeRatio(ieRatio);

    this -> __setSpMinVol(minVol);
    this -> __setSpMaxVol(maxVol);

    this -> __setInitParametersFlag(); //Initial parameters already received!


    //Setup initial motor & PID conditions
    this -> currentCycleSlope = __computeISlope(this->getSpRPM(), this->getSpIeRatio(), this->getSpMinVol(), this->getSpMaxVol());
    this->setCurrentCycleVolume(0); //No air hasn't been pushed yet
    this->currentDirection = INSP;
    pp.resetIDvalues(); 
    
    return 0;
}

void arcontrol::updateSetPoint(float sp){
    pp.pidSetPoint(sp);
}


/*
    Estrategia de control:

    Ciclo inicial:
    - Asegurarse que ambú esté presionado 0%
    - Mover motor (lentamente) hasta alcanzar volumen mínimo deseado (tomando como base medidas de flujo/caudal (R))
        ~ Volumen = Caudal * Tiempo
    - Iniciar proceso cíclico contorlado por PID, supervisando no exceder el límite de presión en ningún instante

    Proceso cíclico:
    Calcular el caudal necesario para lograr enviar al paciente el volumen requerido a la tasa de respiraciones
    por minuto, cumpliendo también con la tasa de inspiración y expiración.

    La variable a controlar es el flujo. Las pendientes (Delta V / Delta t) se calculan en base a los siguientes requisitos:
        - Respiraciones por minuto
        - Relación I:E
        - Delta Volumen (Volumen Mínimo Ambu, Volumen Máximo Ambú)


*/


float arcontrol::controlFlow(float currentFlow, float currentPressure, float currentRPM, float currentIeRatio){
    float newOutput; //Current output
    float accumulatedCycleVolume;
    if(this->currentDirection == INSP){ //If pushing air into patient's lungs

        if(currentPressure > this->getSpPressure()){ //If max. expected pressure is detected
            this->__reduceMaxPIDOut(pp.getMaxOut()); //Gradually reduce motor output speed (inspiration only)
        }

       
        //Compute current cycle accumulated volume
        accumulatedCycleVolume = this->computeCurrentCycleVolume(currentFlow);


        //If maxvol hasn't been reached yet, keep pushing ambu
        if(accumulatedCycleVolume < this->getSpMaxVol()){
            
            newOutput = pp.pidUpdate(currentFlow);

        }else{
            //Otherwise, stop motor and change currentDirection to EXPIRATION
            this->setCurrentCycleVolume(this->getSpMaxVol()); //Now start decreasing volume next clock cycle
            this->currentDirection = EXPI;
            pp.setNewMaxOutput(MOTOR_MAX_OUT); //Reset max motor speed to default value 
            pp.resetIDvalues(); //Reset PID accumulated values

            //Compute new negative PID slope for next respiration cycle (expiration)
            this->currentCycleSlope = this -> __computeESlope(this->getSpRPM(), this->getSpIeRatio(), this->getSpMinVol(), this->getSpMaxVol());
            newOutput = 0; //Momentaneusly pause motor to start direction reversion
        }

    }else if(this->currentDirection == EXPI){ //If current direction is expiration (pulling ambu out)
        //Limit switches MUST be checked in Motor Control Module. Despite of the value sent from this module,
        //Motor Control Module must check switches before acting.
        accumulatedCycleVolume = this->computeCurrentCycleVolume((currentFlow)*(-1)); //Negative direction

        //If minvol hasn't been reached yet, keep pulling ambu out
        if(accumulatedCycleVolume > this->getSpMinVol()){            
            newOutput = pp.pidUpdate(currentFlow);         
        }else{
            //Compute new set point (flow), according to volume, IE, RPM, parameters sent from GUI
            //Compute new positive PID slope for next respiration cycle (inspiration)
            this->currentCycleSlope = this -> __computeISlope(this->getSpRPM(), this->getSpIeRatio(), this->getSpMinVol(), this->getSpMaxVol());

            this->setCurrentCycleVolume(this->getSpMinVol()); //Now strat increasing volume again on next cycle
            this->currentDirection = INSP;
            pp.resetIDvalues(); //Reset prior accumulated PID values
            newOutput = 0; //Momentaneusly pause motor to start direction reversion
        }



    }else{ //No other states have been planned. If entering an invalid state, just shut motors off.
        pp.setNewMaxOutput(0);
        pp.setNewMinOutput(0);
        return 0; //Motors must be stopped
    } 

    return newOutput; //Return new motor speed value

    

}



// Compute total cycle volume, based on flow
float arcontrol::computeCurrentCycleVolume(float currentFlow){
    float lastVol = this->getCurrentCycleVolume();
    return lastVol + (DT*currentFlow);
}

// Public setters and getters
float arcontrol::getCurrentSetPoint(){
    return pp.getSetPoint();
}


//Get current cycle volume
float arcontrol::getCurrentCycleVolume(){
    return this->currentCycleVolume;
}

//Set current cycle volume
float arcontrol::setCurrentCycleVolume(float newVolume){
    this->currentCycleVolume = newVolume;
}



/*
===============
Private methods
===============
*/

float arcontrol::__computeRespirationPeriod(float rpm){
    return (60.0 / rpm); //60 seconds per minute
}


float arcontrol::__computeIDuration(float rpm, float ieRatio){
    float tResp = this -> __computeRespirationPeriod(rpm); //Compute respiration period in seconds
    float iDuration = tResp*ieRatio/(1 + ieRatio);  //Inspiration duration (in SECONDS)
    return iDuration;
}


float arcontrol::__computeEDuration(float rpm, float ieRatio){
    float tResp = this -> __computeRespirationPeriod(rpm); //Compute respiration period in seconds
    float eDuration = tResp/(1 + ieRatio);  //Expiration duration (in SECONDS)
}


//Compute Inspiration rate (slope). Dependent variable: Volume, Independent var: time (inspiration time) 
//This will help to set Motor Speed while pushing ambu. No further Calibration required
float arcontrol::__computeISlope(float rpm, float ieRatio, float minVol, float maxVol){
    float iDuration = this -> __computeIDuration(rpm, ieRatio);
    float deltaVol  = maxVol - minVol; //Inspiration volume delta (in cubic meters)
    return deltaVol/iDuration;
}


//Compute espiration rate (slope). Dependent variable: Volume, Independent var: time (expiration time) 
//This will help to set Motor Speed while "pulling out" ambu. No further Calibration required
//Negative output expected
float arcontrol::__computeESlope(float rpm, float ieRatio, float minVol, float maxVol){
    float eDuration = this -> __computeEDuration(rpm, ieRatio);
    float deltaVol  = minVol - maxVol; //Expiration volume delta (in cubic meters)
    return deltaVol/eDuration; 
}

//Reduce max output value if maximum pressure is exceeded
void arcontrol::__reduceMaxPIDOut(float currentMax){
    //OUTPUT_REDUCTION_FACTOR can be changed in "globals.h"

    //Min value untouched, as it's only used during expiration
    float newMax = (float) currentMax * OUTPUT_REDUCTION_FACTOR; 

    pp.setNewMaxOutput(newMax);

}



//Set max working pressure value, to protect patient's lungs
void arcontrol::__setSpPressure(float press){
    this -> spPressure = press;
}

//Set min opetariontal volume set-point, to avoid negative pressure
void arcontrol::__setSpMinVol(float minVol){
    this -> spVolMin = minVol;
}

//Set max opetariontal volume set-point, to protect patient's lungs
void arcontrol::__setSpMaxVol(float maxVol){
    this -> spVolMax = maxVol;
}

//Set respirations per minute set-point (respiration period)
void arcontrol::__setSpRPM(float rpm){
    this -> spRPM = rpm;
}

//Set Inspiration:Espiration ratio (respiration duty cycle)
void arcontrol::__setSpIeRatio(float ie){
    this -> spIEratio = ie;
}

//Set (1) Init Parameters Flag
void arcontrol::__setInitParametersFlag(){
    this -> initParametersReceived = 1;
}

//Reset (0) Init Parameters Flag
void arcontrol::__resetInitParametersFlag(){
    this -> initParametersReceived = 0;
}


//Getters and setters

//Get Init parameters flag
int arcontrol::__getInitParametersFlag(){
    return this -> initParametersReceived;
}

//Get max working pressure value, to protect patient's lungs
float arcontrol::getSpPressure(){
    return this -> spPressure;
}

//Get min opetariontal volume set-point, to avoid negative pressure
float arcontrol::getSpMinVol(){
    return this -> spVolMin;
}

//Get max opetariontal volume set-point, to protect patient's lungs
float arcontrol::getSpMaxVol(){
    return this -> spVolMax;
}

//Get respirations per minute set-point (respiration period)
float arcontrol::getSpRPM(){
    return this -> spRPM;
}

//Get Inspiration:Espiration ratio (respiration duty cycle)
float arcontrol::getSpIeRatio(){
    return this -> spIEratio;
}