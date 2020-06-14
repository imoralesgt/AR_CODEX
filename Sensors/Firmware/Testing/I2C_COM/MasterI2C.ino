#include <Wire.h> //Este Master Reader es solamente para prueba de recepcción de datos.
  int iic_pack;
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start Serial for output
}

void loop()
{

  Wire.requestFrom(2, 8);    // request  8bytes from slave device #2

  while(Wire.available())    // slave may send less than requested
  { 
    iic_pack = Wire.read();
    Serial.println(iic_pack, HEX);         // print the package in HEX
  }

  delay(500);
}
