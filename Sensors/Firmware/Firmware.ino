#include <TimerOne.h>           //LIBRERIA TIMER UNO
#include <Wire.h>
#include "Funciones.h"

#define SFM3300_SDA_PIN 5
#define SFM3300_SDA_PORT PORTD
#define SFM3300_SCL_PIN 4    
#define SFM3300_SCL_PORT PORTD
#define SFM3300_POWER_PIN 10
#include "SFM3300_SoftI2C.h"
/*AVR Basic functions                         */
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= _BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
/*  PINES DE SENSOR PRESION                   */
#define Manometric A0
/*  CONSTANTES ADC Y ADQUISICION DE DATOS     */
#define ResADC 12.32
#define Vcc 3.27
#define decimacion 25
#define microsegundos 100
/*  CONSTANTES PRESION & SESOR MANOMETRICO    */
#define FULL_SPAN_mano 0.04
#define FULL_SCALE_PREASURE_mano 4900
#define GAIN_mano 100
///////////////////////////
#define i2c_addres 8
#define Baudrate 115200
/*Variables de presion*/
float Convert_mano;
uint32_t Voffset_mano;
/**********************/
/*Variables de funcionamiento*/
int state=0xCC;             //STATUS VARIABLE
byte iic_pack[8];           //I2C, PACK VARIABLE
int dbuffer;             //ADC BUFFER VARIABLE
float Valuesensors[3];      //Float sen values
float Volumen;              //Volumen variable
uint16_t ValoresNormalizados[3]; //Valores enteros para transmision por I2C
volatile int i,j=0;         //Variables conteo de decimacion


//Funcion  de empaquetado 
void pack(int state, int sensors[3]){

  /*STATUS FLAG IS PENDING*/
  byte chksum=0;
  iic_pack[0]=state & 255; //status flag

  iic_pack[1]=(byte)(sensors[0] >>8 & 255); //MSB valor de presion
  iic_pack[2]=(byte)(sensors[0] & 255);     //LSB valor de presion

  iic_pack[3]=(byte)(sensors[1]>>8 & 255);  //MSB valor de flujo
  iic_pack[4]=(byte)(sensors[1] & 255);     //LSB valor de flujo

  iic_pack[5]=(byte)(sensors[2]>>8 & 255);  //MSB valor de volumen
  iic_pack[6]=(byte)(sensors[2] & 255);     //LSB valor de volumne

  /*XOR CHECKSUM*/
  chksum = iic_pack[0]^iic_pack[1]^iic_pack[2]^iic_pack[3]^iic_pack[4]^iic_pack[5]^iic_pack[6];
  iic_pack[7]=chksum & 255;

}

//FUNCION DE ENVENTO DE SOLICITUD DE INFORMACION
void I2C_event()
{
    ValoresNormalizados[0] = Valuesensors[0];
    ValoresNormalizados[1] = Valuesensors[1];
    ValoresNormalizados[2] = Valuesensors[2];
    
    /*Serial.print(ValoresNormalizados[0]);
    Serial.print(",");
    Serial.println(ValoresNormalizados[1]);
    */
    pack(state,ValoresNormalizados);  //empaquetado de I2C, modifica varible global //iic_pack[]


    /*I2C, ENVIO DE PAQUETE*/
    Wire.write(iic_pack,8);
}

