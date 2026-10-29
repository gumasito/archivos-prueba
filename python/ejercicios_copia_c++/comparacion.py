def comparar(x,y):
    if (x>y):
        y = input("Ingrese un nuevo valor Y>> ")
        comparar(x,y)
        return f"x es {x} y es mayor a y: {y}"
    else:
        x = input("Ingrese un nuevo valor X>> ")
        comparar(x,y)
        return f"y es {y} y es mayor a x: {x}"

x= input("Ingrese primer valor X >>")
y = input("Ingrese primer valor Y >>")
comparar(x,y)