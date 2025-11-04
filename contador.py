s = 0
while True:
    v = int(input("Ingrese valoers, 0 para dejar de sumar"))
    s += v
    if v == 0:
        print("="*30)
        print("Resultado final ", s)
        print("="*30)
        break
    print(s)