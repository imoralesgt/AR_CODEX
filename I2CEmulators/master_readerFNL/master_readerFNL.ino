// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>

byte par1 = 14;
byte par2 = 22;
byte par3 = 23;
bool Status = false;
byte BuffR[8];

int contador = 0;

void setPar(){
  Wire.beginTransmission(0x22);
  Wire.write(par1);
  Wire.write(par2);
  Wire.write(par3);
  Wire.endTransmission(0x22);
  par1++;
  par2++;
  par3++;
  Serial.println("Se establecieron los parámetros: ");
  Serial.println(par1);
  Serial.println(par2);
  Serial.println(par3);
  }

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  setPar();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);  // start serial for output
}

void loop()
{
  Serial.print("Buff Recibido es: ");
  Wire.requestFrom(0x22, 8);    // request 8 bytes from slave device #8
  for(int i = 0; i<=7; i++){
    BuffR[i] = Wire.read(); // receive a byte
    Serial.print(BuffR[i]);
    Serial.print(" | ");
  }
  Serial.println();
  Status = Status ^= 0x01;
  digitalWrite(LED_BUILTIN, Status);
  contador++;
  if(contador == 20){
    contador = 0;
    setPar();
    }
  delay(500);
}
