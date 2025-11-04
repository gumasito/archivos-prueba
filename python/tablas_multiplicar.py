print("Bienvenidos a la herramienta de Guma :) para las tablas")
while True:
    print("--------------")
    print("Multiplicar hasta 10- 1")
    print("Multiplicar hasta 100- 2")
    print("Salir :)- 3")
    print("---------------")
    opcion = input("Ingrese un valor (1-3)--> ")
    if opcion == "1":
        numero = int(input("Ingrese el numero a multiplicar--> "))
        print("----------------")
        if numero >= 0:
            for i in range(0,11):
                respuesta = print(f"{numero} * {i} = {i*numero}")
                continue
        else: 
            print("Ingrese un numero valido..")
            print("-------------")
            continue
    elif opcion == "2":
        numero = int(input("Ingrese el numero a multiplicar--> "))
        print("----------------")
        if numero >= 0:
            for i in range(0,101):
                respuesta = print(f"{i} * {numero} = {i*numero}")
                continue
        else: 
            print("-------------")
            print("Ingrese un numero valido..")
            print("-------------")
            continue
    elif opcion == "3":
        print("Gracias por haber entrado :)")
        print("----------")
        break