//FUNCION DE INTERRUPCION DE TIMER1 
void ISR_TIMER1(void){
  /* DECIMACION DE MUETRAS DE SENSORES por A0 y A1 (25)
   * TOMANDO UN MUESTRA CADA 100us Y CON UN TOTAL
   * DE 25 MUESTRAS POR LA DECIMACION, OBTENEMOS UN NUEVO
   * VALOR CADA 100uS *25 = 2.5ms
   * EL VOLUMEN POR SU PARTE, SE TOMA DEL PROMEDIO DE
   * 10 MUESTRAS DE FLUJO, Qprom DIVIDIDO EL TIEMPO 
   * QUE SERIA DE t = 10* 2.5mS = 25mS, CONCLUYENDO CON UN VALOR DE VOLUMEN CADA 25ms 
   */

    if(i < decimacion){                            
      i++;
      dbuffer=analogRead(Manometric)+dbuffer; 
    }
    else
    {


      /*CALCULO DE PRESION, FLUJO*/ /*NO SE ESTA TOMANOD EN CUENTA EL TIEMPO DE EJECUCION DEL CALCULO DE ESTAS FUNCIONES*/
      /*SEGUN LAS PRUEBAS NO HAY PROBLEMA CON EL TIEMPO DE EJECUCION DE TODA LA RUTINA DE ESTE TIMER*/
      /*LAS MUESTRAS SON MANEJADAS CORRECTAMENTE Y ENVIADAS CORRECTAMENTE A UN MASTER A 250HZ*/
      Valuesensors[1] = SFM3300.FlowMeasure();
      Valuesensors[0] = Calculos.presion((dbuffer),Convert_mano,Voffset_mano);
      //Serial.println(Valuesensors[1]);
      //Serial.println(Valuesensors[0]);
      /*CALCULO DE VOLUMEN APARTIR DE FLUJO*/
      if(j <10){   /*OBTENCION DE 10 MUESTRAS DE FLUJO*/
          j++;
          Volumen= Valuesensors[1] + Volumen; 

      }
      else
      {
        Valuesensors[2] = 2.5*((Volumen)/60);    /*CALCULO DEL V = Qprom*25mS = Qprom*40*/
        Volumen =0;
        j=0;
      }

      
      i=0;
      dbuffer=0;
    }

}

void ADP_Voff_Init(){
      Voffset_mano =0;
      int muestras=0;
      for(int i=0; i<decimacion; i++){
        Voffset_mano=analogRead(Manometric)+Voffset_mano;
        delay(1);
      }
      Serial.print("El valor de Voff del ADP1101: ");
      Serial.println(Voffset_mano);
  
}

//Funcion Setup()
void setup(){
    
    /* Configuracion del prescalador del ADC (ADCSRA), ref: pag 255.
    http://electronics.arunsworld.com/wp-content/uploads/2013/11/atmega328p.pdf
     * CON EL PRESCALADOR A 8, OBTENEMOS UNA FRECUENCIA DE MUESTREO DE:
     * Freq =  CLK/(PRESCALADOR * 13) = 8MHz/(8*13) = 77kHz
     * AL SER DOS LECTURAS DE ADC, LA OBTENCION DE DATOS ESTARIA APROX Freq/2 = 38kHz
     * A UN PERIODO DE 26uS, LO CUAL NO GENERA PROBLEMAS CON EL TIMER1 DE 100us
    */
  
    sbi(ADCSRA, ADPS1); 
    sbi(ADCSRA, ADPS0);
    cbi(ADCSRA, ADPS2);
    ADCSRA |= (1<<ADEN);

    /*I2C, INICIALIZACION Y CONFIGURACION*/
    Wire.begin(i2c_addres);
    Wire.onRequest(I2C_event);
    
    Serial.begin(Baudrate);     /*DEBUGGIN SERIAL*/

    /*ENTRADAS ANALOGICAS DE LOS SENSORES*/
    pinMode(Manometric, INPUT); 

    /*Inicializacion SFM3300 */ 
    if(SFM3300.init()){
      Serial.println("SFM3300 DETECTED");
    }else{
      Serial.println("SFM3300 NO DETECTED");
    }


    /*Inicializacion de constantes para calculo
      De la presion por medio del sensor de presion manometrica*/
    Convert_mano = Calculos.Conversion_mano(FULL_SPAN_mano,FULL_SCALE_PREASURE_mano,Vcc,GAIN_mano,ResADC);
    ADP_Voff_Init();
    /*DEBUG SERIAL INITI*/
    Serial.print("El valor de conversion del APD1101 es :");
    Serial.println(Convert_mano);




    /*Configuracion del Timer1 16 bits*/
    Timer1.initialize(microsegundos);       //CADA 40uS
    Timer1.attachInterrupt(ISR_TIMER1);     //ASIGNAR RUTINA DE interrupcion
    Serial.println("INICIALIZACION COMPLETADA");
}

//LOOP
void loop(){
}
