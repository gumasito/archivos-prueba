a = [1, 2, 3]
b = [10, 20, 30]
#t Esto lo hice a mi manera y como lo interprete, pero lo que ChatGPT queria que hiciera era lo siguiente: #metodo 2
suma = [lambda i:a[i]+b[i] for i in range(len(a))]
#en lugar de usar lambda, podriamos haber hecho:
#suma = [a[i] + b[i] for i in range(len(a))]

resultado = [f(i) for i,f in enumerate(suma)]
#Metodo 2
suma = list(map(lambda x,y : x + y , a,b))
print(suma)