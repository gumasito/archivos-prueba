#importando pandas y otras librerias para crear graficos y abrir archivos
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
#abriendo el archivo ".csv"
df = pd.read_csv("python\\archivos_problemas_graficos\\flores_vistas.csv")
#crenado el grafico
sns.lineplot(x="Fecha",y="Flores_Vistas",data=df)# "x = VALOR de la linea X", "y = VALOR de la linea Y", "data = de donde saca los valores"

#haciendo un punto (como tambien podemos poner una "x") en el punto deseado
plt.plot("7-1",5,"o ")

#mostrando el grafico
plt.show()
