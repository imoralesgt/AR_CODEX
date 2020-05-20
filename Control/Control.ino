#include "arcontrol.h"
#include "pinout.h"
#include "motorControlTest.h"
#include "argpio.h"
#include "i2cComms.h"


/*
=================================================================
ToDo:
	- Wrappers para interacción entre módulos
	- Establecer pines (en pinout.h) para funciones específicas
	- Actualizar set points cuando vengan cambios desde la GUI

=================================================================
*/


//MOTOR TEST VARIABLES - MUST BE DELETED LATER
int currentSpeed = -20;
//MOTOR TEST VARIABLES - MUST BE DELETED LATER


arcontrol controlador;
argpio gpios;

volatile unsigned int count = 0;
volatile int currentState = 0;
volatile int printOk = 0;

volatile int intToggle = 0;
volatile int flagToggle = 0;
volatile int timerDone = 0; //MUST BE VOLATILE TO ALLOW DYNAMIC IN-ISR MODIFICATION

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

	pinMode(DEBUG_AMBU_DIRECTION, OUTPUT);
	digitalWrite(DEBUG_AMBU_DIRECTION, 0);

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
	//TCCR1B |= 0x02;
	//Arduino has already set up a prescaler value for Timer 0 (shared with Timer 1 prescaler)

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

	//I2C and buffers initialization
	i2cSetup();



	gpios.initIOs();

	Serial.begin(115200);

	Serial.println("AR_CODEX");

	pinMode(A0, INPUT);


	//Wait until first set points arrive from GUI
	while(!guiNewSetPoints)
		;


	
	controlador.setInitParameters(i2c_receivedParam[1], 0.0, i2c_receivedParam[2], i2c_receivedParam[0], DEFAULT_IE_RATIO);

	controlador.goHome();
	
	

}

void loop(){

	digitalWrite(PIN_MOTOR1, flagToggle);
	
	myFeedback = analogRead(A0);
	//myFeedback = 932;


	//Update control parameters if new values arrive from GUI
	if(guiNewSetPoints){
		controlador.updateControlParameters((float) i2c_receivedParam[1], 0, i2c_receivedParam[2], i2c_receivedParam[0], DEFAULT_IE_RATIO);
		guiNewSetPoints = 0;
	}


	//myOutput = controlador.controlFlow((float)(myFeedback), 1.8);
	myOutput = controlador.controlFlow((float)sensData[2], (float)sensData[0]);
	motorSetSpeed(myOutput);
	//Serial.print("SPD: "); Serial.println(myOutput);
	pidPs++;

	if(currentState && printOk){
		//Serial.println(pidPs);
		pidPs = 0;
		printOk ^= printOk;
	}

	

	digitalWrite(DEBUG_AMBU_DIRECTION, controlador.currentDirection);

	i2c_Request(8); //Request Sensor Data via Software I2C Master Interface

	Serial.println("P,V,F: ");
	Serial.println(sensData[0]);
	Serial.println(sensData[1]);
	Serial.println(sensData[2]);
 
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
	//if(++count == 999/4){ //1000 miliseconds interrupt 
		digitalWrite(LED_BUILTIN, currentState);
		currentState ^= 0x01; //Toggle LED_BUILTIN
		if(currentState){
			printOk ^= 0x01;
		}
		count = 0;





		//MOTOR TEST CODE - MUST BE DELETED LATER
		//currentSpeed += 5;
		//if (currentSpeed >= MOTOR_MAX_OUT){
		//	currentSpeed = MOTOR_MIN_OUT;
		//}
		//motorSetSpeed(currentSpeed);
		//MOTOR TEST CODE - MUST BE DELETED LATER





	}

	//While homing
	if(controlador.motorsHomed < 1){
		motorSetSpeed(MOTOR_MIN_OUT);
		digitalWrite(DEBUG_AMBU_DIRECTION, 1);
	}


	//Timer synchronization with loop() polling 
	flagToggle ^= 1;
	timerDone = 1;

}

