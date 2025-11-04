import tkinter as tk
from time import strftime

def reloj():
    tiempo = strftime("%H:%M:%S")
    display.config(text=tiempo)
    display.after(1000,reloj)
    
ventana = tk.Tk()
ventana.title("SISIS")

display = tk.Label(ventana,font=("Monospace",50))
display.pack()
reloj()
ventana.mainloop()