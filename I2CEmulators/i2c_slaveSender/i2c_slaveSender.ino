
#include <Wire.h>

byte iic_pack[8]; //i2c package to be sent.

//Test signals
int state=0xCC;
int sns[3]={0x08AD, 0x00FA, 0x00AA};
int chksum=0x39;

//Packaging function before transfer. 
void pack(int state, int sensors[3], int chksum){
  iic_pack[0]=state & 255; //status flag

  iic_pack[1]=(byte)(sensors[0] >>8 & 255);  //MSB sensor 0
  iic_pack[2]=(byte)(sensors[0] & 255);     //LSB sensor 0

  iic_pack[3]=(byte)(sensors[1]>>8 & 255);  //MSB sensor 1
  iic_pack[4]=(byte)(sensors[1] & 255);     //LSB sensor 1

  iic_pack[5]=(byte)(sensors[2]>>8 & 255);  //MSB sensor 2
  iic_pack[6]=(byte)(sensors[2] & 255);     //LSB sensor 2

  iic_pack[7]=chksum & 255;
}

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2 //
  Wire.onRequest(requestEvent); // register event
  Serial.begin(115200);
}

void loop()
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
    Serial.print("Se  realizó el envío del paquete");
    pack(state, sns, chksum);
    Wire.write(iic_pack, 8);
////If previous doesn't work try this.
//  for(int i=0; i<8; i++){
//    Wire.write(iic_pack[i]);
//  }
}
