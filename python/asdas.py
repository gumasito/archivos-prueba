import random

print("Hola, bienvenidos al juego de adivinar el numero secreto (1-100). Tienes 10 intentos para adivinarlo, suerte :)")
numero_secreto = random.randint(1,100)
intento = 0

while True:
    adivinanza = int(input("Adivina el numero :) -->  "))
    intento +=1
    print("-----------------------")
    print(f"Intento N°{intento}, dale que podes :)")
    print("-----------------------")
    if intento == 10:
        print("Que lastima :c, perdiste. Suerte la proxima vez :3")
        break
    if adivinanza == numero_secreto:
        print("Felicidades, adivinaste el numero Secreto!!!")
        print(f"Tardaste {intento} intentos para adivinarlo :)")
        break
    elif adivinanza > numero_secreto:
        print("Cuidado, el numero secreto es mas chico :)")
    else: print("El numero secreto es mas grande :o")
