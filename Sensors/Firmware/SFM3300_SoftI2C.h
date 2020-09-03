 /*  Arduino SFM3300 with SoftI2CMaster library.
  *
  *  Version 1.0
  *  Esta libreria utiliza SoftI2CMaster para la comunicacion por I2C con el sensor SFM3300
  *  
  *  Para utilizar esta libreria es necesario definir SFM3300_SDA_PIN, SFM3300_SCL_PIN, 
  *  SFM3300_SDA_PORT, SFM3300_SCL_PORT antes de incluir este archivo. Mira esta documentacion
  *  de Arduino para encontrar informacion del puerto y pines de tu arduino board.
  *  Tienes que usar las siguientes definiciones:
  *  #define SFM3300_SDA_PIN 5
  *  #define SFM3300_SDA_PORT PORTD
  *  #define SFM3300_SCL_PIN 4    
  *  #define SFM3300_SCL_PORT PORTD
  *  #define SFM3300_POWER_PIN
  * 
  */

/*SoftWireI2CMaster PIN ASSIGNATION*/
#define I2C_PULLUP 1
#define SDA_PORT SFM3300_SDA_PORT
#define SDA_PIN SFM3300_SDA_PIN 
#define SCL_PORT SFM3300_SCL_PORT
#define SCL_PIN SFM3300_SCL_PIN 
#define I2C_SFM3300_ADDR 0x40
/*CONVERSION DEF*/

 
#define SCALE_FACTOR_FLOW 120

#include <SoftI2CMaster.h>

float last_flow = 0;
float Offset_Flow = 32769;

class SFM3300 {
    private:
    
    static void Offset_Init(){
        Offset_Flow =0;
        int muestras=0;
        uint32_t sumflow=0;
        uint16_t newflow=0;
        for(int i=0; i<200; i++){
          i2c_rep_start((I2C_SFM3300_ADDR<<1)|I2C_READ);
          uint8_t MS = i2c_read(false);
          uint8_t LS = i2c_read(false);
          uint8_t CRC = i2c_read(true);
          if(CRC_Check(MS,LS,CRC)){       
            newflow = (MS<<8) | LS;
            sumflow +=newflow;
            muestras++;
          }
          delay(5);
        }
        Offset_Flow = (float)(sumflow/muestras);
        Serial.print("OFFSET FLOW: ");
        Serial.print(Offset_Flow);
        Serial.print(", ");
    }
      
    static bool CRC_Check(uint8_t MS, uint8_t LS, uint8_t CRC){
        uint8_t check = 0x0;
        uint16_t value = (MS<<8) | LS;
        for(int NBits=0; NBits<16; NBits++){
            if(Equal7bit(value<<NBits, check)){  //Corrimiento, negacion de bits 4 y 5, y bit0 ='1'
            check  <<=1;
            if (bitRead(check, 4)){bitClear(check,4);}else{bitSet(check,4);}
            if (bitRead(check, 5)){bitClear(check,5);}else{bitSet(check,5);}
            bitSet(check,0);
            }
            else{         //Corrimiento y bit0 ='0'
            check <<=1;
            bitClear(check,0);
            }
        }
        if (check==CRC){return true;}else{return false;} 
    }
    
    static bool Equal7bit(uint16_t first,uint8_t second){
        if ((first>>15) xor second>>7){return true;}else{return false;}
    }

    static void SoftReset(){   //RUTINA PARA ENVIAR EL COMANDO DE SOFT RESET IMPLEMENTADO EN EL SENSOR.
        if(i2c_start((I2C_SFM3300_ADDR<<1)|I2C_WRITE)){
            i2c_write(0x20);
            i2c_write(0x00);
            i2c_stop();
        }else{
            Serial.println("SOFT RESET - I2C DEVICE BUSY");
            hardreset();
        }
        delay(10);
    }

    static void hardreset(){   //RUTINA PARA ACTIVAR EL SENSOR POR MEDIO DE UN TRANSISTOR.
        //Turn Off
        digitalWrite(SFM3300_POWER_PIN, LOW);
        delay(10);
        //Turn On 
        digitalWrite(SFM3300_POWER_PIN, HIGH);
        delay(10);
        //ContinuousMeasurement();
    }
    static void ContinuousMeasurement(){   //RUTINA PARA ENVIAR COMANDO DE TOMA DE MEDIDAS
      SoftReset();
        if(i2c_start((I2C_SFM3300_ADDR<<1)|I2C_WRITE)){
            i2c_write(0x10);
            i2c_write(0x00);
            //i2c_stop();
        }else{
            Serial.println("CONTINUOUS MEASUREMENTS - I2C DEVICE BUSY");
            hardreset();
            return;
        }
        delay(10);
    }
    public:

    static bool init(){
        pinMode(SFM3300_POWER_PIN, OUTPUT);
        digitalWrite(SFM3300_POWER_PIN, HIGH);
        delay(10);
        if (!i2c_init()){
            	return false;
        }else{
            SerialNumber();
            ContinuousMeasurement();
            Offset_Init();
            return true;
        }
        
    }

    static float FlowMeasure(){
        i2c_rep_start((I2C_SFM3300_ADDR<<1)|I2C_READ);
        uint8_t MS = i2c_read(false);
        uint8_t LS = i2c_read(false);
        uint8_t CRC = i2c_read(true);
        uint16_t value = (MS<<8) | LS;
        float flujo = ((float)value - Offset_Flow)/SCALE_FACTOR_FLOW;
        if(CRC_Check(MS,LS,CRC)){
            if (flujo<0){        //TYPICAL ERROR
                hardreset();        //HARD RESET
                return last_flow;
            }else{
                flujo = flujo *1000; //cL/min
                last_flow = flujo;
                return flujo;       //RETURNS VALID VALUE
            }
        }else{
            return last_flow;          //RETURNS -1 
        }
    }

    static void SerialNumber(){
        SoftReset();
        if(i2c_start((I2C_SFM3300_ADDR<<1)|I2C_WRITE)){
            i2c_write(0x31);
            i2c_write(0xAE);
            delay(10);
            i2c_rep_start((I2C_SFM3300_ADDR<<1)|I2C_READ);
            uint32_t sn = 0;
            sn = i2c_read(false); sn <<=8;
            sn += i2c_read(false); sn <<=8;
            uint8_t CRC1 = i2c_read(false);
            sn += i2c_read(false); sn <<=8;
            sn += i2c_read(false);
            uint8_t CRC2 = i2c_read(true);
            i2c_stop();
            Serial.print("SERIAL NUMBER: ");
            Serial.print(sn);
            Serial.print(", ");
        }else{
            Serial.println("I2C DEVICE BUSY");
            hardreset();
        }
    }
    
};

 extern SFM3300 SFM3300;
