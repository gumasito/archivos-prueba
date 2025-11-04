import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.read_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\python\\Trabajo_general\\base_datos_juegos.csv")
sns.barplot(x="Juegos",y="Horas",data=df)

plt.show()