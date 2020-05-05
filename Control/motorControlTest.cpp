#include "motorControlTest.h"
#include "pinout.h"
#include "globals.h"
#include "Arduino.h"

volatile int intToggle2 = 0;

int steppingEnabled = 0;

void motorSetDirection(int direction){
	digitalWrite(PIN_DIRECTION, direction);
}

void motorSetSpeed(int speed){
	motorEnableSteppers();
	if (speed < 0){
		motorSetDirection(1);
	}else if(speed > 0){
		motorSetDirection(0);
	}else{
		motorDisableSteppers();
	}
	OCR1A = motorComputeTimerFromSpeed(speed);
}


void motorEnableSteppers(void){
	steppingEnabled = 1;
}

void motorDisableSteppers(void){
	steppingEnabled = 0;
}


int motorComputeTimerFromSpeed(int speed){
	const int MIN_TIMER = 49;
	const int MAX_TIMER = 249;

	return map(speed, MOTOR_MIN_OUT, MOTOR_MAX_OUT, MAX_TIMER, MIN_TIMER);
}


ISR(TIMER1_COMPA_vect){
	intToggle2 ^= 1;
	digitalWrite(PIN_MOTOR2, (intToggle2&steppingEnabled));
}
