#datos
#duracion de los cursos
otros_cursos_min = 2.5 
otros_cursos_max = 7
otros_cursos_average = 4
dalto_curso= 1.5

#duracion de crudos
crudo_average = 5
crudo_dalto = 3.5

#diferencia de duracion
print(100 - 1.5 /2.5*100)
diferencia_con_min = 100 - dalto_curso / otros_cursos_min * 100
diferencia_con_ave = 100 - dalto_curso / otros_cursos_average * 100
diferencia_con_max = 100 - dalto_curso * 100 // otros_cursos_max#usamos esto para evitar problemas de redondeo con "//" y poner un decimal

#calculando el tiempo vacio removido 
print( 100 - 4 *1000 / 5 / 10)
tiempo_vacio_promedio = 100 - otros_cursos_average *100 // crudo_average 
tiempo_vacio_dalto = 100 - dalto_curso *100 // crudo_dalto 


#mostrando la diferencia de duracion (ejercicio A)
print("----------------------------------------")
print("El curso de dalto dura:")
print(f" - un {diferencia_con_min}% menos que el mas rapido")
print(f" - un {diferencia_con_ave}% menos que el promedio")
print(f" - un {diferencia_con_max}% menos que el mas lento")
print("----------------------------------------")

#mostrando la diferencia de duracion (ejercicio B)
print("El promedio de tiempo reducido de")
print(f" - otros cursos es de: {tiempo_vacio_promedio}%")
print(f" - este curso es de: {tiempo_vacio_dalto}%")
print("----------------------------------------")

#mostrando diferencias si los cursos duraran 10 horas
print("La equivalencia de")
print(f" - ver 10 horas de este curso equivale a ver: {otros_cursos_average * 100 // dalto_curso / 10} horas de otros cursos")
print(f" - ver 10 horas de otros cursos equivale a ver: {dalto_curso * 100 // otros_cursos_average / 10} horas de este curso")
print("----------------------------------------")

#corregidos un poco intentando usar round()