with open("python\\archivos\\leer.txt", "w",encoding="UTF-8") as archivo:
    #Lo que hace "w" es el permiso de escribir/sobreescribir el archivo
    
    #sobreescribiendo el archivo
    #archivo.write("holis jijis")
    
    #escribiendo el archivo
        #podemos hacer una lista/ escribir un archivo completo usando "[]"
    archivo.writelines([" - hola capo, como va? ","todo bien?\n"]) #el "\n" es la forma en la que podemos hacer salto de linea 
    
    #agregando mas lineas
    archivo.writelines([" - todo bien la vdd ", "y vos?"])