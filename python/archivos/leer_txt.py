#colocamos la funcion "open()" para abrir un archivo. En esa funcion debemos colocar la ruta del archivo a abrir, en este caso colocamos la carpeta que contiene a la carpeta contenedora de "leer.txt". Luego colocamos el atributo "encoding="UTF-8" para poder desencriptar todos los caracteres especiales que el archivo contenga"
#Igualamos la funcion a una variable y por ultimo colocamos el modulo ".read()" para leer el contenido 

#usando "open()" para abrir un archivo con una codificacion universal (UTF-8) 
archivo_sin_leer = open("python\\archivos\\leer.txt",encoding="UTF-8")

#Para poder releer un archivo, lo que se debe hacer es cerrar el archivo mismo, ya que por motivos de seguridad, se puede dañar. Por ende, a las siguientes variables las vamos a comentar solo momentaneamente para verificar si el codigo funciona


#leer el archivo completo
#archivo = archivo_sin_leer.read()

#leer linea por linea
#archivo = archivo_sin_leer.readlines()

#leer una sola linea.  Si colocamos un valor dentro de las "()", estamos diciendo la cantidad de caracteres a leer
archivo = archivo_sin_leer.readline()

#Cerrar el archivo
archivo.close()

#ahora si queremos volver a leer el archivo deseado, lo que debemos hacer el volver a hacer una variable leyendo substrayendo el mismo, ya que al cerrarlo, borramos la variable tambien. O, podemos ocupar una variable ya usada sin necesidad de volver a crear una
print(archivo)
