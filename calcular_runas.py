
def contando():

    enemigos = []
    cantidad =[]
    # Carga de valores hasta ingresar 0
    while True:
        try:
            valor = int(input("Ingrese valor por enemigo (0 para terminar) --> "))
        except ValueError:
            print("Entrada inválida. Ingrese un número entero.")
            continue
        if valor == 0:
            break
        if valor > 0:
            enemigos.append(valor)
        else:
            print("El valor debe ser positivo o 0 para terminar.")

    if not enemigos:
        print("No se ingresaron enemigos. Nada para calcular.")
        return

    while True:
        print(enemigos)
        for i in enemigos:
            cantidad_enemigos = int(input(f"Cuantos enemigos hay de {i}? "))
            cantidad.append(cantidad_enemigos)
        break
    # Selección de bonus
    print("=" * 30)
    print("Tipos de bonus -->")
    print("1 - Patas de ave macerada en oro (+20%)")
    print("2 - Escarabajo dorado (+30%)")
    print("3 - Ambos (+50%)")

    bonus1 = 0
    bonus2 = 0
        
    while True:
        try:
            bonus = int(input("Ingrese una de las opciones [1-3] --> "))
        except ValueError:
            print("Entrada inválida. Ingrese 1, 2 o 3.")
            continue
        if bonus == 1:
            bonus1 = 20
            break
        elif bonus == 2:
            bonus2 = 30
            break
        elif bonus == 3:
            bonus1 = 20
            bonus2 = 30
            break
        else:
            print("Opción fuera de rango. Ingrese 1, 2 o 3.")

    porcentaje_total = bonus1 + bonus2

    total_general = 0
    print("=" * 30)
    for i,j in zip(enemigos,cantidad):
        total = (porcentaje_total * i*j) / 100 + i*j
        total_general += total
        print(f"Enemigo de'{i}' con total de '{j}'dropea -> {total:.2f} (con {porcentaje_total}% de bonus)")

    print("-" * 30)
    print(f"Total general: {total_general:.2f}")


if __name__ == "__main__":
    try:
        contando()
    except Exception as e:
        # Mensaje genérico sin silenciar errores durante desarrollo
        print("Ocurrió un error inesperado:", e)
