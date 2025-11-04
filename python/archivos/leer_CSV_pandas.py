import pandas as pd #pd es una abreviacion de "pandas"

#pandas es una libreria, que nos permite hacer varias cosas con los archivos ".CSV". Esta debe ser descargada a traves de CMD: "pip install pandas"
#data: "df" es una abreviacion de "Data Frame", que basicamente podemos decir que es una cuadrilla de calculo ("excel")

#usando la funcion read_csv() para leer los datos del archivo.csv

#se pueden cambiar los encabezados del archivo. Pero e  sos encabezados que estaban antes se pasaran a ser parte del archivo. ¿como se hace? despues de colocar la ruta del archivo a leer se escribe ", names= ["#columna1","columna2","#columna3","#columaN°"]"
df = pd.read_csv("python\\archivos\\leer_CSV.csv")
df2 = pd.read_csv("python\\archivos\\leer_CSV.csv")

#obteniendo todos los datos 
print(df)

#obteniendo los datos de la columna "nombre"
nombres =df["nombre"]

#metodo slicing (es una forma de obtener valores en una cadena, lista o tupla)

cadena = [0,1,2,3,4,5,6,7,8,9]

#print(cadena[:5])

#ordenando el data frame por la edad(tambien podemos hacerlo por el nombre o cualquier otro valor)
df_ordenado = df.sort_values("edad")

#ordenando el data frame por la edad(tambien podemos hacerlo por el nombre o cualquier otro valor)

df_ordenado_reverse =df.sort_values("edad", ascending=False)
#print(df_ordenado_reverse)

#concatenando los data frames
df_concatenado = pd.concat([df,df2])


#accediendo a las 3 primeras filas con .head()

primer_fila = df.head(3)

#accediendo a las 3 ultimas filas con .tail()

ultima_fila =df.tail(3)

#accediendo a la cantidad de filas y columnas con ".shape"
#desempaquetamos

filas_totales,columnas_totales = df.shape

#otra forma es...

filas_y_columnas_totales = df.shape
filas_totales = filas_y_columnas_totales[0]
columnas_totales=filas_y_columnas_totales[1]

#accediendo a un elemento especifico del DF con loc

#lo que hacemos aca es "localizar" un elemento, que en este caso es el "nombre" en la fila "4"
elemento_especifico_loc = df.loc[4,"nombre"]

#accediendo a un elemento especifico del DF con iloc
#esto es similar al "loc", pero la diferencia es que en vez de usar el nombre de la columna, usamos su posicion (que en este caso "nombre", es 0)
elemento_especifico_iloc =df.iloc[4,0]

#accediendo a todas las filas de una columna
#en este caso, usamos ":" para tener en cuenta a todos los valores, y luego usamos el valor del indice al que estamos accediendo (en este caso es "edades" = 2)
edades = df.iloc [:,2]

#accediendo a la fila 3 con loc
fila_3 = df.loc [2, :]

#accediendo a la fila 3 con iloc
fila_3 = df.iloc [2, :] #basicamente es lo mismo, ya que funciona con indices

#accediendo a valores con condicionales
df_condicionales = df.loc[df["edad"]>=17,:]
print(df_condicionales)