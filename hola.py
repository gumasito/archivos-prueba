from datetime import date
import locale
locale.setlocale(locale.LC_TIME, 'es_AR.UTF-8')
nombre = input("Ingrese tu nombre ")
dia = date.today().strftime("%A")
saludo = print(f"Hola {nombre}, como te va en el dia {dia}")   