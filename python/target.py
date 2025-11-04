array = [0,1,2,4,6,10,5,15,141,6,9,26,94,599,1000]
target = 6
result = []
def suma():
    for i in range(len(array)):
        for j in range(i+1, len(array)):
            print(i,j) #T esto muestra las sumas que hace al iterar el array desde cada indice para sumar de uno a uno y si no encuentra resultado, sigue por el otro valor
            #! Si queremos optimizar la secuencia, podemos agregar un [0,1] al array, para aumentar la probabilidad de match
            if array[i] + array[j] == target:
                return [array[i],array[j]]
print(suma())