#include <TimerOne.h>           //LIBRERIA TIMER UNO
#include <Wire.h>
#include "Funciones.h"
/*AVR Basic functions                         */
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= _BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
/*  PINES DE SENSORES                         */
#define Manometric A0
#define Diferential A1
/*  CONSTANTES ADC Y ADQUISICION DE DATOS     */
#define ResADC 12.32
#define Vcc 3.27
#define decimacion 25
#define microsegundos 100
/*  CONSTANTES FLUJO & SENSOR DIFERECIAL      */
//MECANICAS, TUBO VENTURI
#define Densidad_Aire 1.29
#define Area_1 0.000176714
#define Area_2 0.000091608
//CIRCUITO DE ADQUISICION Y SENSOR
#define FULL_SPAN_diff 0.035
#define FULL_SCALE_PREASURE_diff 10000
#define GAIN_diff 100
/*  CONSTANTES PRESION & SESOR MANOMETRICO    */
#define FULL_SPAN_mano 0.04
#define FULL_SCALE_PREASURE_mano 4900
#define GAIN_mano 100
///////////////////////////
#define i2c_addres 2
#define Baudrate 115200
/*Variables del flujo*/ 
float K;
float C;  
float Convert_diff;
float Voffset_diff;
/**********************/
/*Variables de presion*/
float Convert_mano;
float Voffset_mano;
/**********************/
/*Variables de funcionamiento*/
int state=0xCC;             //STATUS VARIABLE
byte iic_pack[8];           //I2C, PACK VARIABLE
int dbuffer[2];             //ADC BUFFER VARIABLE
float Valuesensors[3];      //Float sen values
float Volumen;              //Volumen variable
int ValoresNormalizados[3]; //Valores enteros para transmision por I2C
volatile int i,j=0;         //VArialbe conteo de decimacion


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
  //chksum = iic_pack[0]^iic_pack[1]^iic_pack[2]^iic_pack[3]^iic_pack[4]^iic_pack[5]^iic_pack[6]^iic_pack[7];

  //IVAN: El checksum no debe incluir dentro del XOR el valor del Checksum anterior (iic_pack[7]).
  //IVAN: Nuevo checksum aca:
  chksum = iic_pack[0]^iic_pack[1]^iic_pack[2]^iic_pack[3]^iic_pack[4]^iic_pack[5]^iic_pack[6];  
  iic_pack[7]=chksum & 255;

}

//FUNCION DE ENVENTO DE SOLICITUD DE INFORMACION
void I2C_event()
{
    ValoresNormalizados[0] = Valuesensors[0];
    ValoresNormalizados[1] = Valuesensors[1];
    ValoresNormalizados[2] = Valuesensors[2];
    pack(state,ValoresNormalizados);  //empaquetado de I2C, modifica varible global //iic_pack[]


    /*I2C, REOCRRIDO DE VECTOR Y ENVIO DE CADA BYTE*/
//    for(int i=0; i<8; i++){
//        Wire.write(iic_pack[i]);
//    }

    //IVAN: No utilizar el ciclo para recorrer cada byte al enviarlo por I2C
    //IVAN: Enviar el pack completo directamente con Wire.write(iic_pack, 8)
    Wire.write(iic_pack, 8);

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
      dbuffer[0]=analogRead(Manometric)+dbuffer[0]; 
      dbuffer[1]=analogRead(Diferential)+dbuffer[1];
    }
    else
    {


      /*CALCULO DE PRESION, FLUJO*/ /*NO SE ESTA TOMANOD EN CUENTA EL TIEMPO DE EJECUCION DEL CALCULO DE ESTAS FUNCIONES*/
      /*SEGUN LAS PRUEBAS NO HAY PROBLEMA CON EL TIEMPO DE EJECUCION DE TODA LA RUTINA DE ESTE TIMER*/
      /*LAS MUESTRAS SON MANEJADAS CORRECTAMENTE Y ENVIADAS CORRECTAMENTE A UN MASTER A 250HZ*/
      Valuesensors[1] = Calculos.flujo((dbuffer[1]),K,1,Convert_diff,0);
      Valuesensors[0] = Calculos.presion((dbuffer[0]),Convert_mano,0);

//      /*CALCULO DE VOLUMEN APARTIR DE FLUJO*/
//      if(j <10){   /*OBTENCION DE 10 MUESTRAS DE FLUJO*/
//            j++;
//           Volumen= Valuesensors[1] + Volumen; 
//
//      }
//      else
//      {
//        Valuesensors[2] = 2.5*((Volumen)/60);    /*CALCULO DEL V = Qprom*25mS = Qprom*40*/
//        Volumen =0;
//        j=0;
//      }

      Volumen = 0;

      
      i=0;
      dbuffer[0]=0;
      dbuffer[1]=0;
    }

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

    /*Configuracion del Timer1 16 bits*/
    Timer1.initialize(microsegundos);       //CADA 40uS
    Timer1.attachInterrupt(ISR_TIMER1);     //ASIGNAR RUTINA DE interrupcion
    Serial.begin(Baudrate);     /*DEBUGGIN SERIAL*/

    /*ENTRADAS ANALOGICAS DE LOS SENSORES*/
    pinMode(Manometric, INPUT); 
    pinMode(Diferential, INPUT);

    /*Inicializacion de constantes para calculo
      Del flujo por medio del sensor diferencial*/
    K = Calculos.K_flujo(Densidad_Aire,Area_1,Area_2);
    //C = Calculos.C_compresibilidad(Constante_comprensibilidad); ##NO UTILIZADA
    Convert_diff = Calculos.Conversion_diff(FULL_SPAN_diff,FULL_SCALE_PREASURE_diff,Vcc,GAIN_diff,ResADC);


    /*Inicializacion de constantes para calculo
      De la presion por medio del sensor de presion manometrica*/
    Convert_mano = Calculos.Conversion_mano(FULL_SPAN_mano,FULL_SCALE_PREASURE_mano,Vcc,GAIN_mano,ResADC);

    /*DEBUG SERIAL INITI*/
//    Serial.print("El valor de conversion del APD1101 es :");
//    Serial.println(Convert_mano);
//    Serial.print("El valor de conversion del MPX10DP es :");
//    Serial.println(Convert_diff);
//    Serial.print("El valor de K es(X10000) :");
//    Serial.println(K*10000);


    /*I2C, INICIALIZACION Y ONCFIGURACION*/
    Wire.begin(i2c_addres);
    Wire.onRequest(I2C_event);


}

//LOOP
void loop(){
}
