/*LOGICA DE LA PROGRAMACION PARA LA ADQUISICION DE DATOS DEL SENSOR MPS-2100:
    SE UTILIZA LA LIBRERIA TimerOne.h, para utilizar el Timer1 de manera facil  
    #1 Se establece la velocidad el timer (cada 20 micro segundo), Timer1.initialize(recibe tiempo en microsegundos)
    #2 Se le asigna una funcion a la interrupcion generada por el Timer1
    #3 En este metodo, se hace un promedio de 50 muestras tomadas cada una 20uS(Timer1)
    #4 Esta muestra resultante del promedio de 50 se convierte a un valor aproximado de Volage 
       Con el factor de conversion de Vcc/1024.
    #5 A este valor se le sumo, el Offset aproximado de 0, si existe se cambia el valor de Offset
    #6 Este valor dado en (V), debe ser divido entre 100, debido a la ganacia del circuito de adquisicion
       que cuenta con una ganacia de 100.
       Con el valor en mV, valor en la escala del sensor, se uso la pendiente de 0.05 para calcular la presion
       en psi y luego multiplicado por el factor de conversion para pasarlo a cmH2O
    #7 Los valores son enviados por serial para su recepcion por el monitorl serial o el recepcion-log.py   
    */

#include <TimerOne.h>   //UNICA LIBRERIA

/* DEFINICIONES */
#define PinSensor A0
#define Baudrate 115200
#define microsegundos 20    
#define ganacia 100
#define linealidad 0.03
#define FactorPSIcmH20 70.306957829636
#define Vcc 5.015
#define ResADC 1024     //10bits
#define Offset 0.0
/*              */
/*   VARIABLES  */
volatile int32_t value=0;
volatile double Volts=0;
volatile double preasure=0;
volatile int muestras =0;
/*              */
void ISR_TIMER1(void){
    if(muestras <50)
    {
        value = value + analogRead(PinSensor);  //LECTURA DEL PinSensor
        muestras++;                                 //SUMO AL CONTADOR DE MUESTRAS
    }
    else
    {
        Volts = ((value/muestras) * (Vcc/ResADC))+Offset;           //CONVERT DIGITAL VALUE TO ANALOG VALUE.
        preasure = ((Volts/ganacia)/linealidad)*FactorPSIcmH20;     //CALCULO DE LA PRESION
        Serial.print(Volts*100);                                    //ESCALADOR DE 100, PARA OBTENER MAYOR RESOLUCION EN LA RECEPCION.
        Serial.print(",");                                          //SEPARADOR O DELIMITADOR
        Serial.println(preasure);                                   //PRESION
        muestras=0;                                                 //REINICIO DE VARIABLES
        value=0;                                                    //REINICIO DE VARIABLE
    }

}

void setup(){
    Serial.begin(Baudrate);                     //Serial a 9600
    pinMode(PinSensor, INPUT);              //PIN DEL SENSOR EN MODO ENTRADA
    Timer1.initialize(microsegundos);                //CADA 1mS
    Timer1.attachInterrupt(ISR_TIMER1);     //ASIGNAR RUTINA DE interrupcion
    
}

void loop(){
    
}