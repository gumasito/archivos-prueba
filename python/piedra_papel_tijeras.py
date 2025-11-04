import random
opciones = ["papel","tijeras","piedra"]

while True:
    print("------------------------")
    jugador = input("Elige piedra, papel o tijeras ('salir' para terminar el juego): ").lower()
    print("------------------------")
    if jugador == 'salir':
        print("Gracias por estar :), vuelve pronto")
        break
    computadora = random.choice(opciones)
    print("------------------------")
    print(f"La computadora ha elegido {computadora}")
    print("------------------------")
    if jugador == computadora:
        print("Empate!!")
    elif (jugador == "tijeras" and computadora == "papel") or \
        (jugador == "papel" and computadora == "piedra") or \
        (jugador == "piedra" and computadora == "tijeras"):
            print("Has ganado !!!")
    elif jugador not in opciones:
        print("Elige una opcion valida")
    else: print("Haz perdido :c")