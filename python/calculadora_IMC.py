print("\nBienvenidos a la calculadora de IMC")
peso = float(input("Ingrese su peso--> "))
altura = float(input("Ingrese su altura--> "))

imc = peso / (altura ** 2)
print(f"Tu IMC es {imc:.2f}") #! {:.f} significa que se acortara la expresion a 2 decimales, y "f" significa que es un numero flotante

if imc < 18.5:
    print("Estas bajo en peso")
elif 18.5 <= imc <= 29.9:
    print("Tienes un peso saludable")
elif 25 <= imc < 29.9:
    print("Tienes sobrepeso :)")
else: print("Tas bien fofo")