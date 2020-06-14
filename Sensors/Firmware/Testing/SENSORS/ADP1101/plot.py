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
    volts = []
    preasures = []
    #LECTURA DE DATOS DEL ARCHIVO .TXT
    for line in lines:
        print(line)
        t, V, P = line.split(',') # SEPARADOR "," en archivo .txt    
        ts.append(float(t))       #LISTA PARA LOS TIEMPOS  
        volts.append(float(V)/100)#LISTA PARA EL VOLTAJE, SE DIVIDE ENTRE 100 PARA EL ESCALADOR USADO EN SERIAL
        preasures.append(float(P))#LISTA PARA LAS PRESIONES

    #PRIMERA GRAFICA, VOLTAJE vs Tiempo
    ax1.clear()
    error_positivo = list(map(lambda volts: volts+0.02, volts))         #ERROR ESTIMADO DE 0.02V
    error_negativo = list(map(lambda volts: volts-0.02, volts))         #ERROR ESTIMADO DE 0.02V
    ax1.plot(ts, volts,"b-", ts, error_positivo,"r:",ts, error_negativo,"g:")   #GRAFICA CON ERRORES
    ax1.set_ylabel('Voltaje(V)')                                        #LABEL DEL EJE Y, PARA VOLTAJE
    #SEGUNDA GRAFICA, PRESION vs Tiempo
    ax2.clear()
    error_positivo = list(map(lambda preasures: preasures+0.28, preasures)) #ERROR ESTIMADO DE 0.28cm
    error_negativo = list(map(lambda preasures: preasures-0.28, preasures)) #ERROR ESTIMADO DE 0.28cm
    ax2.plot(ts, preasures,"b-", ts, error_positivo,"r:",ts, error_negativo,"g:")   #GRAFICA CON ERRORES
    ax2.set_ylabel("Presion(cmH2O)")                                        #LABEL DEL EJE Y, PARA PRESION
    #ARREGLOS.
    ax.set_xlabel("Tiempo(s)")          #LABEL EJE X, TIEMPO
    ax.set_yticklabels([])              #ELIMINAR EJE
    ax.set_xticklabels([])              #ELIMINAR EJE
    ax.set_title("GRAFICAS MPS-2107")   #TITULO DE LA GRAFICA
    plt.show()                          #MOSTRAR GRAFICO

plot()