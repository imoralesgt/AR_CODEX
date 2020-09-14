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


volatile int flagToggle = 0;
volatile int timerDone = 0; //MUST BE VOLATILE TO ALLOW DYNAMIC IN-ISR MODIFICATION

float myOutput;
float myFeedback;

volatile int myOutputInt;


volatile float sensorsConvertedPressure;
volatile float sensorsConvertedAirFlow;

void setup(){

	Serial.begin(115200);

	gpios.initIOs();

	//LED for debugging only
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, 0);

	//I2C and buffers initialization
	i2cSetup();

	//Wait until first set points arrive from GUI
	while(!guiNewSetPoints){
		;
	}

	digitalWrite(LED_BUILTIN, 1);
	delay(250);
	digitalWrite(LED_BUILTIN, 0);

	Serial.println("Initial set-point values acquired!");


	/*
	=============
	TIMER 1 SETUP (MOTOR CONTROL)
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
	TIMER 2 SETUP (System Tick)
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

	//62.5 KHz Clk Source for Timer 2
	//250 counts compare match generates interrupt
	//Interrupt rate = 250 Hz


	// //Prescaler /64 clk source
	TCCR2B |= 0x04;


	//Comparator A register limit (overflow value)
	OCR2A = 249; //250 - 1

	//Prescaler /256 clk source //IVAN 125 Hz
	// TCCR2B |= 0x06;

	//Comparator A register limit (overflow value)
	// OCR2A = 124; //125 - 1

	//General interrupt enable bit set (Status Register)
	SREG |= 0x80;


	Serial.println("AR_CODEX");

	//IVAN Temporarily disabled parameters gathering from GUI.
	//controlador.setInitParameters(i2c_receivedParam[1]*GUI_MAX_PRESSURE, 0.0, i2c_receivedParam[2]*GUI_MAX_VOLUME_TO_MILILITERS, i2c_receivedParam[0]*GUI_RESPIRATION_RATIO, DEFAULT_IE_RATIO*GUI_IE_RATIO_NORMALIZATION);

	// controlador.setInitParameters(30.0, 0.0, 250.0, 20.0, 0.4); //IVAN Default set points while debugging
	// controlador.setInitParameters(30.0, 0.0, 400.0, 25.0, 0.5); //IVAN Default set points while debugging
	controlador.setInitParameters(30.0, 0.0, 350.0, 10.0, 0.5); //IVAN Default set points while debugging

	controlador.goHome();
	

}

void loop(){

	//Update control parameters if new values arrive from GUI
	if(guiNewSetPoints){
		//IVAN Temporarily disabled parameters update
		// controlador.updateControlParameters((float) i2c_receivedParam[1], 0, i2c_receivedParam[2], i2c_receivedParam[0], DEFAULT_IE_RATIO);
		// guiNewSetPoints = 0;
	}

	
	sensorsConvertedPressure = ((float)(sensData[0])+PRESS_OFFSET)*PASCALS_TO_CMH20; 
	sensorsConvertedAirFlow = (float)sensData[1]*MILILITERS_PER_MIN_TO_MILILITERS_PER_SECOND;

	//Updating real time data coming from sensors and applying conversion factors (more info at globals.h file)
	myOutput = controlador.controlFlow(sensorsConvertedAirFlow, sensorsConvertedPressure);
	myOutputInt = (int) myOutput;
	motorSetSpeed(myOutputInt);
	
	
	
	#ifdef DEBUG_MODE
	
		Serial.print("P/F: ");
		Serial.print(sensorsConvertedPressure);
		Serial.print(" / ");
		Serial.println(sensorsConvertedAirFlow);
		
		Serial.print("SPD: "); Serial.println(myOutputInt);

	#endif

	i2c_Request(8); //Request Sensor Data via Software I2C Master Interface
 
	//Timer synchronization with Timer 2 ISR
	timerDone = 0;
	flagToggle ^= 1;
	digitalWrite(DEBUG_AMBU_DIRECTION, flagToggle); //Main loop synchronization signal with interrupts

	while(!timerDone){ //Interrupts for 250 Hz synchronization
	 	;
	}

}


ISR(TIMER2_COMPA_vect){ //Timer comparison interrupt
	#ifdef DEBUG_MODE
		if(++count == 599/4){ //600 miliseconds interrupt (min inspiration period)
		//if(++count == 999/4){ //1000 miliseconds interrupt 
			digitalWrite(LED_BUILTIN, currentState);
			currentState ^= 0x01; //Toggle LED_BUILTIN
			count = 0;
		}
	#endif
	

	//While homing
	if(controlador.motorsHomed < 1){
		motorSetSpeed(MOTOR_MIN_OUT);
		//digitalWrite(DEBUG_AMBU_DIRECTION, 1);
	}

	//Timer synchronization with loop() polling 
	timerDone = 1;

}
