# FIRMWARE SENSORES VENTILADOR

## Funciones.h
 *  LIBRERIA PARA LAS FUNCIONES QUE CALCULAN LAS CONSTANTES   
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
 *
 
