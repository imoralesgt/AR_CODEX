/*Analog readout and packaging for i2c slave tranmision */
#include "pinout.h" //pinout definition (set in other tab)

#define max_buf 50 //setting max buffer length for data testing ONLY USE FOR TESTING NOT ENOUGH SPACE FOR BIG BUFFER, REDUCE IN CASE OF PROBLEMS.

int cal=0;
int sensor[3]={0,0,0};
int dbuffer[3][max_buf];

void ad_readout(){ //Single analog readout of all sensors
  sensor[0]=analogRead(sensorP);
  sensor[1]=analogRead(sensorV);
  sensor[2]=analogRead(sensorF);
}

/*Display function customized for display in Serial Plotter
 * tool. Do an analog readout of each sensor and store it in a buffer. 
 * buf_size  Input size of the data buffer
 * 
 * if buf_size < max_buf displays 0, 
 */
void calib_verbose(int buf_size){
  if (buf_size<max_buf){
    for (int i=0; i<buf_size; i++){
      dbuffer[0][i]=analogRead(sensorP);
      dbuffer[1][i]=analogRead(sensorV);
      dbuffer[2][i]=analogRead(sensorF);
    }
    for (int i=0; i<buf_size; i++){
      Serial.print(dbuffer[0][i]);
      Serial.print("\t");
      Serial.print(dbuffer[1][i]);
      Serial.print("\t");
      Serial.println(dbuffer[2][i]);  
    }
  }
  else{
      Serial.print(0);
      Serial.print("\t");
      Serial.print(0);
      Serial.print("\t");
      Serial.println(0);  
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(calbit, INPUT_PULLUP);
}


void loop() {
  cal=digitalRead(calbit); //read calibration status bit.
  if(cal==HIGH){
    calib_verbose(40);
  }
  //TODO: I2C SLAVE ROUTINE IN ELSE CONDITION.
}
