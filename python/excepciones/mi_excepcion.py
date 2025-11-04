#Creando nuestra propia excepcion
class MiExcepcion(Exception):
    def __init__(self,err):
        print(f"Que macana, mira el error al que llamaste {err}")
#raise se utiliza para llamar a excepciones
#raise ValueError("JASJASKSAJ")
try: 
    raise MiExcepcion("jaksjkas q corki")
except: print("no pasa nada, nos pasa a todos :)")
