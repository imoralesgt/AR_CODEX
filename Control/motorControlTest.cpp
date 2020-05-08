#include "motorControlTest.h"
#include "pinout.h"
#include "globals.h"
#include "Arduino.h"

volatile int intToggle2 = 0;

volatile int steppingEnabled;

void motorSetDirection(int direction){
	digitalWrite(PIN_DIRECTION, direction);
}

void motorSetSpeed(int speed){
	motorEnableSteppers();
	if (speed < (-1)*(SPEED_HYSTERESIS)){
		motorSetDirection(1);
		//Serial.println("BKWRDS");
	}else if(speed > SPEED_HYSTERESIS){
		motorSetDirection(0);
		//Serial.println("FRWRD");
	}else{
		motorSetDirection(0);
		motorDisableSteppers();
		Serial.println("STOP");
	}
	OCR1A = motorComputeTimerFromSpeed(speed);
}

// void motorSetSpeed2(int index, int speed){
// 	motorEnableSteppers();
// 	if (speed < (-1)*(SPEED_HYSTERESIS)){
// 		motorSetDirection(1);
// 	}else if(speed > SPEED_HYSTERESIS){
// 		motorSetDirection(0);
// 	}else{
// 		motorDisableSteppers();
// 	}
// 	OCR1A = motorComputeTimerFromSpeed(speed);
// }


void motorEnableSteppers(void){
	steppingEnabled = 1;
}

void motorDisableSteppers(void){
	steppingEnabled = 0;
}


int motorComputeTimerFromSpeed(int speed){
	const int MIN_TIMER = 199;
	const int MAX_TIMER = 999;
	int computedSpeed;

	//Serial.println(speed);

	Serial.print("SPD: "); Serial.println(speed);

	if(speed < 0){
		speed = (speed)*(-1);
		computedSpeed =  (int)map(speed, 0, (-1)*(MOTOR_MIN_OUT), MAX_TIMER, MIN_TIMER);
	}else{
		computedSpeed = (int)map(speed, 0, MOTOR_MAX_OUT, MAX_TIMER, MIN_TIMER);
	}

	
	//Serial.print("MSPD: "); Serial.println(computedSpeed);

	return computedSpeed;
}


ISR(TIMER1_COMPA_vect){
	intToggle2 ^= 1;
	digitalWrite(PIN_MOTOR2, (intToggle2&steppingEnabled));
}
