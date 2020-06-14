/*LOGICA DE LA PROGRAMACION PARA LA OBTENCIÓN DEL CAUDAL CON EL VALOR OBTENIDO DEL SENSOR MPX10:
    #1 El valor obtenido se convierte a un valor aproximado de Voltaje análogo 
       con el factor de conversión de Vcc/1024.
    #2 A este valor se le sumó, el Offset aproximado de 0, si existiera se cambia el valor de Offset.
    #3 Este valor dado en (V), debe ser divido entre 100, debido a la ganacia del circuito de adquisición
       que cuenta con una ganacia de 100.
       Con el valor en mV, valor en la escala del sensor, se usó la pendiente de 0.0035 y multiplicó por 
       1000 para calcular la presión en pascales y luego utilizando el valor de la presión para poder calcular
       el caudal que circula por el tubo.   
       
     *  pa = densidad del aire [kg/m^3] 
     *  s1 = área superficial entrada de tubo venturi [m^2]
     *  s2 = área superficial reducción de tubo venturi [m^2]
     *  dP = p2-p1 [Pa]
     *  q = caudal [m^3/s]
     *  
     */
class Caudal    
{

float flujo(float V){
  float pa=1.19,s1=0.0002488455541,s2=0.0000916088417;
  float m=0.0035;
  float Ve=0,dP=0,q=0,k=0;
  float G=100,Vcc=5.0,ResADC=1024,Offset=0;
  
  Ve = (V*(Vcc/ResADC)/G)+Offset;
  dP = -(Ve/m)*1000;
  
  k = 0.5*pa*((pow(s2,2)-pow(s1,2))/(pow(s1,2)*pow(s2,2)));
  q = sqrt(dP/k);
  return q;
}
};