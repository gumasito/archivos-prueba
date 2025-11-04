import tkinter as tk

def aumentar():
    global contador_local
    contador_local +=1
    etiqueta_local.config(text=f"Contador Local:{contador_local}")

def disminuir():
    global contador_local
    contador_local -=1
    etiqueta_local.config(text=f"Contador Local: {contador_local}")
def aumentar2():
    global contador_visi
    contador_visi +=1
    etiqueta_visi.config(text=f"Contador Visitante:{contador_visi}")

def disminuir2():
    global contador_visi
    contador_visi -=1
    etiqueta_visi.config(text=f"Contador Visitante: {contador_visi}")

ventana = tk.Tk()
ventana.title("Contador con botones")
ventana.geometry("500x400")
contador_local = 0
contador_visi = 0


#etiqueta local
etiqueta_local = tk.Label(ventana, text=f"Contador Local: {contador_local}", font= ("Arial", 16))
etiqueta_local.grid(row=0,column=0)
#etiqueta visitante
etiqueta_visi = tk.Label(ventana, text=f"Contador Visitante: {contador_visi}", font= ("Arial", 16))
etiqueta_visi.grid(row=0,column=1)

#t BOTONES PARA LOCAL
boton_suma = tk.Button(ventana, text="Sumar", command=aumentar, font=("Arial", 14))
boton_suma.grid(row=1,column=0,pady=10)


boton_resta = tk.Button(ventana, text="Resta", command=disminuir, font=("Arial", 14))
boton_resta.grid(row=2,column=0,pady=10)

#t BOTONES PARA VISITANTE

boton_suma_visi = tk.Button(ventana, text="Sumar", command=aumentar2, font=("Arial", 14))
boton_suma_visi.grid(row=1,column=1,pady=10)


boton_resta_visi = tk.Button(ventana, text="Resta", command=disminuir2, font=("Arial", 14))
boton_resta_visi.grid(row=2,column=1, pady=10)

ventana.mainloop()

#!Lo que pasa si es que modificas el boton o etiqueta directamente con ".grid" es que se retorna un valor "none", por ende, no se podran efectuar cambios en el contador