#2 listas con nombres y apellidos
nombre = ["Jere", "Lau", "Emi", "Copito","Gato"]
apellidos = ["More", "Sob","More","Fofo","Amargado"]

#Registrar esta informacion en un TXT de forma optima

with open("python\\archivos_problemas_resueltos\\problema1_txt.txt","w",encoding="UTF-8") as archivo:

    archivo.writelines("Los datos son \n\n")

    #forma reducida
    [archivo.writelines(f"El nombre es: {n} y el apellido es: {a}\n-------------------\n") for n,a in zip(nombre,apellidos)]
    #forma normal
    #for n,a in zip(nombre,apellidos):
    #    archivo.writelines(f"El nombre es: {n} y el apellido es: {a} \n")