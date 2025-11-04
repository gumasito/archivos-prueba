sabores = ["umami", "salado", "dulce", "acido", "agrio"]
r2 = ["antartida","la antartida"]
r3 = "homero"
r4 = "ulan bator"
r5 = "queen"
no_se_r5 = ["cristal castle","molchat doma","laufey","junko yagami","tv girl"]
contador = 0
print("Bienvenidos al juego de preguntas by Guma :)\n")

#!Meh
pri_pre = input("Primera pregunta... ¿Cuáles son los 5 tipos de sabores primarios?\n").lower()

# Divide la respuesta del usuario en una lista
respuesta_user = pri_pre.split(",")
respuesta_user = [resp.strip() for resp in respuesta_user]
if len(respuesta_user) < 5:
    print("Aun faltan..")
    if len(respuesta_user) >=3:
        contador +=.5
    else: contador +=.1
elif any(resp not in sabores for resp in respuesta_user):
    print("Hay algo que sigue sin concluir..")
else: 
    print("Perfecto, prosigamos +1 punto\n")
    contador += 1
print("-----------")
print("Siguiente pregunta")
print("-----------")
#! Responder con solo la palabra
sec_pre= input("¿Cuál es el lugar más frío de la tierra?").lower()
if sec_pre in r2:
    print("Correcto!! +1 punto\n")
    contador += 1
elif sec_pre == "alaska":
    print("Casi, pero no (mentira, le erraste bien fiero)\n")
elif sec_pre == ["rusia","russia"]:
    print("Se asemeja, pero estamos hablando de un lugar en el otro extremo del mundo\n")
else: print("ayayay, nop:), pero bueno, la proxima seguro que le pegás\n")
print("-----------")
#! Aca no hace falta solo el autor
ter_pre = input("Quin escribio la Odisea?\n").lower()
if r3 in ter_pre:
    print("Correcto! (te felicito la verdad, no todos saben este dato :? ) +1 punto\n")
    print("Prosigamos\n")
    contador +=1
else: print("Que mal.. no le sabes")
print("----------------")
print("Siguiente pregunta")
#! Si le pega, es de ojet3
cuar_pre = input("¿Cómo se llama la capital de Mongolia?").lower()
if r4 in cuar_pre:
    print("...")
    print("Que raro, ni yo lo sabia :)")
    print("+2 puntos por este dato")
    contador +=2
else: 
    print("Wrong!!")
    print("Ahre que ni yo le pegaba")
#! Easiest one
print("--------")
print("Por ultima pero menos importante... ")
ult_pre = input("Cual es la banda fav de Guma?????????? ").lower()
if ult_pre in r5:
    print("YEYYY, felicidades por saber la obviedad dentro de lo obvio +100000000 de puntos")
    contador +=100000000
elif ult_pre in no_se_r5:
    print("Puede ser... pero hay una mas obvia.. +1 punto")
    contador +=1
else: 
    print("pegate un baño, no me conoces -1000 puntos")
    contador -= 1000
print("------------------")
print(f"El puntaje final es...  {contador}!!\n")
print("Gracias por participar en este quiz :)")
print("Vuelve pronto...")
