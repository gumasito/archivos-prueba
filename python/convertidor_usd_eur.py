print("\nConversor de moneda")
eur_usd = 1.09
usd_eur = .92
while True:
    try:
        print("Seleccione una opcion: ")
        print("Convertir Dolar a Euro- 1")
        print("Convertir Euro a Dolar- 2")
        print("Salir- 3")
        
        opcion = input("Elige una opcion (1-3)--> ")
        if opcion == "3":
            print("------------------")
            print("Vuelve pronto :)")
            break
        elif opcion == "1":
            moneda = float(input("Ingrese la cantidad en USD: "))
            resultado = moneda * usd_eur
            print("------------------")
            print(f"{moneda} USD son {resultado:.2f} Euros")
            print("------------------")
            break
        elif opcion == "2":
            moneda = float(input("Ingrese la cantidad en Euros: "))
            resultado = moneda * eur_usd
            print("------------------")
            print(f"{moneda} Euros son {resultado:.2f} USD")
            print("------------------")
            break
        else: 
            print("Eliga una opcion valida")
            print("------------------")
            continue
    except ValueError:
        print("------------------")
        print("Sea serio porfa")
        print("------------------")
        continue
    