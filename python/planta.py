import serial
import time
import matplotlib.pyplot as plt

puerto = serial.Serial('COM1', 9600, timeout=1)
time.sleep(2)

# Listas para almacenar los datos
tiempos = []
humedades = []

plt.ion()  # Habilita el modo interactivo de Matplotlib
fig, ax = plt.subplots()

while True:
    try:
        if puerto.in_waiting > 0:
            humedad = puerto.readline().decode('utf-8').strip()
            if humedad.replace('.', '', 1).isdigit():
                humedad = float(humedad)
                tiempos.append(time.time())  # Almacena el tiempo
                humedades.append(humedad)  # Almacena el valor de la humedad
                
                # Limita el número de puntos en el gráfico
                if len(tiempos) > 100:
                    tiempos.pop(0)
                    humedades.pop(0)
                
                # Grafica los datos
                ax.clear()
                ax.plot(tiempos, humedades)
                ax.set_xlabel('Tiempo')
                ax.set_ylabel('Humedad (%)')
                plt.pause(0.1)  # Actualiza el gráfico en cada ciclo

    except KeyboardInterrupt:
        print("\nSaliendo...")
        puerto.close()
        break
