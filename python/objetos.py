import tkinter as tk
from time import strftime
from PIL import Image, ImageTk
def relojito():
    apa = strftime("%H:%M:%S")
    mostro.config(text=apa)
    backback.after(1000, relojito)
backback = tk.Tk()
backback.title("Relojito Bim Bim")
img = Image.open("C:\\Users\\Equipo\\OneDrive\\Escritorio\\pis.png")
img_tk = ImageTk.PhotoImage(img)
lab = tk.Label(backback, image=img_tk)
lab.pack()
mostro = tk.Label(backback, font=("Monospace",50), bg="black",fg="red")
mostro.pack(padx=0,pady=0)

relojito()
backback.mainloop()