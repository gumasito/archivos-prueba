def capicua(n):
    valor = str(n)
    valorlon = len(valor)
    for i in range(valorlon//2):
        if valor[i] != valor[-i-1]:
            print("No")
        else:print("si")

capicua(1014101)