num = 456
#t Metodo 1
lista = [int(d) for d in str(num)]
lista =[]
#t Metodo 2
for d in str(num):
    d= int(d)
    lista.append(d)
print(lista)

#! INVERSAAAA
lista = [1,2,4]
num = int("".join(map(str,lista)))
print(num)