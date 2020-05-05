#include "argpio.h"
#include "pinout.h"
#include "Arduino.h"

argpio::argpio(){
    ;
}

argpio::~argpio(){
    ;
}

void argpio::initIOs(void){
    int i;

    //Initialize motors and motor-related end/start stop switches
    for(i = 0; i < TOTAL_MOTORS; i++){
        this -> pSetup(MOTOR[i], OUTPUT); //Outputs
        this -> pSetup(START_ENDSTOP[i], INPUT_PULLUP); //Inputs
        this -> pSetup(END_ENDSTOP[i], INPUT_PULLUP); //Inputs
    }


}

void argpio::pSetup(uint8_t pin, uint8_t mode){
    pinMode(pin, mode);
}

void argpio::dWrite(uint8_t pin, int value){
    digitalWrite(pin, value);
}


int argpio::dRead(uint8_t pin){
    return digitalRead(pin);
}