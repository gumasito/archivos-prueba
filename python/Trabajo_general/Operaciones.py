import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\Trabajo_general\\sisi.csv")


juego_actual = input("¿Que dia? ")


if juego_actual in df["ajam"].values:
    df.loc[df["ajam"] ==juego_actual,"dias"] += 1
else:
    nuevo_juego = pd.DataFrame({"ajam": [juego_actual], "dias" : [1]}) #pd.DataFrame = crear un diccionario, los contenidos nuevos agregados deben estar SI O SI en una LISTA
    df = pd.concat([df,nuevo_juego],ignore_index=True)
# Guardar los cambios en el archivo CSV
print("Registro Actualizado")
df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\Trabajo_general\\sisi.csv",index=False)

sns.barplot(x="ajam",y="dias",data=df)
plt.show()
