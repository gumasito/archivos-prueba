
#creando un conjunto con set()
conjunto = set(["dato1", "dato2"])

#creando un conjunto dentro de otro conjunto
conjunto1 = frozenset(["dato3","dato4"])
conjunto2 = {conjunto1, "dato5"}

#teoria de conjuntos
conjunto1 = {1,3,5,7}
conjunto2 = {1,3,5}

#verificando si es un subconjunto (estas formas de verificar devuelven resultados booleanos)
resultado = conjunto2.issubset(conjunto1)
#verificando si es un superconjunto
resultado = conjunto1.issuperset(conjunto2)

#otro forma de hacerlo 
resultado = conjunto2 <= conjunto1
resultado = conjunto1 >= conjunto2

#verificar si hay algun numero en comun
resultado = conjunto2.isdisjoint(conjunto1) #si devuelve "False" es porque hay coincidencias entre los numeros de ambas listas. Caso contrario, devuelve "True"
print(resultado)