#primer ex
ingreso_mensual = 1001
if ingreso_mensual > 10000:
    print("estas bien economicamente")
elif ingreso_mensual > 1000:
    print("estas bien en latam")
else: print("tas pobre")


#if anidados- else if (elif)
salario_mensual = 1000
gastos_mensual = 1100

if salario_mensual >= 800:
    if salario_mensual - gastos_mensual < 0:
        print("estas en deficit")
    elif salario_mensual - gastos_mensual >= 800: 
        print("uff, que suerte")
    else: print("uf papi, cuidate")
elif salario_mensual >= 500:
    print("apa querido, ponele un poco mas de onda")
else: print("ufa, vas a tener q vivir con papis un rato mas de tiempo")