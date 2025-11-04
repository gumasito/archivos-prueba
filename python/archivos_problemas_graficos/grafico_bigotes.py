import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("python\\archivos_problemas_graficos\\bigotes.csv")

sns.boxplot(x="categoria",y="valor",data=df)

plt.show()