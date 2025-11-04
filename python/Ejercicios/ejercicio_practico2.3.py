#creando una funcion que muestre la serie fibonacci entre el 0 y el numero dado
def fibonacci(num):
    a,b= 0,1
    fibonacci_list = []
    for i in range(num +1):
        if b > num:
            return fibonacci_list
        else:
            fibonacci_list.append(b)
            a,b = b, a+b
res = fibonacci(1000)
print(res)
#entendi esta :DDDDDDDDD