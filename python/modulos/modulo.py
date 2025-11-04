#Explicacion de lo que es un modulo: Un modulo es un archivo, en este caso, son todos aquellos que terminan/tienen la extension .py
#A los modulos se los pueden llamar, a traves del "import + archivo_modulo"
#Estas funciones que tengamos en los modulos se transformaran en "Metodos"
import modulo_saludar as modulito

#PODEMOS USAR EL "AS", para "renombrar" el modulo y utilizarlo de una forma mas rapida en nuestro codigo
#Podemos llamar a una sola funcion de otro modulo a traves de "from #archivo.py import #funcion"
#funcion es def saludo()
saludo = modulito.saludo("jere")
print(saludo)

#accedemos al nombre de este modulo
print(__name__)

#accedemos al nombre del modulo llamado
print(modulito.__name__)

#paths de las carpetas y/o archivos:
#from #carpeta.#subcarpeta/archivo.py

#cuando el modulo esta en una carpeta externa de las nuestra, lo que debemos hacer es llamar a la funcion "sys" (cuya funcion es built-in) y colocar .path 
#con esto podremos saber la ruta de los modulos de python. Lo que debremos de hacer seria copiar la ruta de la carpeta y luego importar el archivo
import sys
sys.path.append("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\Ejercicios")
print(sys.path)