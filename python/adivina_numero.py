import random
numero_secreto = random.randint(1,20)
max_intentos= 5
intentos = 0
while intentos < max_intentos:
        jugador = int(input("ingrese un valor entre 1-20: "))
        intentos += 1
        print(f"intento N°{intentos}")
        if jugador == numero_secreto:
            print("Felicidades, haz ganado :)!!!")
            pregunta = input("Desea seguir jugando?(s/n)--> ").lower()
            if pregunta == "s":
                continue
            else: break
        elif jugador < numero_secreto:
                print("El numero es mas grande :o")
        elif intentos == max_intentos and jugador != numero_secreto:
            print("Que lastima, haz perdido :( ")
        else: 
            print("El numero es mas pequeño :(")
            pregunta2 =input("Deseas seguir jugando?(s/n) --> ").lower()
            if pregunta2 == "s":
                continue
            elif pregunta2 =="n":
                print("Gracias por participar, nos vemos :)")
            else:  
                print("No se que dijiste, pero bueno, puedes repetirlo?")
                continue

        