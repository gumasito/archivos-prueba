#creando una funcion que nos devuelva los numeros primos
#entre el 0 y el valor que querramos 

#crear una funcion que verifique si un numero es primo
def es_primo(num):
    #verificamos que el numero pasado no pueda dividirse por
    #ningun numero entre 2 y ese mismo numero -1
    for i in range(2,num-1):
        #si es divisible por alguno retornamos False y terminamos el bucle
        if (num%i==0): 
            return False
        #si termina el bucle, significa que no fue divisible y es primo
    return True
r=es_primo(20)
print(r)
#creando una funcion que retorna una lista de todos los primos
def primos_hasta(num):
    #creamos la lista
    primos= []
    no_primos = []
    for i in range (2,num+1):
    #verificamos si el valor es primo
        resultado = es_primo(i)
        #en caso de que lo sea, lo agregamos a la lista
        if resultado == True:
            primos.append(i)
        else: no_primos.append(i)    
    #devolvemos la lista
    return primos, no_primos

#creamos el resultado llamando la funcion y lo mostramos
resultado1, resultado2 = primos_hasta(30)
print(resultado1)   
print(resultado2)


#PRUEBA DE DALTO
#Opinion: Entendi la funcion de la misma, pero no supe como hacerla o resolverla (no entendi ciertos puntos, ya que no manejo perfectamente las funciones "lambda" aun, pero intentare mejorar :)), y ciertas expresiones matematicas no las se aun, asi que tambien tratare de mejorar en ello
primos1_hasta = lambda num : list(filter(lambda x:all(x%i!=0 for i in range(2,int(x**0.5) +1)), range(2,num)))

print(primos1_hasta(15))



def ines (num):
    for i in range(2,num -1):
        if (num%i==0): 
            return False
    return True

def loveu (num):
    lista = []
    for i in range(2,num +1):
        lysm = ines(i)
        if (lysm == True):
            lista.append(i)
    return lista

print(loveu(19))