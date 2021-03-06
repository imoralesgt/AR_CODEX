#ifndef MOTORCONTROLTEST_H
#define MOTORCONTROLTEST_H

extern volatile int motorCurrentDir;

void motorSetDirection(int direction);
void motorSetSpeed(int speed);
//void motorSetSpeed2(int index, int speed);
void motorEnableSteppers(void);
void motorDisableSteppers(void);
int motorComputeTimerFromSpeed(int speed);



#endif