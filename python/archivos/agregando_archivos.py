with open("python\\archivos\\leer.txt", "a",encoding="UTF-8") as archivo:
    #Lo que hace "a" es el permiso de agregar contenido al archivo
    
    archivo.writelines(["\n"])
    #se va a agregar contenido cada vez que ejecutemos el archivo
    
    #ahora en un bucle
    #for i in range(9):
    #   archivo.writelines(f"Linea {i+1} agregada\n")

    #intento de hacer lo mismo pero en una linea de code
    intento = [archivo.writelines(f"linea {i+1} agregada\n")for i in range(4)]
    #Resultado, no me costo tanto, ya que recordaba la teoria un poco, pero tuve que buscar el archivo "mas_iteraciones.py" para recordad como era la estructura de hacer un "for i " en una sola linea de codigo