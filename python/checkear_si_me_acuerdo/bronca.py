import tkinter as tk

ventana = tk.Tk()
ventana.geometry("300x200")
ventana.title("Contador")

texto1 = tk.Label(ventana,text="Hola",font=("Monospace",16),bg="#000",fg="#bbf")
texto1.grid(row=0,column=0,pady=10)
texto2 = tk.Label(ventana,text="Hola",font=("Monospace",16),bg="#000",fg="#bbf")
texto2.grid(row=0,column=1,pady=10)
texto3 = tk.Label(ventana,text="Hola",font=("Monospace",16),bg="#000",fg="#bbf")
texto3.grid(row=0,column=2,pady=10)
boton1 = tk.Button(ventana,text="Botonsito",font=("Monospace",20))
boton1.grid(columnspan=3,rowspan=1)

ventana.mainloop()