import pandas as pd
df = pd.read_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tienda_pokemon\\lista_productos.csv")
afirmaciones = ["si","s","yes","y"]
negaciones = ["no","n"]
estar = ["voy a quedarme","me quedo","stay","no me voy","si","bueno,me quedo","quedo"]
irse = ["ir","me voy","me iré","me ire","me voy a ir yendo"]
print("Hola! Bienvenido a la tienda pokemon -- by Guma :)")


df["cantidad"] = df["cantidad"].astype(int)

while True:
    try:
        print("\n")
        print("Que deseas hacer?\n")
        print("Comprar- 1")
        print("Vender- 2")
        print("Hablar- 3")
        print("Salir- 4\n")
        #secreto "sec"
        opcion = input("Elige el numero (1-4): \n")
        if opcion == "4":
            print("Vuelve cuando antes! :), nos vemos")
            break
        
        elif opcion == "1":
            print(df)
            compra = input("Que desea comprar?\n")
            #PARCHE, ahora si no pones un producto disponible, te dice que pongas uno y vuelve al menu principal
            
            if compra not in df["productos"].values:
                print("----------------")
                print("Por favor, eliga algo de los productos disponibles :)")
                continue
            cantidad_compra = int(input("Cuantos deseas comprar?: \n"))
            #Este es un nuevo parche, stock o no
            if cantidad_compra == 0:
                print("---------------------")
                print("Elige una cantidad valida :)")
                continue
            
            if compra in df["productos"].values:
                #parche
                cantidad_disponible = df.loc[df["productos"] == compra, "cantidad"].values[0]
                
                if cantidad_compra > cantidad_disponible:
                    print("No hay suficiente stock disponible, por favor, eliga otra cantidad")
                    continue
                #termina parche 
                df.loc[df["productos"] == compra,"cantidad"] -= cantidad_compra
                #// Filtra si los productos tienen cantidad, caso de que haya stock, los mantiene en la lista, caso contrario, los elimina
                df = df[df["cantidad"] > 0]
                
                df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tienda_pokemon\\lista_productos.csv",index=False)
                
                pregunta=input("Deseas algo mas? ")
                #t parche nuevo, en vez de colocar el mismo codigo, puedo solo poner "continue para volver"
                if pregunta in afirmaciones:
                    continue
                elif pregunta in negaciones:
                    print("------------")
                    estar_o_no = input("Desea seguir recorriendo al tienda o desea retirarse? ").lower()
                    #// Si quiero colocar una frase para despedirme como "me voy a ir yendo" y si quiero poner una palabra como clave para retirarme, la debo colocar en una variable como str y no list. Por ende, no puedo colocar un conjunto de palabras claves
                    #// En este caso solo voy a poder colocar las palabras en la lista para poder ejecutar los comandos como se debe, caso de que no se cumpla, el bucle volverá al inicio
                    if estar_o_no in estar:
                        print("-----------")
                        print("Dale, no hay apuros :)\n")
                        print("------------")
                    elif estar_o_no in irse:
                        print("------------")
                        print("Gracias por venir, nos vemos ;)")
                        break
                else: print("Elija una opcion valida por favor :)")
            
            else: 
                print("Eliga una opcion valida\n")
                print("---------------------")

        
        elif opcion == "2":
            producto = input("Que deseas vender? \n").capitalize()
            precio = int(input("A que precio deseas venderlo? \n"))
            cantidad_producto = int(input("Cuantos deseas vender? \n"))
            if cantidad_producto > 10 and precio >= 60:
                while True:
                    try:
                        print("Uyuyuy... no te parece medio carito??")
                        rebajar = input("No te parece mejor bajar un poquito el precio?").lower()
                        if rebajar in afirmaciones:
                            nuevo_precio = int(input("Dale gracias por entender ¿A cuanto le pones el precio?"))
                            if nuevo_precio >= 60:
                                print("Yo que vos vuelvo a mirar eso..")
                                continue
                            elif nuevo_precio < 60:
                                print("Gracias por la generosidad :)")
                                precio = nuevo_precio
                                break
                            else: print("Por favor, ingrese un valor")
                    except ValueError:
                        print("Ingrese un valor válido")
                        continue
            else: 
                print("------------")
                print("Me parece un precio justo, sisi")
                print("------------")
            if producto in df["productos"].values:
                print("--------------------------")
                print("Este producto ya esta en la lista ;)\n")
                print("--------------------------")
            else: 
                nuevo_producto =  pd.DataFrame({"productos":[producto], "precio $" : [precio], "cantidad" : [cantidad_producto]})
                df = pd.concat([df,nuevo_producto],ignore_index=True)
                df = df.sort_values("productos",ascending=True)
                df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tienda_pokemon\\lista_productos.csv",index=False)
                estar_o_no = input("Desea seguir recorriendo al tienda o desea retirarse? \n").lower()
                if estar in estar_o_no:
                    print("-----------")
                    print("Dale, no hay apuros :)\n")
                    print("------------")
                elif irse in estar_o_no:
                    print("------------")
                    print("Gracias por venir, nos vemos ;)")
                    break
                
        elif opcion == "3":
            charla1 = input("¿Como estas?").lower()
            if (charla1 in ["bien","perfecto","todo piola","re bien"]):
                print("---------------------")
                print("\nMe encanta, me parece perfecto, te felicito\n")
            elif (charla1 in ["mal", "no tan bien", "horrible", "un poquito mal"]):
                print("---------------------")
                print("\nUff, que mal bld, cualquier cosa hablame :)\n")
            else:
                print("---------------------")
                print("\nepa, bueno.. ponete de buen humor :). Btw, que lindo outfit que llevas, love it <3")
        #opcion secretea "solo admin :3"
        elif opcion == "sec":
            df["cantidad"] = 30 #HACER UN RESTOCK A 30 de todos los productos
            df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tienda_pokemon\\lista_productos.csv",index=False)
        else: 
            print("-----------------------")
            print("Eliga una opcion correcta\n")
            print("-----------------------")
    except ValueError as Ve:
        print("Intente otra vez por favor, evite errores")