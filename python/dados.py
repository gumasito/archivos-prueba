import random
while True:
    print("-------------------")
    print("Bienvenidos a la ruleta de dados!!")
    print("Deseas lanzar los dados? -1")
    print("Mejor me voy... -2")
    print("-------------------")
    opcion = input("Elije 1/2 --> ")
    print("------------------")
    if opcion == "1":
        dados = random.randint(1,6)
        print(f"El dado salió en el número {dados}")
        print("-------------------")
        pregunta = input("Desea seguir? ").lower()
        if pregunta == "si":
            print("Ok, esta bien..")
            print("-------------------")
            continue
        elif pregunta == "no":
            print("No pasa nada :), la proxima será")
        else: 
            print("Escriba una opcion válida por favor")
            continue
    elif opcion == "2":
        print("Esta bien.. Nos vemos!")
        break
    else: 
        print("Elija una opción válida")
        continue