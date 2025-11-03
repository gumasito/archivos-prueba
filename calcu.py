def calcu():
    while True:
        print("=" * 30)
        print("Ingrese 0 para terminar")
        n = input("Ingrese valores>> ")
        if (n == "0"):
            break
        try:
            r = eval(n)
            print(f"Resultado {r}")
        except:
            print("Expresionnnnn incorrecta, ingrese un valor correspondiente")

calcu()