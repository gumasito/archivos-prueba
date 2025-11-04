def alumno_notas(n):
    nota_general = 0
    alumno = {}
    for i in range(n):
        nota = int(input(f"Ingrese la nota del alumno {i+1}>> "))
        nota_general += nota
        if nota >=6:
            alumno[f"Alumno {i+1}"] = nota
    nota_promedio = nota_general/n
    return nota_promedio, alumno
cantidad = int(input("Ingrese la cantidad de alumnos>> "))
prom,dicc = alumno_notas(cantidad)
print(f"La nota promedio del curso es de {prom:.2f}")
print(f"La cantidad de alumnos que aprobaron son {len(dicc)}")
for nombre,nota in dicc.items():
    print(f"El {nombre}- obtuvo {nota}")