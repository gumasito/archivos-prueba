import tkinter as tk
from PIL import Image,ImageTk
def añadir(valor):
    display.config(text=display.cget("text") + str(valor))
def borrar():
    display.config(text="")
def calcular():
    try:
        resultado = eval(display.cget("text"))
        display.config(text=str(resultado))
    except Exception as e:
        error = tk.Tk()
        error.geometry("400x150")
        error.title("Error")
        try:
            img = Image.open("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\errorrr.png")
            img = img.resize((100,100))
            imgtk = ImageTk.PhotoImage(img)
            ventanita = tk.Label(error, image=imgtk)
            ventanita.pack()
            ventanita.imgtk = imgtk
            error.mainloop()
        except:
            msg = tk.Label(error,text=("Error :("),font=("Monospace",100),bg="#000",fg="#f00")
            msg.pack()
ventana = tk.Tk()
ventana.title("Prueba")

display = tk.Label(ventana,text=(),width=36,height=4,bg="#224",fg="#c1c1c1")
display.grid(columnspan=4,pady=10,padx=5)
#numero 0
boton0 = tk.Button(ventana, text=("0"),width=10, height=4,command=lambda:añadir(0), bg="#224",fg="#c1c1c1")
boton0.grid(row=1,column=0,pady=5,padx=5)
#numero 1
boton1= tk.Button(ventana,text=("1"),width=10,height=4,command=lambda :añadir(1),bg="#224",fg="#c1c1c1")
boton1.grid(row=1, column=1,pady=5,padx=5)
#numero 2
boton2= tk.Button(ventana,text=("2"),width=10,height=4,command=lambda :añadir(2),bg="#224",fg="#c1c1c1")
boton2.grid(row=1, column=2,pady=5,padx=5)
#numero 3
boton3= tk.Button(ventana,text=("3"),width=10,height=4,command=lambda :añadir(3),bg="#224",fg="#c1c1c1")
boton3.grid(row=2, column=0,pady=5,padx=5)
#numero 4
boton4= tk.Button(ventana,text=("4"),width=10,height=4,command=lambda :añadir(4),bg="#224",fg="#c1c1c1")
boton4.grid(row=2, column=1,pady=5,padx=5)
#numero 5
boton5= tk.Button(ventana,text=("5"),width=10,height=4,command=lambda :añadir(5),bg="#224",fg="#c1c1c1")
boton5.grid(row=2, column=2,pady=5,padx=5)
#numero 6
boton6= tk.Button(ventana,text=("6"),width=10,height=4,command=lambda :añadir(6),bg="#224",fg="#c1c1c1")
boton6.grid(row=3, column=0,pady=5,padx=5)
#numero 7
boton7= tk.Button(ventana,text=("7"),width=10,height=4,command=lambda :añadir(7),bg="#224",fg="#c1c1c1")
boton7.grid(row=3, column=1,pady=5,padx=5)
#numero 8
boton8= tk.Button(ventana,text=("8"),width=10,height=4,command=lambda :añadir(8),bg="#224",fg="#c1c1c1")
boton8.grid(row=3, column=2,pady=5,padx=5)
#numero 9
boton9= tk.Button(ventana,text=("9"),width=10,height=4,command=lambda :añadir(9),bg="#224",fg="#c1c1c1")
boton9.grid(row=4, column=0,pady=5,padx=5)
#suma
botonsuma= tk.Button(ventana,text=("+"),width=10,height=4,command=lambda :añadir("+"),bg="#224",fg="#c1c1c1")
botonsuma.grid(row=2, column=3,pady=5,padx=5)
#resta
botonresta= tk.Button(ventana,text=("-"),width=10,height=4,command=lambda :añadir("-"),bg="#224",fg="#c1c1c1")
botonresta.grid(row=3, column=3,pady=5,padx=5)
#multi
botonmulti= tk.Button(ventana,text=("x"),width=10,height=4,command=lambda :añadir("x"),bg="#224",fg="#c1c1c1")
botonmulti.grid(row=4, column=2,pady=5,padx=5)
#divi
botondivi= tk.Button(ventana,text=("/"),width=10,height=4,command=lambda :añadir("/"),bg="#224",fg="#c1c1c1")
botondivi.grid(row=4, column=3,pady=5,padx=5)
#borrar
botonborr = tk.Button(ventana,text="C",width=10,height=4,command=lambda:borrar(),bg="#224",fg="#c1c1c1")
botonborr.grid(row=1,column=3,pady=5,padx=5)
#igual
botonigual = tk.Button(ventana,text="=",width=10,height=4,command= lambda : calcular(),bg="#224",fg="#c1c1c1")
botonigual.grid(row=4,column=1,pady=5,padx=5)
#relleno
boton_relleno1= tk.Button(ventana,text=("☻"),width=10,height=4,bg="#224",fg="#c1c1c1")
boton_relleno1.grid(row=5, column=0,pady=5,padx=5)
#relleno 
boton_relleno2= tk.Button(ventana,text=("♥"),width=10,height=4,bg="#224",fg="#c1c1c1")
boton_relleno2.grid(row=5, column=1,pady=5,padx=5)
#relleno
boton_relleno3= tk.Button(ventana,text=("☺"),width=10,height=4,bg="#224",fg="#c1c1c1")
boton_relleno3.grid(row=5, column=2,pady=5,padx=5)
#Ejecutar
ventana.mainloop()
