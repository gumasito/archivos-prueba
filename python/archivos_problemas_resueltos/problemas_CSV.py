import pandas as pd

df = pd.read_csv("python\\archivos_problemas_resueltos\\leer_CSV.csv")
#cambiar el tipo de dato de una columna

#convertir a string los datos de una columna
df["edad"] = df["edad"].astype(str)

#mostrar el tipo de dato del primer elemento de la columna edad
print(type(df["edad"][0]))

#reemplazando "jeremias" por "big guy"
df["nombre"].replace("jeremias", "big guy", inplace=True) #inplace=True lo que hace es validar el cambio

#mostrando la columna "nombre"
print(df["nombre"])

#eliminando las filas que tengan datos vacios

df = df.dropna() #parametro por defecto dentro de "dropna()" es 0 (que vendria siendo las filas), pero si queremos eleminiar las columnas, deberemos colocar "dropna(axis=1)"

#eliminando las filas repetidas
df = df.drop_duplicates()

#creando un CSV con el data frame resultante (limpio)
df.to_csv("python\\archivos_problemas_resueltos\\leer_CSV_limpio.csv")

#Se puede hacer un archivo nuevo HTML (Tambien hay muchos mas tipos de archivos)
# df.to_html("python\\archivos_problemas_resueltos\\leer_CSV_limpio.html")
