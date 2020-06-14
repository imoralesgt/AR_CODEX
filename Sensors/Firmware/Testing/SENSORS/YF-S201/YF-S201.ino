#include <TimerOne.h>

/*VARIABLES DE INTERRUPCIONES*/
volatile float NumPulsos = 0;             //VARIABLE PARA DETECTAR LOS PULSOS POR INTERRUPCIONES
volatile float frecuencia =0;           //VARIABLE PARA CALCULAR LA frecuencia
volatile float caudal_instantaneo = 0;  //LITROS EN EL TIEMPO ESTABLECIDO
volatile float caudal_L_m = 0;          //LITROS POR MINUTO
volatile float caudal_L_h = 0;          //LITROS POR HORA
/*DEFINICONES DE PINES Y FACTORES*/
#define PinSensor 2
#define factor_K 8.23
#define factor 494.06


/*VARIABLES*/
float frecuencia_ant=0;

//ISR PIN2
void ISR_PIN2 ()
{ 
  NumPulsos++;      //INCREMENTA EN PULSOS 
}

void ISR_TIMER1(void) {
  frecuencia = NumPulsos;
  caudal_instantaneo = frecuencia /factor;  
  caudal_L_m = frecuencia/factor_K;
  caudal_L_h = frecuencia/factor_K*60;
  NumPulsos =0;
  Serial.println(frecuencia);
}
void setup()
{ 
  Serial.begin(9600); 
  pinMode(PinSensor, INPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(ISR_TIMER1);
} 

void loop ()    
{
  //Serial.print("Numero_de_pulsos:");
  //Serial.println(frecuencia);
  //Serial.print(" ");
  //Serial.print("Caudal_Instantaneo:");
  //Serial.print(caudal_instantaneo);
  //Serial.print(" ");
  //Serial.print("Caudal_(l/min):");
  //Serial.print(caudal_L_m);
  //Serial.print(" ");
  //Serial.print("Caudal_(l/h):");
  //Serial.println(caudal_L_h);
  }