import pandas as pd

# Leer el archivo CSV
df = pd.read_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tareas_pendientes.csv")

afirmaciones = ["si", "s", "y", "yes"]

print("="*30)
print("Bienvenidos al gestor de tareas by Guma :)")
print("="*30)

while True:
    print("Que desea hacer?\n")
    print("---------------")
    print("Agregar una tarea- 1")
    print("Eliminar una tarea- 2")
    print("Marcar como completada una tarea- 3")
    print("Ver la lista de tareas- 4")
    print("Salir- 5")
    print("-----------")
    
    try:
        elegir_tarea = input("Elija una opción: ")
        if elegir_tarea not in ['1', '2', '3', '4', '5']:
            raise ValueError("Opción no válida")
    except ValueError as e:
        print(f"Error: {e}")
        continue
    
    if elegir_tarea == "5":
        print("Gracias por estar :)")
        break
    
    elif elegir_tarea == "4":
        print(df)
        seguir = input("¿Desea seguir? (si/no): ").lower()
        if seguir not in afirmaciones:
            print("Gracias por estar")
            break

    elif elegir_tarea == "1":
        while True:
            tarea_nueva = input("Nombre de la tarea: ").lower()
            if tarea_nueva == "5":
                break
            if tarea_nueva in df["tareas"].values:
                print("Esta tarea ya está registrada. Por favor, ingresa otro nombre.")
            else:
                nueva = pd.DataFrame({"tareas": [tarea_nueva], "hechas": "no"})
                df = pd.concat([df, nueva], ignore_index=True)
                df = df.sort_values("tareas", ascending=True)
                df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tareas_pendientes.csv", index=False)
                print("--------------")
                print(f"Tarea '{tarea_nueva}' agregada correctamente.")
                break

    elif elegir_tarea == "2":
        while True:
            print(df)
            try:
                tarea_eliminar = int(input("¿Qué tarea deseas eliminar? (ingresa el número de la tarea): "))
                if tarea_eliminar == "5":
                    break
                df = df.drop(tarea_eliminar)
                df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tareas_pendientes.csv", index=False)
                print("--------------")
                print("Tarea eliminada correctamente.")
                print(df)
                seguir = input("¿Deseas seguir eliminando tareas? (si/no): ").lower()
                if seguir not in afirmaciones:
                    break
            except ValueError:
                print("Por favor, ingresa un número válido.")
            except IndexError:
                print("Número de tarea fuera de rango, intenta de nuevo.")
        
    elif elegir_tarea == "3":
        while True:
            print(df)
            marcar_tarea = input("¿Qué tarea deseas marcar como hecha? (escribe el nombre de la tarea): ").lower()
            if marcar_tarea == "5":
                break
            if marcar_tarea in df["tareas"].values:
                df.loc[df["tareas"] == marcar_tarea, "hechas"] = "sí"
                df.to_csv("C:\\Users\\Equipo\\OneDrive\\Escritorio\\VSC\\python\\tareas_pendientes.csv", index=False)
                print("--------------")
                print(f"Tarea '{marcar_tarea}' marcada como completada.")
                print(df)
                seguir = input("¿Deseas seguir? (si/no): ").lower()
                if seguir not in afirmaciones:
                    break
            else:
                print("Tarea no encontrada, intenta de nuevo.")
