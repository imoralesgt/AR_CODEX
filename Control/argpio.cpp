#include "argpio.h"

argpio::argpio(){
    ;
}

argpio::~argpio(){
    ;
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