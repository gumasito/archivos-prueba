list_num= [4.14,124,14,50,0,19]

#encontrando el numero mayor de una lista
find_max = max(list_num)
print(find_max)

#encontrando el numero menor de una lista
find_min = min(list_num)
print(find_min)

#redondeando a 6 caracteres
num = round(12.241941741441556, 6) #round() nos permite redondear los numeros, y la coma se coloca para establecer los espacios detras de la misma que querramos que tenga
print(num)

#retorna False --> 0, False, Vacio, ninguno / True --> cualquier numero != 0, cadena o True
resultado_bool = bool("") #puede ser bool([]) bool(0) bool() bool(False) bool("")
print(resultado_bool)

#retorna True, si todos los valores son verdaderos (caso de que coloquemos valores "0" (como el ejemplo de arriba) retorna False)
resultado_all = all(["ahawqqw", 1241, ["hola", "como", "estas"]])
print(resultado_all)

#suma todos los valores de un iterable
suma_total = sum(list_num)
print(suma_total)