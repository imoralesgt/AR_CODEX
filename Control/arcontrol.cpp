#include "arcontrol.h"


/*
======================
Constructor/Destructor
======================
*/

arcontrol::arcontrol(){
    this -> __resetInitParametersFlag(); //IRM initialization from GUI not done yet.

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

//IRM Gets init parameters from GUI I2C controller block, which are set as working set-points. Returns 0 if everything ok
//Call this method from an external function
int arcontrol::setInitParameters(float pressure, float minVol, float maxVol, float rpm, float ieRatio){
    this -> __setSpPressure(pressure);
    this -> __setSpMinVol(minVol);
    this -> __setSpMaxVol(maxVol);
    this -> __setSpRPM(rpm);
    this -> __setSpIeRatio(ieRatio);

    this -> __setInitParametersFlag(); //Initial parameters already received!
    
    return 0;
}







/*
===============
Private methods
===============
*/

float __computeRespirationPeriod(float rpm){
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
//This will help to set Motor Speed while pushing ambu. Further Calibration required
float arcontrol::__computeISlope(float rpm, float ieRatio, float minVol, float maxVol){
    float iDuration = this -> __computeIDuration(rpm, ieRatio);
    float deltaVol  = maxVol - minVol; //Inspiration volume delta (in cubic meters)
    return deltaVol/iDuration;
}


//Compute espiration rate (slope). Dependent variable: Volume, Independent var: time (expiration time) 
//This will help to set Motor Speed while "pulling out" ambu. Further Calibration required
float arcontrol::__computeESlope(float rpm, float ieRatio, float minVol, float maxVol){
    float eDuration = this -> __computeEDuration(rpm, ieRatio);
    float deltaVol  = minVol - maxVol; //Expiration volume delta (in cubic meters)
    return deltaVol/eDuration;
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


/*
==========================================================================================================
INSPIRATION AND EXPIRATION SLOPES COMPUTED SUCCESFULLY.

Slope values match with Inspiration and Expiration Flows

ToDo:
    - Setup Control System
        ~ Continuously check pressure value and reduce output value if limit is exceeded
        ~ Output value should be set in order to match Sensor Flow measurements with computed Slopes (PID)
==========================================================================================================
*/






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



//Get Init parameters flag
int arcontrol::__getInitParametersFlag(){
    return this -> initParametersReceived;
}

//Get max working pressure value, to protect patient's lungs
float arcontrol::__getSpPressure(){
    return this -> spPressure;
}

//Get min opetariontal volume set-point, to avoid negative pressure
float arcontrol::__getSpMinVol(){
    return this -> spVolMin;
}

//Get max opetariontal volume set-point, to protect patient's lungs
float arcontrol::__getSpMaxVol(){
    return this -> spVolMax;
}

//Get respirations per minute set-point (respiration period)
float arcontrol::__getSpRPM(){
    return this -> spRPM;
}

//Get Inspiration:Espiration ratio (respiration duty cycle)
float arcontrol::__getSpIeRatio(){
    return this -> spIEratio;
}