 /*  LIBRERIA PARA LAS FUNCIONES QUE CALCULAN LAS CONSTANTES   
 *  Y FACTORES DE CONVERSION DE LA LECTURA DE LOS SENSORES       
 *  DE PRESION MANOMETRICO DEL CUAL OBTENEMOS    
 *  LA PRESION EN EL SISTEMA DE RESPIRACION.
 *  
 *  
 *  PARA EL CALCULO DE PRESION SE UTILIZA LAS SIGUIENTE DOS FUNCIONES PARA EL
 *  CALCULO DE CONSTANTES Y FACTORES DE CONVERSION UNA UNICA VEZ 
 *  AL INICIO EL MICROCONTROLADOR.
 *     
 *
 *  Conversion_mano, es la funcion para el calculo del factor para convertir
 *  el valor de voltaje digital a un valor de presion diferencial.
 * 
 *  presion, es la funcion para la presion resultante con el valor de voltaje digital
 *  obtenido del sensor de presion manometrica (ADP1101)
 * 
 */

class Calculo {
    
  public:
    
    /*Funcion para el calculo del factor de convercion, que relaciona el valor digital
    del ADC sin decimar con el valor de presion manometrica
    recibe SPAN --> Voltaje full escala del sensor, PREASURE --> la presion en la que trabaj el sensor
    Vcc -->El voltaj de la fuente, GAIN --> Ganancia amplificador de intrumentacion, ADC_RES --> Resolucion ADC*/
    float Conversion_mano (float SPAN,float PREASURE,float Vcc, int GAIN, float ADC_RES){
       
        float resultado;
        resultado = (PREASURE /SPAN)* (Vcc/GAIN);    //CONVERT TO Pa
        resultado = resultado / pow(2,ADC_RES);
        return resultado;
    }


    /*Funcion para el calculo de la presion, recibe un valor de voltage 
    digital(V),un factor de conversion (f_conversion)  y un Voffset */
    float presion(int V,float f_conversion, float Offset){
        
        float p;
        p = ((V - Offset) * f_conversion);
        return p;
    }


};
extern Calculo Calculos;
