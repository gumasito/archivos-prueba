def suma():
    while True:    
        a =input("Ingrese el valor 1: ")
        b =input("Ingrese el valor 2: ")
        try:
            resultado= int(a) + int(b)
            #break
        except Exception as e: #"e" es el nombre general que se le dan a las excepciones
            print("Ingrese los valores correctamente por favor :)")
            print(f"El ERROR es: {e}")
        else: break
        finally: 
            print("(: ----------------------------- :)")
    return resultado

print(suma())
#EXPLICACION: La forma en la que las excepciones funcionan es "sencilla" (por ahora D:), ya que podemos colocar un bucle "while = True" y dentro poner una operacion llamada "Try"(su funcion basicamente es intentar en hacer la operacion sin importar si un dato esta mal ingresado) y "Except" (caso de que "try" no se pueda cumplir, se pasa el except). En el except podemos poner un mensaje para dar aviso al operador que esta haciendo algo mal, luego el programa va a volver a correr y el usuario debera ingresar bien los valores.
#En un intento de deal con una excepcion, se puede poner un "else", ya que es recomendable que si el "while = True" pasa al "else" para "breakear" la funcion y retornar la data que querramos.
#Caso de que el "while = False" se van a volver a pedir los datos para hacer otra vez las operaciones
#FINALLY es una parte de la operacion de delear con excepciones que se ejecutara SIEMPRE, sin importar las excepciones, SIEMPRE va a ejecutarse
#Tambien se puede tratar con las excepciones dentro de las excepciones, por ejemplo, podemos mostrar al usuario cual fue el error que cometio