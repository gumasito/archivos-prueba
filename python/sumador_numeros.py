print("Bienvenidos a la sumadora-- by Guma :)")
suma = 0
while True:
    numero = int(input("Ingrese los valores a sumar ('0' para terminar la suma)--> "))
    
    if numero == 0:
        break
    suma += numero
    
print(f"La suma de los numeros ingresados es de '{suma}'")