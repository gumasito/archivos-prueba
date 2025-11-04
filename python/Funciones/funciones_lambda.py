numeros = [1,2,3,4,5,6,7,8,9]

#creando funciones lambda
multiplicar_por_dos = lambda x : x*2
print(multiplicar_por_dos(2))

#lo mismo pero con una funcion comun
def multiplicar(x):
    return x*2

#devolviendo numeros pares
def num_pares(num):
    if (num%2==0):
        return True 

#usando filter () con una funcion comun
numeros_pares = filter(num_pares,numeros)

#haciendo lo mismo pero con lambda
numeros_impares = filter(lambda numero:numero%2==1, numeros)
numeros_pares = filter(lambda numero:numero%2==0, numeros)
print(list(numeros_impares))
#explicacion de lambda: es una funcion anonima, su estructura es muy sencilla y es utilizada para hacer una operacion. su primer parametro es la variable que se va a llamar, en este caso es "numero", a "numero" se le va a dividir entre "2" y si el resto de esa operacion es "0", se envia un "True". Luego se utiliza otro parametro, que seria los datos a utilizar, en este caso es una lista con la variable "numeros"
#Con filter, lo que hacemos es utilizar SOLO los valores que se devuelvan "True" y los mostramos

def r(num):
    if(num%2==0):
        return True

rs = filter(r,numeros)
print(rs)# en este caso devuelve "filter object", algo que no entendemos. Lo que debemos hacer es colocar "lisT()" para pasarlo como lista
print(list(rs))