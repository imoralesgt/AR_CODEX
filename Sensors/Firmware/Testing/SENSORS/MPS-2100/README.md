# LOGICA DE LA PROGRAMACION PARA LA ADQUISICION DE DATOS DEL SENSOR MPS-2100:
## 1. SE UTILIZA LA LIBRERIA TimerOne.h, para utilizar el Timer1 de manera facil
## 2. Se establece la velocidad el timer (cada 20 micro segundo), Timer1.initialize(recibe tiempo en microsegundos)
## 3. Se le asigna una funcion a la interrupcion generada por el Timer1
## 4. En este metodo, se hace un promedio de 50 muestras tomadas cada una 20uS(Timer1)
## 5. Esta muestra resultante del promedio de 50 se convierte a un valor aproximado de Voltage con el factor de conversion de Vcc/1024.(10bits)
## 6. A este valor se le sumo, el Offset aproximado de 0, si existe se cambia el valor de Offset
## 7 Este valor dado en (V), debe ser divido entre 100, debido a la ganacia del circuito de adquisicion que cuenta con una ganacia de 100.Con el valor en mV, valor en la escala del sensor, se uso la pendiente de 0.05 para calcular la presion en psi y luego multiplicado por el factor de conversion para pasarlo a cmH2O
## 8. Los valores son enviados por serial para su recepcion por el monitorl serial o el recepcion-log.py   
    */