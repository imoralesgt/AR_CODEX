#ifndef I2CCOMMS_H_
#define I2CCOMMS_H_

#include "Arduino.h"

#define I2C_TIMEOUT 20
// #define I2C_PULLUP 1
#define I2C_FASTMODE 1
#define SDA_PORT SOFT_I2C_PORT
#define SDA_PIN SOFT_I2C_PORT_SDA // = A2
#define SCL_PORT SOFT_I2C_PORT
#define SCL_PIN SOFT_I2C_PORT_SCL // = A3

/// GENERAL
#define SLAVE_ADDRESS 0x22
#define SENS_ADDRESS 0x08
#define i2c_SENS_DATA_SIZE 8   // Data size from SensorsData.
#define i2c_MAX_PARAM 3   // ¿? Number of Bytes that are going to be sent from GUI.
#define NUM_OF_SENSORS 3


//---------- I2C GLOBLAL VARIABLES ------------
// All the pointer variables are pointing to the base address of the arrays, the [0] position.
extern byte i2c_sensData[i2c_SENS_DATA_SIZE];      // In i2c_sensData remains the bytes received by the i2c interface.
extern byte i2c_sensData2[i2c_SENS_DATA_SIZE];     // In i2c_sensData2 remain the bytes copied from i2c_sensData when these bytes are completely received and checked.
extern byte *i2c_buffer1;     // Input buffer.
extern byte *i2c_buffer2;    // Output buffer.
extern int sensData[NUM_OF_SENSORS];         // In sensData Remains the last three principal values obtained by the sensors, these are int-type and are obtained by the corresponding two bytes in the transmission.
extern int *pnt_sensData;         // pnt_sensData points to the sensData vector whith the control variables.
extern byte i2c_receivedParam[i2c_MAX_PARAM]; // This array contains the Set-point parameters received from GUI.
extern byte *pnt_parameters;

extern volatile int guiNewSetPoints;



extern void i2c_Request(int NumBytes);
void i2c_checkData();
void i2c_buffer_CP();
void i2c_depack();
void i2c_empty();
void i2c_SetParameters(int BytesNum);
extern void i2cSetup();

#endif