#crenado diccionarios con dict()
diccionario = dict(nombre = "jere", apellido = "moreira")

#las listas no pueden ser claves, y usamos "frozenset" para meter conjuntos

diccionario = {frozenset(["dato1", "dato2"]) : "jere"}

#creando diccionarios con fromkeys(), valor por defecto "none"
diccionario = dict.fromkeys(["nombre", "apellido"])

#creando diccionarios con fromkeys(), cambiando el valor a "no se"
diccionario = dict.fromkeys(["nombre", "apellido"], "no se")
print(diccionario)
