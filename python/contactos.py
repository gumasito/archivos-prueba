import pandas as pd
import re
df = pd.read_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\contactos.csv")
afirmar = ["si","ofc","obvio","bueno","s","y","yes"]
negar = ["no","n","nope"]
while True:
    print("="*30)
    print("Bienvenidos a la agenda de contactos by Guma")
    print("="*30)
    print("Agregar contacto-1")
    print("Modificar contacto-2")
    print("Eliminar contacto-3")
    print("Ver lista-4")
    print("Salir-5\n")
    opcion = input("Que deseas hacer?\n")
    try:
        if opcion == "5":
            print("Gracias por venir :)")
            break
        elif opcion == "4":
            while True:
                print(df)
                seguir = input("Deseas seguir?>> ")
                if seguir in afirmar:
                    print("Prosigamos")
                else: break
        elif opcion == "1":
            while True:
                nombre = input("Ingrese el nombre>>> ")
                numero = input("Ingrese el número>>> ")
                verificar = r"\+\d{2}\s\d{4}\s\d{3}\s\d{3}"
                verificando = re.match(verificar,numero)
                if verificando:
                    print("Numero verificado :)")
                else: 
                    print("Numero erroneo\n")
                    print("Pruebe con otro numero\n")
                    print("-"*30)
                    break
                if numero in df["numero"].values:
                    print("Este contacto ya esta registrado")
                else:
                    contacto_nuevo = pd.DataFrame({"nombre" : [nombre], "numero": [numero]})
                    df = pd.concat([df,contacto_nuevo],ignore_index=True)
                    df = pd.sort_values("nombre",ascending=True)
                    df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\contactos.csv",ignore_index=True)
                    print("="*30)
                    seguir = input("Deseas seguir?>> ")
                    if seguir in afirmar:
                        print("Prosigamos\n")
                        
                    else: break
        elif opcion == "3":
            while True:
                try:
                    print(df)
                    eliminar = input("Que contacto deseas eliminar?>> ")
                    df = df[df['nombre'] != eliminar]
                    df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\contactos.csv",index=False)
                    break
                except:
                    print("Seleccione un valor correcto")
                    break
        elif opcion == "2":
            while True:
                try:
                    print(df)
                    modificar = input("Que deseas modificar? (nombre o numero)>> ").lower()
                    if modificar == "nombre":
                        indice_modificar = int(input("Seleccione el indice a modificar"))
                        nuevo_nombre = input("Ingrese el nombre nuevo>> ")
                        indice_mod = df.loc[indice_modificar, "nombre"] = nuevo_nombre
                        df.sort_values("nombre",ascending=True, inplace= True)
                        df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\contactos.csv",index=False)
                        break
                    elif modificar == "numero":
                        indice_modificar = int(input("Seleccione el indice a modificar>>"))
                        nuevo_num = input("Ingrese el numero nuevo>> ")
                        indice_mod = df.loc[indice_modificar, "numero" ]= nuevo_num
                        df.sort_values("nombre",ascending=True, inplace=True)
                        df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\contactos.csv",index=False) 
                        break
                    else:
                        break
                except:
                    print("To mal\n")
                    break
    except:
        print("Seleccione una opcion correcta")