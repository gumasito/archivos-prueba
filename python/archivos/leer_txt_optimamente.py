#abriendo el archivo con "with open()"
with open("python\\archivos\\leer.txt",encoding="UTF-8") as archivo: #archivo en este caso seria una variable random que le damos al archivo por leer. Y el valor que tiene por defecto el archivo es "read"
    #leemos el contenido
    contenido = archivo.read()
    
    #mostramos el archivo
    print(contenido)
    
#no es necesario cerrar el archivo usando "with open()"

#with open, lo que hace es evitar errores/trabajo de cerrar el archivo abierto, permitiendo una mejor optimizacion en el codigo y a la hora de trabajar