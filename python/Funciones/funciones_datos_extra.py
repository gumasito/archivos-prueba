#parametros ordenatorios (se colocan segun el orden que aparecen)
def frase(nombre,apellido,adjetivo):
    return f"hola {nombre} la {apellido}, sos muy {adjetivo} :)"
#parametros de palabra clave, se pueden cambiar de posicion si es que colocamos el nombre de la variable y su valor (deberemos hacerlo con todos los valores si es que ponemos uno)
resultado = frase(adjetivo = "insoportable", apellido = "cerdita", nombre = "peppa")
print(resultado)

#creando una funcion con un parametro opcional (adjetivo) con un valor por defecto ("malo")
def frasesita(nombre,apellido, adjetivo ="malo"):
    return f"hola {nombre} {apellido}, sos muy {adjetivo}"
resultado1 = frasesita("jere", "moreira", "alto")
print(resultado1)
#se pueden cambiar las variables forzadas (y no hay problema de colocar una variable en la respuesta, ya que estamos cambiando el valor puesto con anterioridad). EJ (adjetivo="#palabra")
