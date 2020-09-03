#include <Wire.h> //Este Master Reader es solamente para prueba de recepcción de datos.
  int iic_pack;
  byte data[8];
  int i=0;
  int PRESION, FLUJO, VOLUMEN;
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start Serial for output
}

void loop()
{

  Wire.requestFrom(8, 8);    // request  8bytes from slave device #2
  i=0;
  while(Wire.available())    // slave may send less than requested
  { 
    
    data[i] = Wire.read();
    i++;
  }
  Serial.print("\n");
    PRESION =  (data[1] <<8 & 65535) +  (data[2]&255);
    FLUJO = (data[3] <<8 & 65535) +  (data[4]&255);
    VOLUMEN =  (data[5] <<8 & 65535) +  (data[6]&255);
    Serial.print(PRESION);
    Serial.print(",");
    Serial.print(FLUJO);
    //Serial.print("\t");
    //Serial.print(VOLUMEN); 
    Serial.print("\n");
  delay(100);
}
