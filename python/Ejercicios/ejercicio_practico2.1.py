#Falto el profe y los chicos van a tener que hacer la clase

#funcion para tener el asistente y el profesor
def obtener_compañeros(cantidad_compañeros):
    
    
    #creando la lista de los compañeros
    compañeros= []
    
    #ejecutando un for para pedir la lista de los compañeros
    for i in range (cantidad_compañeros):

        nombre = input("Ingrese el nombre del compañero: ")
        edad = int(input("Ingrese la edad del compañero: "))
        compañero = (nombre,edad)
        
        #agregando la informacion a la lista
        compañeros.append(compañero)
        
        #ordenamos de menor a mayor segun la lista (edad) #x es una variable random para ejecutar los valores de la tupla [1] (en este caso es X)
    compañeros.sort(key=lambda x:x[1])
    
    #accedemos al primer valor de la tupla para definirlo como asistente, y al ultimo como el profesor
    asistente = compañeros[0][0]
    profesor = compañeros [-1][0]
    
    #retornamos una tupla
    return asistente, profesor

#desempaquetamos lo que nos retorna la funcion
a,p =obtener_compañeros(3)

#mostramos el resultado :p
print(f"el profesor es {p} y el asistente es {a}")