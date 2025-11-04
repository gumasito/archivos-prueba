frutas = "manzana", "frutilla", "melon", "pomelo", "uvas", "banana"
texto = "hola peppa"
num = [1,2,3,4,5,6,7,8,9,10]
print("---------------------")

#evitando que se coma un pomelo con "continue"
for fruta in frutas:
    if fruta == "pomelo":
        continue
    print(f"me voy a comer un(a) {fruta}")
print("---------------------")
#evitar que el bucle siga ejecutandose con "break" (else no se ejecuta si se encuentra con "break")
#forma 1
for fruta in frutas:
    if fruta == "uvas":
        break
    print(f"me voy a comer un(a): {fruta} ")
print("Me duele la panza, no como mas :p")
print("---------------------")

#forma 2
for fruta in frutas:
    print(f"me voy a comer un(a): {fruta} ")
    if fruta == "uvas":
        break
print("Me duele la panza, no como mas :p")
print("---------------------")

#iterar una cadena de texto
for letra in texto:
    print(letra)

#for en una sola linea de codigo
num_duplicados = [x*2 for x in num]
print(num_duplicados)




























#realizar un calculo con for
numeros_duplicados = list()
for numero in num:
    numeros_duplicados.append(numero*2)
print(numeros_duplicados)
