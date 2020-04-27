#include "arcontrol.h"
#include "globals.h"
#include "pinout.h"

arcontrol controlador;

volatile unsigned int count = 0;
int currentState = 0;
int printOk = 0;

int intToggle = 0;
int flagToggle = 0;
volatile int timerDone = 0; //MUST BE VOLATILE TO ALLOW DYNAMIC IN-ISR MODIFICATION

int intToggle2 = 0;

float myOutput;
float myFeedback;


unsigned long pidPs = 0;


void setup(){

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, 0);
	pinMode(PIN_MOTOR0, OUTPUT);
	digitalWrite(PIN_MOTOR0, 0);

	pinMode(PIN_MOTOR1, OUTPUT);
	digitalWrite(PIN_MOTOR1, 0);

	pinMode(PIN_MOTOR2, OUTPUT);
	digitalWrite(PIN_MOTOR2, 0);

	/*
	=============
	TIMER 1 SETUP
	=============
	*/
	//General interrupts enable bit clear (Status Register)
	SREG &= ~0x80;

	//Disable power-saving feature (enables Timer 1)
	PRR &= ~0x80;

	//Compare A interrupt enable
	TIMSK1 |= 0x02; 	

	//Clear timer value on compare match mode (CTC mode)	
	TCCR1A  = 0x00;
	TCCR1B |= 0x08;

	//Prescaler /8 clk source (higher resolution 16-bit timer)
	TCCR1B |= 0x02;

	//Comparator A register limit (overflow value)
	//Comparator set to 249 counts (250 - 1)
	OCR1A = 249;

	/*
	OCR1AH = 0x07; //High byte
	TEMP = 0x07;
	OCR1AL = 0xCF; //Low byte
	*/

	

	//General interrupt enable bit set (Status Register)
	//SREG |= 0x80;	 //Won't enable here, as Timer 2 setup is next



	/*
	=============
	TIMER 2 SETUP
	=============
	*/

	//General interrupts enable bit clear (Status Register)
	SREG &= ~0x80;

	//Disable power-saving feature (enables Timer 2)
	PRR &= ~0x40;

	//Compare A interrupt enable
	TIMSK2 |= 0x02; 

	//Clear timer value on compare match mode (CTC mode)
	TCCR2A = 0x02;
	TCCR2B &= ~0x08;

	//Prescaler /64 clk source
	TCCR2B |= 0x04;

	//Comparator A register limit (overflow value)
	OCR2A = 249; //250 - 1

	//General interrupt enable bit set (Status Register)
	SREG |= 0x80;

	//62.5 KHz Clk Source for Timer 2
	//250 counts compare match generates interrupt
	//Interrupt rate = 250 Hz

	Serial.begin(115200);

	pinMode(A0, INPUT);

	controlador.setInitParameters(4.0, 100.0, 800.0, 16.5, 0.4);

	//controlador.__reduceMaxPIDOut(255);
}

void loop(){

	digitalWrite(PIN_MOTOR1, flagToggle);
	
	myFeedback = analogRead(A0);
	myOutput = controlador.controlFlow((float)(myFeedback/100.0), 1.8, 16.5, 0.4);
	pidPs++;

	if(currentState && printOk){
		Serial.println(pidPs);
		pidPs = 0;
		printOk ^= printOk;
	}


	//Timer synchronization with Timer 2 ISR
	timerDone = 0;
	while(timerDone < 1){
	 	;
	}

	
}


ISR(TIMER2_COMPA_vect){ //Timer comparison interrupt
	intToggle ^= 1;
	
	digitalWrite(PIN_MOTOR0, intToggle);
	//analogWrite(PIN_MOTOR1, myOutput);
	if(++count == 599/4){ //600 miliseconds interrupt (min inspiration period)
		digitalWrite(LED_BUILTIN, currentState);
		currentState ^= 0x01; //Toggle LED_BUILTIN
		if(currentState){
			printOk ^= 0x01;
		}
		count = 0;
	}

	//Timer synchronization with loop() polling 
	flagToggle ^= 1;
	timerDone++;
}

ISR(TIMER1_COMPA_vect){
	intToggle2 ^= 1;
	digitalWrite(PIN_MOTOR2, intToggle2);
}
