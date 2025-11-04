import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\Trabajo_general\\base_datos_juegos.csv")

#NUEVO PARCHE, AHORA PIDE LAS HORAS JUGADAS
juego_actual = input("¿A qué juego entraste? ")
cuantas_horas= float(input("Cuantas horas jugaste? "))


if juego_actual in df["Juegos"].values:
    df.loc[df["Juegos"] ==juego_actual,"Horas"] += cuantas_horas
    df.loc[df["Juegos"] == juego_actual, "Registro"] +=1
else:
    nuevo_juego = pd.DataFrame({"Juegos": [juego_actual],"Registro" : [1], "Horas" : [cuantas_horas]}) #pd.DataFrame = crear un diccionario, los contenidos nuevos agregados deben estar SI O SI en una LISTA
    
    df = pd.concat([df,nuevo_juego],ignore_index=True)
# Guardar los cambios en el archivo CSV
print("Registro Actualizado")
df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\Trabajo_general\\base_datos_juegos.csv",index=False)
