lista = [1, 2 , "hola", False] #lista es una list que contiene valores que se pueden modificar
tupla = (1, 2 , "hola", False) #tupla es un tipo de variable que no se puede modificar

lista[2] = "ciao"
#tupla[2] = "adios"
print(lista) #1,2, "ciao", False 

#creando un conjunto set
conjunto = {"papa", "cebolla", "calabaza"} #se pueden rehacer, pero no sobreescribir elementos especificos.
#tampoco se pueden repetir valores

print(conjunto)

#creando un diccionario (dict)

diccionario = {
    "nombre" : "pepe argento",
    "canal" : "telefe",
    "familia" : "insoportable",
    "esta_cansado?" : True,
    "altura" : 1.60    
}

print(type(diccionario))
print(diccionario["altura"]+.05)


#listas
#metodo 1
o =["nombre",]
#metodo 2
o = list(["nombre"])

#Conjuntos set()
#metodo 1
n = set(["nombre", "moreira"])
#metodo 2
n = {"papa", "cebolla", "zapallo"}

#tuplas tuple()
#metodo 1
e= ("nombre", "moreira", 18)
#metodo 2
e = tuple(["nombre", "moreira"]) 

#diccionarios dict()
#metodo 1
s = dict.fromkeys(["nombre", "apellido", "edad", "altura", "peso"])
#metodo 2
s = {   #forma 2 de hacerlo
    "nombre" : "",
    "apellido" : "",
    "edad": "",
    "altura": "",
    "peso" : "",
    }
print()