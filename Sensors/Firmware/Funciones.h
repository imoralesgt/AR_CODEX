 /*  LIBRERIA PARA LAS FUNCIONES QUE CALCULAN LAS CONSTANTES   
 *  Y FACTORES DE CONVERSION DE LA LECTURA DE LOS SENSORES       
 *  DE PRESION MANOMETRICO Y DIFERENCIAL DE LOS CUALES OBTENEMOS    
 *  LA PRESION, FLUJO Y VOLUMEN EN EL SISTEMA DE RESPIRACION.
 *  
 *  
 *  PARA EL CALCULO DE FLUJO Y PRESION SE UTILIZA LAS SIGUIENTE FUNCIONES PARA EL
 *  CALCULO DE CONSTANTES Y FACTORES DE CONVERSION UNA UNICA VEZ 
 *  AL INICIO EL MICROCONTROLADOR.
 *   
 *  K_flujo, es la funcion dedicada para el calculo de la constante para obtener
 *  el flujo por el principio de Bernoulli.
 * 
 *  C_compresibilidad, es la funcion para el calculo de la constante de comprensibildad
 *  del gas que circula en el sistema de respiracion aplicable.
 * 
 *  Conversion_diff, es la funcion para el calculo del factor para convertir
 *  el valor de voltaje digital a un valor de presion diferencial.  
 *
 *  Conversion_mano, es la funcion para el calculo del factor para convertir
 *  el valor de voltaje digital a un valor de presion diferencial.
 * 
 *  flujo, es la funcion para calcular el flujo resultante con el valor de voltaje digital
 *  obtenido en voltaje del sensor presion difencial (MPX10DP).
 * 
 *  presion, es la funcion para la presion resultante con el valor de voltaje digital
 *  obtenido del sensor de presion manometrica (ADP1101)
 * 
 */

class Calculo {
    
  public:

    /*Funcion para el calculo de la constante K para el flujo
    recibe un valor de densidad del gas Pa, las areas del tubo venturi
    A1 -->s1 y A2 -->S2*/    
    float K_flujo(float Pa, float s1, float s2){

        float resultado;
        resultado = sqrt(1/Pa)*(s1*(sqrt(2/(pow(s1/s2,2)-1))));
        return resultado;

    }

    /*Funcion para el calculo de la constante C que es la comprensibilidad 
    del gas recibe gamma como el factor*/   
    float C_compresibilidad (float gamma){

        float resultado;
        resultado = sqrt((gamma)/(gamma-1));
        return resultado;

    }

    /*Funcion para el calculo del factor de convercion, que relaciona el valor digital
    del ADC sin decimar con el valor de presion diferencial del sensor
    recibe SPAN --> Voltaje full escala del sensor, PREASURE --> la presion en la que trabaj el sensor
    Vcc -->El voltaj de la fuente, GAIN --> Ganancia amplificador de intrumentacion, ADC_RES --> Resolucion ADC*/
    float Conversion_diff(float SPAN,float PREASURE,float Vcc, int GAIN, float ADC_RES){
       
        float resultado;
        resultado = (PREASURE /SPAN)* (Vcc/GAIN);    //CONVERT TO Pa
        resultado = resultado / pow(2,ADC_RES);
        return resultado;
    }


    /*Funcion para el calculo de flujo, recibe un valor de voltage 
    digital(V),un factor de conversion (f_conversion)  y un Voffset */
    float flujo(int V,float k, float c, float f_conversion, float Offset){

        float dP, q;
        float convert = 60000;
        dP = (V * (f_conversion + Offset));
        /*Serial.print("Valor de bits:");
        Serial.println(V);
        Serial.print("Valor de dp:");
        Serial.println((dP));
        Serial.print("Valor de raiz(dp):");
        Serial.println(sqrt(dP));*/
        q =   k *10* sqrt(dP);        //dL/s
        /*Serial.print("Valor de Q (dL/s):");
        Serial.println(q);*/
        q = q * convert;
        /*Serial.print("Valor de Q(dL/min):");
        Serial.println(q);*/
        return q;
    }

    
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
        p = ((V + Offset) * f_conversion)/10;       //CHANGE SCALE OF Pa, now is deciPascal
        return p;
    }


};
extern Calculo Calculos;
