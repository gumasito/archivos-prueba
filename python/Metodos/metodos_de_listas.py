lista = 'Lorem ipsum dolor sit, amet consectetur adipisicing elit. Sit animi ab neque exercitationem fuga explicabo a suscipit culpa perferendis, officiis odio dolore aliquid cum nulla optio illum quibusdam deserunt magni?'
lista_linda = lista.split(" ")
print(len(lista_linda))
#creando una lista con list()

lista1 = list(["hola", "papa","calabaza", "zapallo", 310, False])
cantidad_elementos = len(lista1)

#agregando un elemento a la lista
lista1.append("jasksasa")

#agregando un elemento a la lista en un indice especifico 
lista1.insert(0, "ciao")

#agregar varios elementos a una lista
lista1.extend(["cebolla", "rabanito"])

#eliminando un elemento de una lista a traves de su indice
lista1.pop(1) #para eliminar el ultimo elemento de una lista, se debe colocar "-1" penultimo "-2" y asi sucesivamente

#eliminando un elemento de la lista por su valor
lista1.remove("ciao")

#eliminando todos los elementos de la lista
lista1.clear()

#ordenando los elementos de una lista de orden ascendente (CUIDADO, no pueden haber texto)
lista2= list([31 ,4, 414, 100, 1.3, 5.514,False, True])
lista2.sort() #cambia el orden de los valores de la lista (los False siempre van primero, dsp los True y asi con los numeros) Tambien se puede poner sort(reverse=true) para ordenar inversamente

#revertir el orden de los elementos ORIGINALES
lista2.reverse()
#buscar elementos en una lista :3

buscar = lista1.index("zapallo")
print(lista2)