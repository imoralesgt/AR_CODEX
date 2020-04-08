#include "Pid.h"

// const byte PWM_PIN = 37; //Ventilador
// const byte POTENCIOMETRO = A3; //LM35

// void setup()
// {
  
//   pinMode(PWM_PIN, OUTPUT);
  
//   Serial.begin(115200);
//   pinMode(POTENCIOMETRO, INPUT);
  
//   //Extremadamente importante calibrar adecuadamente los coeficiente
//   pidInit(30, 8, 0, -100, 100); //Coeficientes y limites de integrador
//   pidSetPoint(100); //Temperatura deseada
// }

// void loop()
// {
//   uint16_t temp;
//   int16_t pwmOut;
//   temp = analogRead(POTENCIOMETRO) / 16;
  
//   pwmOut = pidUpdate(temp); //Actualizar el sistema de control
//                             //y obtener nuevo valor

//   analogWrite(PWM_PIN, pwmOut);
  
//   Serial.print("CurrentValue: ");
//   Serial.println(temp);
//   Serial.print("PWMValue: ");
//   Serial.println(pwmOut);
//   Serial.println("");
  
//   delay(100);
  
// }  
