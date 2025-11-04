from googletrans import Translator
translator = Translator()
si = ["si","y","yes","bueno","dale"]
no = ["no","n","chau","ciao"]
while True:
    try:
        print("\n" + "=" * 30)
        print("       TRADUCTOR by Guma      ")
        print("=" * 30 + "\n")
        texto = input("Ingresa un texto a traducir... \n").capitalize()
        print ("Elige el idioma a traducir!!")
        idiomas = {
            "1":"es",
            "2": "en",
            "3": "fr",
            "4": "ru",
            "5": "ja"
        }
        print ("Español- 1")#? origen
        print ("Ingles- 2")#? Poner a prueba
        print ("Frances- 3")#t no
        print ("Ruso- 4")#t no
        print ("Japones- 5")#t no
        print("="*30)
        leng = input("Elige una opcion válida\n").strip()
        if leng in idiomas:
            try:
                txt_traducido = translator.translate(texto, dest=f"{idiomas[leng]}")
                print(f"Texto traducido: {txt_traducido.text}")
                proseguir = input("Desea proseguir?\n").lower()
                if proseguir in si:
                    continue
                elif proseguir in no:
                    print("="*30)
                    print("Gracias por usar el traductor by Guma :)")
                    break
                else:
                    print("No se que dijiste, pero te mando otra vez al inicio")
                    continue
            except Exception as e:
                print(f"Error al traducir: ",e)
        else:
            print("Opcion invalida, intente de nuevo ")
    except ValueError:
        print("Ingrese un valor válido por favor ]:)")
        continue
        #Esta es la base principal, luego lo que haria seria desarrollarlo un poco mas en un futuro (ahr q ahora a la noche lo hago)