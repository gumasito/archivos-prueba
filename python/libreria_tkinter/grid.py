import tkinter as tk
ventana = tk.Tk()
ventana.geometry("300x400")
ventana.title("Grid")

#?grid

tk.Label(ventana,text="Fila 0, Columna 0").grid(row=0, column= 0)
tk.Label(ventana,text="Fila 1, Columna 0").grid(row=1, column= 0)
tk.Label(ventana,text="Fila 0, Columna 1").grid(row=0, column= 1)
tk.Label(ventana,text="Fila 1, Columna 1").grid(row=1, column= 1)
ventana.mainloop()