#include "arcontrol.h"
#include "globals.h"
#include "pinout.h"

arcontrol controlador;

volatile unsigned int count = 0;
int currentState = 0;
int printOk = 0;

float myOutput;
float myFeedback;


unsigned long pidPs = 0;


void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  pinMode(PIN_MOTOR0, OUTPUT);
  digitalWrite(PIN_MOTOR0, 0);

  //General interrupts enable bit clear (Status Register)
  SREG &= ~0x80;

  //Compare A interrupt enable
  TIMSK2 |= 0x02; 

  //Comparator A register comparator limit (overflow value)
  OCR2A = 249; //250 - 1

  //Prescaler /64 clk source
  OCR2A = 0x04;

  //General interrupt enable bit set (Status Register)
  SREG |= 0x80;

  //62.5 KHz Clk Source for Timer 2
  //250 counts compare overflow generates interrupt
  //Interrupt rate = 250 Hz

  Serial.begin(115200);

  pinMode(A0, INPUT);

  controlador.setInitParameters(4.0, 100.0, 800.0, 16.5, 0.4);

  //controlador.__reduceMaxPIDOut(255);
}

void loop(){
  myFeedback = analogRead(A0);
  myOutput = controlador.controlFlow((float)(myFeedback/100.0), 1.8, 16.5, 0.4);
  pidPs++;

  if(currentState && printOk){
    Serial.println(pidPs);
    pidPs = 0;
    printOk ^= printOk;
  }
}


ISR(TIMER2_COMPA_vect){ //Timer comparison interrupt
  if(++count == 249){ //1 second interrupt 
    digitalWrite(LED_BUILTIN, currentState);
    currentState ^= 0x01; //Toggle LED_BUILTIN
    if(currentState){
      printOk ^= 0x01;
    }
    count = 0;
  }
}