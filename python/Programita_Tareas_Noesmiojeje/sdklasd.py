import csv

# Archivo para guardar las tareas
FILE_NAME = "tasks.csv"

# Cargar tareas desde el archivo CSV
def load_tasks():
    tasks = []
    try:
        with open(FILE_NAME, mode='r', newline='') as file:
            reader = csv.reader(file)
            tasks = [row for row in reader]
    except FileNotFoundError:
        pass  # No hacer nada si el archivo no existe
    return tasks

# Guardar tareas en el archivo CSV
def save_tasks(tasks):
    with open(FILE_NAME, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(tasks)

# Mostrar las tareas
def display_tasks(tasks):
    if not tasks:
        print("\nNo hay tareas.")
    else:
        print("\nLista de Tareas:")
        for index, (task, status) in enumerate(tasks):
            status_text = "[Completada]" if status == "1" else "[Pendiente]"
            print(f"{index + 1}. {task} {status_text}")

# Agregar una nueva tarea
def add_task(tasks):
    task_name = input("\nIngrese el nombre de la tarea: ").strip()
    if task_name:
        tasks.append([task_name, "0"])  # "0" significa pendiente
        print("Tarea agregada.")
    else:
        print("No se puede agregar una tarea vacía.")

# Marcar una tarea como completada
def complete_task(tasks):
    display_tasks(tasks)
    try:
        task_num = int(input("\nIngrese el número de la tarea a completar: ")) - 1
        if 0 <= task_num < len(tasks):
            tasks[task_num][1] = "1"  # "1" significa completada
            print("Tarea marcada como completada.")
        else:
            print("Número de tarea inválido.")
    except ValueError:
        print("Entrada no válida.")

# Eliminar tareas completadas
def delete_completed_tasks(tasks):
    initial_count = len(tasks)
    tasks[:] = [task for task in tasks if task[1] == "0"]
    if len(tasks) < initial_count:
        print("Tareas completadas eliminadas.")
    else:
        print("No hay tareas completadas para eliminar.")

# Menú principal
def main():
    tasks = load_tasks()

    while True:
        print("\nGestor de Tareas")
        print("1. Mostrar tareas")
        print("2. Agregar tarea")
        print("3. Completar tarea")
        print("4. Eliminar tareas completadas")
        print("5. Salir")

        choice = input("\nSeleccione una opción: ")

        if choice == "1":
            display_tasks(tasks)
        elif choice == "2":
            add_task(tasks)
            save_tasks(tasks)
        elif choice == "3":
            complete_task(tasks)
            save_tasks(tasks)
        elif choice == "4":
            delete_completed_tasks(tasks)
            save_tasks(tasks)
        elif choice == "5":
            save_tasks(tasks)
            print("Saliendo del programa. Hasta luego!")
            break
        else:
            print("Opción no válida. Intente nuevamente.")

if __name__ == "__main__":
    main()
