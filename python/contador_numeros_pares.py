contador = 0
inicio = int(input("Elige el valor inicial para contar: "))
fin = int(input("Elige el ultimo numero: "))
for i in range(inicio,fin, +1):
    if i % 2 == 0:
        contador +=1
print(f"Hay un total de {contador} numeros pares")