import tkinter as tk
import serial

puerto = serial.Serial('COM5',9600)
ventana = tk.Tk()
ventana.title("Puertito")

def Prender():
    puerto.write(b'1')

def Apagar():
    puerto.write(b'0')

on_but = tk.Button(ventana,text = "Encender", command=Prender, bg="green",fg="black")
on_but.pack()

off_but =tk.Button(ventana,text= "Apagar",command=Apagar,bg ="red",fg="black")
off_but.pack()

ventana.mainloop()