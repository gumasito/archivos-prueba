#recorriendo la lsita animales
animales = {"erizo", "loro", "gato", "perro"}
for animal in animales:
    print(f"el animal es: {animal}")
#recorriendo la lista de  numeros y multiplicando cada valor por 1.5
numeros = [1,31,4.15,19]

for numero in numeros:
    resultado = numero * 1.5  
    print(round(resultado,1))

#recorriendo dos conjuntos simultaneamente (ambas conjuntos deben tener la misma cantidad de elementos para ser leidas simultaneamente)
for animal,numero in zip(animales,numeros): #el orden que ingresemos las variables, seran el orden que salgan
    print(f"recorriendo conjunto 1: {animal}")
    print(f"recorriendo conjunto 2: {numero}")

#forma para printear los numero de un rango de mismos o hasta el num (2 valores, printea valores entre medio, 1 valor, empieza de 0 hasta el numero)
for num in range(5):
    print(num)

#forma no optima de recorrer una lista/tupla. NO FUNCIONA EN CONJUNTOS
for num in range(len(numeros)):
    print(numeros[num])
#forma correcta de recorrer una conjunto con su indice
for num in enumerate(numeros): #enumerate() convierte los datos en tupla, por ende se puede colcoar un indice para recorrer
    indice= num[0]
    valor = num[1]
    print(f"el indice del numero es: {indice} y el valor es: {valor}")
#Desempaquetando valores dentro de un bucle
for num in numeros:
    primero, segundo, tercero, cuarto = numeros
    print(f"el indice del numero es: {tercero}")

#SOLUCION: debemos colocar las variables de los valores de LA VARIABLE MADRE, a la que estamos llamando, en este caso es "numeros", de la forma en la que muestra. "primero es igual al numero de indice [0] en la variable "numeros", segundo es el numero de indice[1] y asi sucesivamente"

#usando el else
for numero in numeros:
    print(f"el valor es: {numero}")
else: print("el bucle temrino")

#TODO LO ANTERIOR FUNCIONA IGUAL CON TUPLAS Y LISTAS