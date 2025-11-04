#importando las librerias
import pandas as pd
import matplotlib.pyplot  as plt
import seaborn as sns

#leyendo el archivo "".csv"
df = pd.read_csv("python\\archivos_problemas_graficos\\artistas_escuchados.csv")

#Creando un grafico de barras 
sns.barplot(x="Artistas", y="Veces_Escuchados", data=df)

#sumando las horas escuchadas (podemos sumar los valores de una linea)
total_escuchado = df["Veces_Escuchados"].sum()

#mostrando la suma
print(f"el total escuchado fue de--> {total_escuchado} horas")

#mostrando el grafico en barra
plt.show()