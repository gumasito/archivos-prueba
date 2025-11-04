#"def" se encarga de establecer el inicio de una funcion propia. Luego tendriamos el nombre de la funcion, que en este caso es "saludar()". Dentro de los "()" se colocan parametros/variables que se van a tomar en cuenta a la hora de realizar la ejecucion del codigo. Estos, van a ser seteados a la hora de ejecutarse. 

#creando una funcion simple
def saludar():
    print("hola capo, como va? esta es mi primera funcion :)")

saludar()

#creando una funcion que tenga parametros
def saludo(nombre,sexo):
    sexo = sexo.lower()
    if (sexo == "mujer"):
        pp = "una girl"
    elif (sexo == "hombre"):
        pp = "un kpo"
    else: pp  = " una personita del señor"

    print(f"Hola {nombre}, como va?, este es mi primer funcion 'compleja' por asi decirlo. Eres {pp}?")
    y = input(f"... sos un {pp}?? ")
    if (y == "si", "obvio", "obvio que si", "ofc"):
        print("bien ahi, como se debe <3")
    elif (y == "no"):
        print(f"no amigo, si sos, todos somos {pp} <3")
    else: print(f"¿Como que {y}? Si eres un {pp}")
    print("...")
    print("...")
    print("...")
    x = input("¿Como estas? espero que bien, es un buen dia -->  ")
    if (x == "bien", "todo perfecto", "bien bien", "excelente"):
        print("bien ahi <3")
    elif (x == "mal"):
        print("mandame un msg, asi hablamos, no te preocupes")
    else: print("cualquier cosa, estoy para que me cuentes ;)")
    
saludo(input("cual es tu nombre?"), input("perdon por la intromicion, pero con que genero te sientes identificado?"))
#PROGRESO <3<3<3<3<3<3<3
#Pude hacer la ultima parte por mi mismo, utilizando unos inputs para hacer una funcion de una mini charla

#creando una funcion para una contraseña y devolver multiples valores
def contraseña_random():
    #lista de valores utilizados
    chars = "abcdefghijklllmnñopqrstuvwxyz0123456789ABCDEFGHIJKLLLMNÑOPQRSTUVWXYZ"
    print(len(chars))
    #cambiando el valor numerico a texto
    while True:
        try:
            num = int(input("Ingrese un valor entre el 0-9: "))
            if (num > 9):
                num = int(input("Eliga otro numero por favor: "))
            num_entero = str(num)
        except:
            print("Ingrese un valor ENTERO por favor del 0 al 9: ")
        else: break
    
    #tomando el primer valor del texto para usarlo y luego hacerlo número
    num1 = int(num_entero[0])
    
    #haciendo lo mismo con los "u1-u8"
    
    #haciendo los calculos
    while True:
            try:
                if (num1 <= 9):
                    x =int(input("Tu valor ingresado es igual o menor a 9, por ende, elige un valor entre 1-9: "))
                    #este condicional es por si las dudas
                    if (x<=9):
                        print("Prosigamos")
                    else: int(input("Tomese esto enserio porfavor --> "))
                    #me falta aprender como usar dos variables al mismo tiempo, ya que si ingreso un valor mayor al inicio, se van a poder hacer las operaciones normales, la cosa es que este mensaje aparecera
                c1 = 1 * x
                c2 = num1 //  int(input("Elegir el valor de c2 entre 0-68: "))
                c3 = num1 + int(input("Elegir el valor de c3 entre 0-58: "))
                c4 = num1 * 4
                c5 = num1 + int(input("Elegir el valor de c5 entre 0-58: ")) 
                c6 = num1 // int(input("Elegir el valor de c6 entre 0-68: ")) 
                c7 = num1 + int(input("Elegir el valor de c7 entre 0-58: ")) 
                c8 = num1 * 6
            except ValueError:
                print("Por favor, elija un numero")
            except ZeroDivisionError:
                print("Por favor, elija otro numero que no sea 0 :)")
            else:break
    #colocando los valores
    contraseña = f"{chars[c1]}{chars[c5]}{chars[c2]}{chars[c3]}{chars[c4]}{chars[c5]}{chars[c6]}{chars[c7]}{chars[c8]}{num1}"
    
    #devolviendo la contraseña pero no mostrandola aun
    return contraseña,num1
#desempaquetando 2 valores

contraseña,num =contraseña_random()

#devolviendo la contraseña y el primer numero utilizado
print(f"Perdon por la demora, pero aqui esta su contraseña {contraseña}")
print(f"Tu primer numero a utilizar fue el: {num}")
#TERMINEEEEEEE SON LAS 4:00 AMMM LA PUTA MADRE ESTUVE 1 HORA CON ESTA PORONGA MAJESTUOSAAAAAA (escuchando molchat doma :3)
#! Me di cuenta que se puede hacer lo que hice mas rapido con 5 lineas de codigo, importando "random" y "string"