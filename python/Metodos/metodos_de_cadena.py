cadena1 = 'Lorem ipsum dolor sit, amet consectetur adipisicing elit. Sit animi ab neque exercitationem fuga explicabo a suscipit culpa perferendis, officiis odio dolore aliquid cum nulla optio illum quibusdam deserunt magni?'
cadena2= "bienvenido maquinola" 

#forma de hacer una lista teniendo en cuenta una cadena "listac1 = cadena1.split(" ")""
#buscar elemento de esa lista "print(listac1[3])"
# dir: es usado para saber que se puede hacer con el contenido. print(dir(contenido))
#print(dir(cadena1))


#upper(), devuelve el texto en mayusculas. variable.upper()
mayus = cadena1.upper()

#lower(), es la inversa
minus = cadena1.lower()

#primera letra en mayusculas
primer_letra_mayus= cadena1.capitalize()

#buscamos una cadena en otra cadena, si no hay coincidencia, return -1
busqueda_find = cadena1.find("dolor")

#buscamos una cadena en otra cadena, caso de que no se encuentra, da una es excepcion ("error")
busqueda_index = cadena1.index("l")

#si es numerico, devuelve TRUE, caso contrario, FALSE (puede estar en "" y solo debe haber numeros)
es_numerico = cadena1.isnumeric()

#si es texto, devuelve TRUE, caso contrario, FALSE (el texto debe estar EN SOLO TEXTO y SIN espacios)
es_alphanumerico = cadena1.isalpha()

#contamos las coincidencias de una cadena, dentro de otra cadena, devuelve la cantidad de las mismas
contar_coincidencias = cadena1.count("a")

#contamos la cantidad de caracteres tiene una cadena (cuenta todo tipo de caracters (INCLUSO ESPACIOS))
contar_caracteres = len(cadena1)

#verificamos si una cadena empieza con otra cadena dada, si es asi, devuelve TRUE
empieza_con = cadena1.startswith("h")

#verificamos si una cadena termina con otra cadena dada, si es asi, devuelve TRUE
termina_con = cadena1.endswith("h")

#si el valor 1 se encuentra en la cadena original, reemplaza el valor 1 por el 2
cadena_nueva = cadena1.replace(" ","")

#separar cadenas con la cadena que le pasemos, formando una lista
cadena_separada = cadena1.split(" ")
cadena_separada1 = cadena_separada.index("dolor")

print(cadena_separada1)