#DATA: no es necesario separar con comas para hacer un espacio en linea, ya que el formato ".CSV" interpreta el espacio en linea como "separador".
import csv
#csv es un modulo que nos permite la comprension de los archivos ".CSV"

with open("r_CSV.csv") as archivo: 
    #ejemplo de como se lee un apython\\archivos\\leerchivo ".CSV" correctamente
    reader = csv.reader(archivo)
    print(reader)
    for row in reader:
        print(row)