#libreria tkinter: para hacer interfaces graficas
import tkinter as tk
#*funcion al hacer click
def click():
    etiqueta.config(text="Me hiciste click :O") #config(text="nuevo texto") cambia el texto de la etiqueta.
def default():
    etiqueta.config(text="Este es un boton de nuevo :)")

def mostrar_texto():
    texto = entrada.get()
    etiqueta.config(text=f"Escribiste: {texto}", font=("Monospace", 16))
#tk.Tk(): para hacer la ventana
ventana = tk.Tk()
#.title: indica el titulo de la ventana
ventana.title("Mi primera ventana")
#.geometry: el tamaño de la ventana
ventana.geometry("300x400")
#ejecuta la ventana
#! ventana.mainloop()


#? AGREGANDO BOTONES Y ETIQUETAS
etiqueta = tk.Label(ventana, text="Hola tkinter", font=("Arial",16)) #.Label: crea una etiqueta de texto
etiqueta.pack(pady=20) #.pack: coloca los elementos en la ventana

#botón+
boton = tk.Button(ventana, text="Este es un boton", font=("Arial", 14), command=default) #.Button: crea un boton
boton.pack()

#? EVENTOS AL HACER CLICK
boton_click = tk.Button(ventana, text="Si me haces click... cuidado", command=click, font=("Monospace", 14)) #command=click hace que el botón ejecute la función click() al hacer clic
boton_click.pack()
#?AGREGANDO UN CUADRO DE TEXTO
entrada = tk.Entry(ventana, font=("Arial",14)) #Entry() crea un cuadro donde el usuario puede escribir.
#Con entry() ingresamos texto, y con la funcion "mostrar_texto()" vamos a cambiar el nombre del titulo del cuadro, y con el button "boton_mostrar" lo que hacemos es cambiar el titulo con la funcion nombrada anteriormente
entrada.pack(pady=10)
boton_mostrar = tk.Button(ventana, text="Mostrar texto", command=mostrar_texto, font=("Monospace", 14))
boton_mostrar.pack()





ventana.mainloop()