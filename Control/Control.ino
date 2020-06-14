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
//int currentSpeed = -20;
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


volatile float sensorsConvertedPressure;
volatile float sensorsConvertedAirFlow;

void setup(){

	gpios.initIOs();

	//LED for debugging only
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, 0);

	//I2C and buffers initialization
	i2cSetup();

	//Wait until first set points arrive from GUI
	while(!guiNewSetPoints)
		;




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

	Serial.println("AR_CODEX");

	
	controlador.setInitParameters(i2c_receivedParam[1]*GUI_MAX_PRESSURE, 0.0, i2c_receivedParam[2]*GUI_MAX_VOLUME_TO_MILILITERS, i2c_receivedParam[0]*GUI_RESPIRATION_RATIO, DEFAULT_IE_RATIO*GUI_IE_RATIO_NORMALIZATION);

	//controlador.setInitParameters(30.0, 0.0, 600.0, 15.0, 0.3);
	controlador.goHome();
	
	

}

void loop(){

	digitalWrite(DEBUG_AMBU_DIRECTION, flagToggle); //Main loop synchronization signal with interrupts

	//myFeedback = 932;


	//Update control parameters if new values arrive from GUI
	if(guiNewSetPoints){
		controlador.updateControlParameters((float) i2c_receivedParam[1], 0, i2c_receivedParam[2], i2c_receivedParam[0], DEFAULT_IE_RATIO);
		guiNewSetPoints = 0;
	}

	
	sensorsConvertedPressure = (float)sensData[0]*DECIPASCALS_TO_CMH20; 
	sensorsConvertedAirFlow  = (float)sensData[1]*DECILITERS_PER_MIN_TO_MILILITERS_PER_MINUTE;

	//Updating real time data coming from sensors and applying conversion factors (more info at globals.h file)
	myOutput = controlador.controlFlow(sensorsConvertedAirFlow, sensorsConvertedPressure);
	motorSetSpeed(myOutput);
	//Serial.print("SPD: "); Serial.println(myOutput);
	pidPs++;

	if(currentState && printOk){
		//Serial.println(pidPs);
		pidPs = 0;
		printOk ^= printOk;
	}

	//digitalWrite(DEBUG_AMBU_DIRECTION, controlador.currentDirection);

	i2c_Request(8); //Request Sensor Data via Software I2C Master Interface

	Serial.println("P,F: ");
	Serial.println(sensorsConvertedPressure);
	Serial.println(sensorsConvertedAirFlow);
 
	//Timer synchronization with Timer 2 ISR
	timerDone = 0;
	while(timerDone < 1){
	 	;
	}
	
}


ISR(TIMER2_COMPA_vect){ //Timer comparison interrupt
	intToggle ^= 1;
	
	//digitalWrite(DEBUG_AMBU_DIRECTION, intToggle); //We already know interrupts work fine, commenting this line out
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
