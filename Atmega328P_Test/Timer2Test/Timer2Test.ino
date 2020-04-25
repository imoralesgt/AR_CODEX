#include "globals.h"
#include "pinout.h"
#include "Pid.h"

volatile unsigned int cuenta = 0;
bool currentState = false;
int printOk = 0x00;

float myOutput;
float myFeedback;


//Performace measurement
//PID computations per second
unsigned long pidPs = 0;




Pid ledpp(1.0, 0.3, 0.0, 0, 255);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, false);

  pinMode(9, OUTPUT);
  digitalWrite(9, 0);

  //General Interrupts Disable bit (Status Register)
  SREG &= ~0x80; 

  //Compare A interrupt
  TIMSK2 = TIMSK2|0b00000010; //Habilita la interrupcion por overflow

  //Comparator A register value (overflow value)
  OCR2A = 249; //250 - 1 
  
  //Prescaler /64 clk source
  TCCR2B = 0b00000100;

  //General Interrupts Enable bit (Status Register)
  SREG |= 0x80;

  //62.5 KHz Clk Source for Timer 2
  //250 counts overflow to generate interrupt
  //Interrupt rate = 250 Hz


  ledpp.pidSetPoint(5.0);

  Serial.begin(115200);

  pinMode(A0, INPUT);
 

}

void loop() {
 
  myFeedback = analogRead(A0);
  myOutput = ledpp.pidUpdate(myFeedback);
  pidPs++;

  if(currentState && printOk){
    Serial.println(pidPs);
    pidPs = 0;
    printOk ^= printOk;
  }
}

//ISR(TIMER2_OVF_vect){ //No overflow used any more
ISR(TIMER2_COMPA_vect){ //Comparison overflow
    analogWrite(9, myOutput);
    if(++cuenta >= 249){ //1 second interrupt
      digitalWrite(LED_BUILTIN, currentState);
      currentState ^= 0x01; //Toggle LED
      if(currentState){
        printOk ^= 0x01;
      }
      cuenta=0;
    }  
}
