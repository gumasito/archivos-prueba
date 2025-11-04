lista_numeros = [1,3,5,7,9]
lista2 = [2,4,6,8,10]
lista_nueva = []
no_numeros = []
for i in lista2:
    if i not in lista_numeros:
        lista_nueva.append(i)
lista_nueva.extend(lista_numeros)
lista_nueva.sort()
print(lista_nueva)