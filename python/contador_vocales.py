palabra = input("Ingrese una palabra, y te devolveré las vocales que tenga: ").lower()
contador_vocales = 0
for vocales in palabra:
    if vocales in "aeiouáéíóú":
        contador_vocales +=1

print(contador_vocales)