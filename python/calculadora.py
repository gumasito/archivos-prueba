print("Bienvenido a la calculadora made by Guma :)")
print("--------------------------------")
posibles_valores = ["1","2","3","4","5"]
valores_positivos = ["si","puede ser","y","yes","ofc"]
valores_negativos = ["no","n","nope","bye","exit"]
while True:
    try:
        print("Seleccione la operación a realizar")
        print("Suma- 1")
        print("Resta- 2")
        print("Multiplicacion- 3")
        print("Division- 4")
        print("Salir -5")

        opcion = input("\nElige un valor(1-5): \n")
        if opcion not in posibles_valores:
            print("------------")
            print("Elije un valor valido por favor :)")
            print("------------")
            continue
        if opcion == "5":
            print("------------")
            print("Adios! Vuelve pronto")
            break
        primer_numero= float(input("Ingrese el primer numero: \n"))
        segundo_numero= float(input("Ingrese el segundo numero: \n"))
        if opcion == "1":
            print("------------")
            print(f"Resultado de {primer_numero} + {segundo_numero} = {primer_numero + segundo_numero}")
            print("------------")
            pregunta= input("¿Deses continuar?").lower()
            print("------------")
            if pregunta in valores_positivos:
                continue
            elif pregunta in valores_negativos: 
                print("Gracias, nos vemos :)")
                print("------------")
                break
        if opcion == "2":
            print("------------")
            print(f"Resultado de {primer_numero} - {segundo_numero} = {primer_numero - segundo_numero}")
            print("------------")
            pregunta= input("¿Deses continuar?").lower()
            print("------------")
            if pregunta in valores_positivos:
                continue
            elif pregunta in valores_negativos: 
                print("Gracias, nos vemos :)")
                print("------------")
                break
        if opcion == "3":
            print("------------")
            print(f"Resultado de {primer_numero} * {segundo_numero} = {primer_numero * segundo_numero}")
            print("------------")
            pregunta= input("¿Deses continuar?").lower()
            print("------------")
            if pregunta in valores_positivos:
                continue
            elif pregunta in valores_negativos: 
                print("Gracias, nos vemos :)")
                print("------------")
                break
        if opcion == "4":
            if segundo_numero != 0:
                print("------------")
                print(f"Resultado de {primer_numero} / {segundo_numero} = {primer_numero / segundo_numero}\n")
                print("------------")
                pregunta= input("¿Deses continuar?").lower()
            print("------------")
            if pregunta in valores_positivos:
                continue
            elif pregunta in valores_negativos: 
                print("Gracias, nos vemos :)")
                print("------------")
                break
            else: print("ERROR: Ingrese otro valor, no se puede dividir por 0\n")
    except ValueError: 
        print("------------")
        print("Ingrese un valor valido")
        print("------------")