import matplotlib.pyplot as plt
import matplotlib.animation as animation
#FILE ORIGIN
import os
THIS_FOLDER = os.path.dirname(os.path.abspath(__file__))
my_file = os.path.join(THIS_FOLDER, 'Muestras.txt')
#####################################################
#matplotlib, figura y subplotts
fig = plt.figure()
ax = fig.add_subplot(111)
ax1 = fig.add_subplot(211)
ax2 = fig.add_subplot(212)
################################

def plot():
    #APERTURA DE ARCHIVO .TXT
    data = open(my_file,'r').read()
    lines = data.split('\n')
    ts = []
    S1 = []
    S2 = []
    #LECTURA DE DATOS DEL ARCHIVO .TXT
    for line in lines:
        try:
            t, s1, s2 = line.split(',') # SEPARADOR "," en archivo .txt    
            ts.append(float(t))       #LISTA PARA LOS TIEMPOS  
            S1.append(float(s1))#LISTA PARA EL PRIMER SENSOR
            S2.append(float(s2))#LISTA PARA EL SEGUNDO SENSOR
        except Exception:
            #print("ERROR ENIMPRESION DE SERIAL")
            ts.append(float(t))       #LISTA PARA LOS TIEMPOS  
            S1.append(0)#LISTA PARA EL PRIMER SENSOR 
            S2.append(0)#LISTA PARA EL SEGUNDO SENSOR
    #PRIMERA GRAFICA, SENSOR1 vs Tiempo
    ax1.clear()
    #error_positivo = list(map(lambda volts: volts+0.02, volts))         #ERROR ESTIMADO DE 0.02V
    #error_negativo = list(map(lambda volts: volts-0.02, volts))         #ERROR ESTIMADO DE 0.02V
    ax1.plot(ts, S1,"b-")# ts, error_positivo,"r:",ts, error_negativo,"g:")   #GRAFICA CON ERRORES
    ax1.set_ylabel('Sensor1')                                        #LABEL DEL EJE Y, PARA VOLTAJE
    #SEGUNDA GRAFICA, SENSOR2 vs Tiempo
    ax2.clear()
    #error_positivo = list(map(lambda preasures: preasures+0.28, preasures)) #ERROR ESTIMADO DE 0.28cm
    #error_negativo = list(map(lambda preasures: preasures-0.28, preasures)) #ERROR ESTIMADO DE 0.28cm
    ax2.plot(ts, S2,"b-")# ts, error_positivo,"r:",ts, error_negativo,"g:")   #GRAFICA CON ERRORES
    ax2.set_ylabel("Sensor2")                                        #LABEL DEL EJE Y, PARA PRESION
    #ARREGLOS.
    ax.set_xlabel("Tiempo(s)")          #LABEL EJE X, TIEMPOclear

    ax.set_yticklabels([])              #ELIMINAR EJE
    ax.set_xticklabels([])              #ELIMINAR EJE
    ax.set_title("Grafica decimacion")   #TITULO DE LA GRAFICA
    plt.show()                          #MOSTRAR GRAFICO

plot()