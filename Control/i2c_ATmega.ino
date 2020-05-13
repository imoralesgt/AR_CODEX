
/// I2C SOFTWARE
#define I2C_TIMEOUT 1000
#define I2C_PULLUP 1
#define SDA_PORT PORTC
#define SDA_PIN 2 // = A2
#define SCL_PORT PORTC
#define SCL_PIN 3 // = A3
#include <SoftI2CMaster.h>      // Yes, defines before calling this function, it's a requirement of the library.
#include <Wire.h>
/// GENERAL
#define SLAVE_ADDRESS 0x22
#define SENS_ADDRESS 0x08
#define i2c_SENS_DATA_SIZE 8   // Data size from SensorsData.
#define i2c_MAX_PARAM 3   // ¿? Number of Bytes that are going to be sent from GUI.
#define NUM_OF_SENSORS 3



//---------- I2C GLOBLAL VARIABLES ------------
// All the pointer variables are pointing to the base address of the arrays, the [0] position.
byte i2c_sensData[i2c_SENS_DATA_SIZE];      // In i2c_sensData remains the bytes received by the i2c interface.
byte i2c_sensData2[i2c_SENS_DATA_SIZE];     // In i2c_sensData2 remains the bytes copied from i2c_sensData when this bytes are completely received and checked.
byte *i2c_buffer1 = i2c_sensData;     // Input buffer.
byte *i2c_buffer2 = i2c_sensData2;    // Output buffer.
int sensData[NUM_OF_SENSORS];         // In sensData Remains the last three principal values obtained by the sensors, these are int-type and are obtained by the corresponding two bytes in the transmission.
int *pnt_sensData = sensData;         // pnt_sensData points to the sensData vector whith the control variables.
byte i2c_receivedParam[i2c_MAX_PARAM]; // This array contains the Set-point parameters received from GUI.
byte *pnt_parameters = i2c_receivedParam;



// Request data from sensors by the master-mode i2c (SOFTWARE INTERFACE). NumBytes is the # of bytes to be read from the line.
void i2c_Request(int NumBytes){
  i2c_start(SENS_ADDRESS);
  i2c_rep_start((SENS_ADDRESS<<1)|I2C_READ);
  for(int i=0; i<=(NumBytes)-2; i++){
      *(i2c_buffer1+i) = i2c_read(false);
      Serial.print(*(i2c_buffer1+i));
      Serial.print(" | ");
    }
  //Serial.println(i2c_buffer1);
  *(i2c_buffer1 + (NumBytes-1)) = i2c_read(true);
  Serial.println(*(i2c_buffer1+(NumBytes-1)));
  i2c_stop();
  //Go to check if the Data is received correctly.
  i2c_checkData();
}



// This functions check the Checksum Byte in the received data by sensors.
void i2c_checkData() {
  byte check = 0;
  for(int i = 0; i<=6; i++){
    check = check ^ *(i2c_buffer1+i);  
    }
  Serial.println(check);
  if(check == *(i2c_buffer1+7)){      // check is turned into a consecutive XOR from 7 first bytes.
    i2c_buffer_CP();                   //if it's correct, continue to copy and bring the data to control.
    i2c_depack();                     
    }
  else{
    Serial.print("Incorrect data, requesting for retransmission"); 
    i2c_Request(8);}                  // if not, request for another transmission.
  } 



// This Function creates a copy of the sensData array, it's pretended to be "refreshed" every time the sensData original array is fulled by the i2c.
// and the checksum is correct.
// sensData2 is the array to be used by the control system and to be sended to GUI in response of a request.

void i2c_buffer_CP(){
  
  for(int i = 0; i<=7; i++){
    *(i2c_buffer2+i) = *(i2c_buffer1+i);  
    }
    
  }



// This function depackages the received data and stores the reading of sensors in the sensData array.
void i2c_depack(){
  *pnt_sensData = (*(i2c_buffer2+1) <<8 )  | *(i2c_buffer2+2);
  *(pnt_sensData+1) =  (*(i2c_buffer2+3) <<8 )  | *(i2c_buffer2+4);
  *(pnt_sensData+2) =  (*(i2c_buffer2+5) <<8 )  | *(i2c_buffer2+6);
  Serial.print("CtlData is : ");
  Serial.println((String) *(pnt_sensData)+" | "+ *(pnt_sensData+1) + " | " + *(pnt_sensData+2));
  }



// Empty the buffer to the GUI trough the slave-mode i2c.
void i2c_empty() {
  Wire.write(i2c_sensData2, i2c_SENS_DATA_SIZE);
  Serial.println("SE ENVIARON DATOS A GUI");
}




// Receive and store the parameters set by the GUI
void i2c_SetParameters(int BytesNum){
  for(int i = 0; i<BytesNum; i++){
    if(i < i2c_MAX_PARAM) {
      *(pnt_parameters + i) = Wire.read();
    }
    else{
      Wire.read();
    }
  }
  Serial.println((String)"Los parámetros establecidos por GUI son: " + i2c_receivedParam[0] + " | " + i2c_receivedParam[1] + " | " + i2c_receivedParam[2]);
}




// ----------- SETUP ------------  
void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(i2c_empty);
  Wire.onReceive(i2c_SetParameters);
}




// -------------- MAIN VOID -------------
void loop() {
  i2c_Request(8);
  delay(3000);
}

/*
  // Timer flag reading
//ISR(TIMER2_OVF_vect){ //No overflow used any more
ISR(TIMER2_COMPA_vect){ //Comparison overflow
    if(++cuenta >= 249){ //1 second interrupt
    i2c_Request(8):
      
    } 
}
*/
