import tkinter as tk
#t parche de un temporizador que solo se ejecuta cuando no haya otro
cronometro_ejecucion = False
def iniciar():
    #t llamamos a la variable y siempre debe estar en False al principio para poder ejecutarse, caso de que no este, no se convertiría "false --> true" por ende, no se ejecutaria
    global cronometro_ejecucion
    if not cronometro_ejecucion:
        try:
            tiempo = int(entrada_tiempo.get())
            if tiempo > 0:
                cronometro_ejecucion = True #t establecemos True
                cuenta_regresiva(tiempo)
            else: etiqueta.config(text="Ingrese un valor positivo")
        except ValueError:
            etiqueta.config(text="Ingrese un número válido")
def cuenta_regresiva(tiempo):
    global cronometro_ejecucion
    if tiempo > 0:
        etiqueta.config(text=f"Quedan {tiempo} segundos")
        ventana.after(1000,cuenta_regresiva,tiempo -1)
    else: 
        etiqueta.config(text="Time's Over :)")
        cronometro_ejecucion = False #t Establecemos "False" para luego en el inicio se vuelva a convertir a "True"

ventana = tk.Tk()
ventana.geometry("300x200")
ventana.title("Cronometro")

etiqueta = tk.Label(ventana,text="Cronometro con tkinter", font=("Monospace",16))
etiqueta.pack(pady=15)

etiqueta_cronometro = tk.Label(ventana, text="Ingrese el tiempo", font=("Monospace", 16))
etiqueta_cronometro.pack(pady=8)

entrada_tiempo = tk.Entry(ventana,font=("Monospace",14))
entrada_tiempo.pack()

boton = tk.Button(ventana, text="Iniciar cronometro", command=iniciar, font=("Monospace", 16))
boton.pack()
ventana.mainloop()