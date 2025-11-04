import re #"re" es el modulo oficial para trabajar con las expresiones regulares

texto = '''Lorem ipsum dodoooododolor sit,414 amet consectetur adipisicing elit.   Sit animi ab neque 
exercitationem fuga explicabo a susc$#ipit culpa perferendis, officiis odio dolore aliquid cum
nulla optio illum quibusdam deserunt 42agni?'''

#".findall" encuentra todas las coincidencias en una cadena de texto
resultado = re.findall("do",texto,flags=re.IGNORECASE)

#En python, las mayusculas son lo contrario de las minusculas. Los ejemplos a continuacion lo explican

#\d --> busca digitos numericos del 0-9
resultado = re.findall(r"\d",texto) #"r" en este caso lo que hace es permitir usar expresiones regulares

#\D --> busca TODO menos digitos numeros
resultado = re.findall(r"\D",texto)

#\w --> busca todos los caracteres alfanumericos (a-z, A-Z,0-9, _)
resultado = re.findall(r"\w",texto)

#\W --> busca TODO menos los caracteres alfanumericos (espacios y caracteres especiales)
resultado = re.findall(r"\W",texto)

#\s --> busca los espacios, tabs, saltos en linea
resultado = re.findall(r"\s",texto)

#\S --> busca TODO menos los espacios, tabs, saltos en linea
resultado = re.findall(r"\S",texto)

#\n --> busca los saltos en linea
resultado = re.findall(r"\n",texto)

#. --> busca TODO menos los saltos en linea
resultado = re.findall(r".",texto)

#\ --> cancelas caracteres especiales, cancelando la funcion del punto y buscando puntos
resultado = re.findall(r"\.", texto) #podemos buscar cualquier cosa si es que utilizamos el "\" antes de lo deseado a buscar

#DATO, podemos buscar  varios parametros en una sola misma busqueda (SOLO VA A SER POSIBLE SI, estos parametros se encuentran igual en la cadena de texto)
#armando una cadena que busque un numero, seguido de un punto y un espacio
resultado = re.findall(r"\w\W\s",texto)

#^ busca el comienzo de una linea
resultado = re.findall(r"^queso",texto) #normalmente se utiliza en conjunto a otros parametros de busqueda, como por ejemplo, verificar si "queso" es la primer palabra de la cadena de texto
#podemos buscar palabras al inicio de cada linea nueva con "flags=re.M" (<-- activa la multilinea). EJ: -->
resultado = re.findall(r"^nulla",texto,flags=re.M)


#$ busca el final de una linea
resultado = re.findall(r"agni\W$",texto)

#{n} --> busca n veces el valor de la izquierda
resultado = re.findall(r"\d{3}",texto) #en este caso estamos pidiendo que nos busque 3 numeros seguidos

#{n,m} --> busca n veces el valor de la izquierda y un m de veces puede mostrarse
resultado = re.findall(r"\d{3,4}",texto) #en este caso estamos pidiendo que nos busque numeros con 3 minimos caracteres y si tienen mas de 4, corta el numero (pero si los numeros sobrantes llegan a cumplir el primer parametro dado, seran mostrados tambien)

#tambien podemos buscar letras o palabras repetidas con esto
resultado = re.findall(r"do{3,4}",texto)#En este momento estamos buscando la palabra "do" con 3 "o" (do-o-o) con un maximo de 4 "o"
#si ponemos (do{2}), nos va a buscar "dodo" y nos va a devolver solo un "do", en este caso solo nos devolverá 2 "do"
resultado =re.findall(r"(do){2}",texto)
#en este caso (si usamos "[]" en vez de "()" )nos va a devolver cualquier combinacion entre los valores ingresados, en este caso pueden ser ("do", "oo", "od","dd")"[do]{2}". Si aumentamos el valor n, nos va a aumentar la longitud de la respuesta, pero las diferentes variables van a incrementar tambien
resultado =re.findall(r"[do]{2}",texto)

#or | nos permite buscar una cosa o caso de que no este, la otra

resultado = re.findall(r"\d{2}| dolo", texto) #en este caso nos devuelve ambas, ya que encontro ambas
print(resultado)