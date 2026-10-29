import pywhatkit
import time
print("=" * 30)
mensaje = input("\nIngrese tu mensaje--> ")
print("=" * 30)
print("\n")
contactos = [
    "+54 9 3498 41-8860",
    "+54 9 3425 48-7137",
    "+54 9 3498 46-2274"
]
hora = time.localtime().tm_hour
minuto = time.localtime().tm_min

while minuto >= 61:
    minuto = minuto - 60
    hora +=1
minuto +=1
for i in contactos:
# Enviar mensaje a un número (con código país, ej: +54 <b )
    pywhatkit.sendwhatmsg(i, mensaje,hora,minuto)
    minuto +=1