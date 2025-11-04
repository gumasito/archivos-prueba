diccionario = {
    "nombre" : "Jeremias",
    "apellido" : "Moreira", 
    "altura" : 190,
    "peso" : 105
}
diccionario_2= {
    0 : "jeremias",
    1 : "moreira",
    2 : 17,
    3 : 190,
    4 : 105
}

#obteniendo las claves/keys
claves = diccionario.keys()

#obteniendo un elemento con .get(), si no encuentra, devuelve none, y no lanza excepciones. Permitiendo que el programa pueda seguir corriendo
obtener = diccionario.get("edad")

#eliminando los elementos del diccionario
diccionario_2.clear()

#eliminando un elemento del diccionario
bye = diccionario.pop("altura")

#obteniendo elementos de un dict_items iterable
diccionario_iterable = diccionario.items()
print(diccionario_iterable)