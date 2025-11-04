import random
import time
respuestas = ["si","puede ser","obvio","ofc girl","segui soñando","dios te escuche :("]
while True:
    pregunta = input("¿Que deseas preguntar? ")
    rta = random.choice(respuestas)
    print(rta)
    #En conclusion, la muestra de 5to 2024 fue una kgada, ya que hice lo mismo en 2 segundos en python
    print("Esperando 5 segundos para la proxima pregunta...")
    for i in range(5,0,-1):
        print(f"{i}...", end="\r")
        time.sleep(1)
    print("Hora de la siguiente pregunta")