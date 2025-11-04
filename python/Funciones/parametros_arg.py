#FORMA NO OPTIMA DE SUMAR VALORES. ¿como funciona? RTA: es un bucle donde num_sumados es la base para hacer la operacion, y num son los valores ingresados. La operacion va sumando numero a numero hasta que termine el bucle
def suma(lista):
    num_sumados= 0
    for num in lista:
        num_sumados = num_sumados + num
    return num_sumados
resultado =suma([5,5,10,20])
print(resultado)

#Forma optima de sumar valores utilizando el parametro arg *
def suma(nombre, *num): #lo que hace "*" es colocar todos los valores en una tupla y despues sumarlos
    print(type(num))
    return f"Hola {nombre}, la suma de tus numeros es--> {sum(num)}"
resultado = suma("jere", 3,12,41,51)
print(resultado)
#desventaja, no se pueden colocar mas parametros despues de los numeros, ya que, la funcion los va a tomar parte de la variable "*variable". Por ende, siempre deberemos colocar la misma como ultima para evitar confusiones

#forma optima de sumar valores
def suma_total(num):
    return sum([*num])
resultado1 = suma_total([1,23,41,1])
print(resultado1)
#explicacion de lo de arriba: lo que hace es tomar los valores ingresados de una LISTA para poder hacer la suma, caso de que no esten en lista va a dar error. luego lo que hace es tomar la variable num y recien ahi es convertir la lista a una tupla, para luego si poder sumar los numeros.Ventaja, se pueden colocar mas parametros despues de la lista.

#forma mas eficiente
def s(*num):
    return sum(num)
resultado2 = s(1,23,1,41)
print(resultado2)