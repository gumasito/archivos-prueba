#Paquete: Es una "Carpeta" por asi decirlo, que contiene un conjunto de "modulos"/archivos.
#Para considerar a una "Carpeta", "Paquete", lo que debemos hacer es colocar un archivo .py llamado "__init__". Esto lo que va a hacer es cuando VSC busque la ruta de los subdirectorios dentro de esta carpeta, lo haga posible, ya que sin este solo va a ocasionar un error y no se va a poder encontrar los archivos

import paquete.saludar

print(paquete.saludar.saludar("jere"))