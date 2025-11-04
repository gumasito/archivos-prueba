diccionario = {
    "nombre" : "jere",
    "apellido" :"moreira",
    "edad" : 17,
    "altura" : 194,
    "peso" : 106
}
#obteniendo las claves de un diccionario
for keys in diccionario:
    print(keys)
#iterar los valores de un diccionario con items()
for keys in diccionario.items():
    print(keys)

#iterar los valores de un diccionario con un indice
for keys in diccionario.items():
    key = keys[0]
    value = keys[1]
    print(f"El valor es: {value} de la clave: {key} ")