lista = ["verduras","carnes","pescados","frutas","postres"]
for comidas in enumerate(lista):
    indice = comidas[0]
    comida = comidas[1]
    print(f"el topic es '{comida}' con el numero '{indice}'")
#? Esto me parece una practica util, ya que le podemos dar una enumeracion a los items de una lista