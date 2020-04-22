#include "arcontrol.h"
#include "globals.h"
#include "pinout.h"

arcontrol controlador;

void setup(){
  pinMode(PIN_MOTOR0, OUTPUT);
  controlador.__reduceMaxPIDOut(255);
}

void loop(){
  ;
}
