print("Hola, por favor, ingresa un numero")
print("Ingresa '0' para salir")

contador = 0

while True:
    numero_ingresado = float(input("Numero -->"))
    if numero_ingresado > 0:
        contador += 1
    elif numero_ingresado == 0:
        break

print(f"\nLos numeros positivos ingresados fueron {contador}")
#