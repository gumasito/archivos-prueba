import csv
import os
import sqlite3
import sys


def directorio_base():
    """Carpeta donde está el .exe (o el .py), para guardar la base y el CSV junto a él."""
    if getattr(sys, "frozen", False):
        return os.path.dirname(sys.executable)
    return os.path.dirname(os.path.abspath(__file__))


BASE = directorio_base()
DB_PATH = os.path.join(BASE, "tienda.db")
CSV_PATH = os.path.join(BASE, "lista_productos.csv")
AFIRMATIVOS = ("s", "si", "sí", "y", "yes")


# ---------- Conexión y tabla ----------

def conectar():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn


def crear_tabla(conn):
    conn.execute("""
        CREATE TABLE IF NOT EXISTS productos (
            id       INTEGER PRIMARY KEY AUTOINCREMENT,
            producto TEXT NOT NULL UNIQUE COLLATE NOCASE,
            precio   REAL NOT NULL CHECK (precio >= 0),
            cantidad INTEGER NOT NULL CHECK (cantidad >= 0)
        )
    """)
    conn.commit()


# ---------- Validación de entradas ----------

def pedir_texto(mensaje):
    while True:
        texto = input(mensaje).strip()
        if texto:
            return texto
        print("Error: el campo no puede estar vacío.")


def pedir_entero(mensaje, minimo=0):
    while True:
        try:
            valor = int(input(mensaje).strip())
            if valor < minimo:
                raise ValueError
            return valor
        except ValueError:
            print(f"Error: ingrese un número entero mayor o igual a {minimo}.")


def pedir_precio(mensaje):
    while True:
        try:
            valor = float(input(mensaje).strip().replace(",", "."))
            if valor < 0:
                raise ValueError
            return round(valor, 2)
        except ValueError:
            print("Error: ingrese un precio válido (ej: 150.50).")


# ---------- Operaciones CRUD ----------

def alta(conn):
    """C - Create"""
    nombre = pedir_texto("Nombre del producto: ")
    precio = pedir_precio("Precio: $")
    cantidad = pedir_entero("Cantidad en stock: ")
    try:
        conn.execute(
            "INSERT INTO productos (producto, precio, cantidad) VALUES (?, ?, ?)",
            (nombre, precio, cantidad),
        )
        conn.commit()
        print("Producto agregado correctamente.")
    except sqlite3.IntegrityError:
        print("Error: ya existe un producto con ese nombre.")


def mostrar(filas):
    if not filas:
        print("No hay resultados.")
        return
    print(f"{'ID':<5}{'Producto':<25}{'Precio':>10}{'Cantidad':>10}")
    print("-" * 50)
    for f in filas:
        print(f"{f['id']:<5}{f['producto']:<25}{f['precio']:>10.2f}{f['cantidad']:>10}")


def consultar(conn):
    """R - Read (todos los registros)"""
    mostrar(conn.execute("SELECT * FROM productos ORDER BY producto").fetchall())


def buscar(conn):
    """R - Read (con filtro)"""
    texto = pedir_texto("Buscar por nombre (parte del texto): ")
    filas = conn.execute(
        "SELECT * FROM productos WHERE producto LIKE ? ORDER BY producto",
        (f"%{texto}%",),
    ).fetchall()
    mostrar(filas)


def modificar(conn):
    """U - Update"""
    try:
        id_ = pedir_entero("ID del producto a modificar: ", 1)
        fila = conn.execute("SELECT * FROM productos WHERE id = ?", (id_,)).fetchone()
        if fila is None:
            print("No existe un producto con ese ID.")
            return

        print("(Deje vacío para mantener el valor actual)")
        nombre = input(f"Nombre [{fila['producto']}]: ").strip() or fila["producto"]
        precio_txt = input(f"Precio [{fila['precio']}]: ").strip()
        cant_txt = input(f"Cantidad [{fila['cantidad']}]: ").strip()

        precio = float(precio_txt.replace(",", ".")) if precio_txt else fila["precio"]
        cantidad = int(cant_txt) if cant_txt else fila["cantidad"]

        if precio < 0 or cantidad < 0:
            print("Error: precio y cantidad no pueden ser negativos.")
            return

        conn.execute(
            "UPDATE productos SET producto = ?, precio = ?, cantidad = ? WHERE id = ?",
            (nombre, round(precio, 2), cantidad, id_),
        )
        conn.commit()
        print("Producto modificado correctamente.")
    except ValueError:
        print("Error: ingrese valores numéricos válidos.")
    except sqlite3.IntegrityError:
        print("Error: ya existe otro producto con ese nombre.")


def baja(conn):
    """D - Delete"""
    try:
        id_ = pedir_entero("ID del producto a eliminar: ", 1)
        fila = conn.execute("SELECT producto FROM productos WHERE id = ?", (id_,)).fetchone()
        if fila is None:
            print("No existe un producto con ese ID.")
            return
        confirma = input(f"¿Confirma eliminar '{fila['producto']}'? (s/n): ").strip().lower()
        if confirma in AFIRMATIVOS:
            conn.execute("DELETE FROM productos WHERE id = ?", (id_,))
            conn.commit()
            print("Producto eliminado.")
        else:
            print("Operación cancelada.")
    except ValueError:
        print("Error: ID inválido.")


# ---------- CSV ----------

def importar_csv(conn, ruta=CSV_PATH):
    """Carga el CSV (columnas: productos, precio $, cantidad) en la base."""
    insertados = omitidos = 0
    try:
        with open(ruta, newline="", encoding="utf-8-sig") as f:
            for fila in csv.DictReader(f):
                try:
                    conn.execute(
                        "INSERT INTO productos (producto, precio, cantidad) VALUES (?, ?, ?)",
                        (
                            fila["productos"].strip(),
                            float(fila["precio $"]),
                            int(fila["cantidad"]),
                        ),
                    )
                    insertados += 1
                except (KeyError, ValueError, AttributeError, sqlite3.IntegrityError):
                    omitidos += 1
        conn.commit()
        print(f"Importación terminada: {insertados} insertados, {omitidos} omitidos.")
    except FileNotFoundError:
        print(f"Error: no se encontró el archivo {ruta}")
    except OSError as e:
        print(f"Error al leer el archivo: {e}")


def exportar_csv(conn, ruta=CSV_PATH):
    try:
        filas = conn.execute(
            "SELECT producto, precio, cantidad FROM productos ORDER BY producto"
        ).fetchall()
        with open(ruta, "w", newline="", encoding="utf-8") as f:
            escritor = csv.writer(f)
            escritor.writerow(["productos", "precio $", "cantidad"])
            escritor.writerows(tuple(r) for r in filas)
        print(f"Exportado a {ruta}")
    except OSError as e:
        print(f"Error al escribir el archivo: {e}")


# ---------- Modo SQL ----------

def modo_sql(conn):
    print("Modo SQL. Ejemplo: SELECT * FROM productos WHERE cantidad < 5;")
    print("Escriba 'salir' para volver al menú.")
    while True:
        sentencia = input("SQL> ").strip()
        if sentencia.lower() in ("salir", "exit"):
            break
        if not sentencia:
            continue
        try:
            cur = conn.execute(sentencia)
            if cur.description:  # SELECT: mostrar resultados
                columnas = [d[0] for d in cur.description]
                filas = cur.fetchall()
                print(" | ".join(columnas))
                print("-" * 40)
                for f in filas:
                    print(" | ".join(str(v) for v in f))
                print(f"({len(filas)} filas)")
            else:  # INSERT / UPDATE / DELETE / CREATE...
                conn.commit()
                print(f"Ejecutado. Filas afectadas: {cur.rowcount}")
        except sqlite3.Error as e:
            print(f"Error SQL: {e}")


# ---------- Menú principal ----------

MENU = """
========== TIENDA POKÉMON ==========
1. Alta (agregar producto)
2. Consultar todos
3. Buscar por nombre
4. Modificar producto
5. Baja (eliminar producto)
6. Modo SQL
7. Importar CSV
8. Exportar CSV
0. Salir
====================================
"""


def main():
    try:
        conn = conectar()
    except sqlite3.Error as e:
        print(f"No se pudo abrir la base de datos: {e}")
        input("Presione Enter para salir...")
        return

    crear_tabla(conn)

    total = conn.execute("SELECT COUNT(*) FROM productos").fetchone()[0]
    if total == 0 and os.path.exists(CSV_PATH):
        print("Base vacía: importando lista_productos.csv...")
        importar_csv(conn)

    print("Hola! Bienvenido a la tienda pokemon -- by Guma :)")

    acciones = {
        "1": alta,
        "2": consultar,
        "3": buscar,
        "4": modificar,
        "5": baja,
        "6": modo_sql,
        "7": importar_csv,
        "8": exportar_csv,
    }

    while True:
        try:
            print(MENU)
            opcion = input("Elija una opción: ").strip()
            if opcion == "0":
                print("Vuelva cuando quiera. Nos vemos :)")
                break
            accion = acciones.get(opcion)
            if accion is None:
                print("Opción inválida, intente de nuevo.")
                continue
            accion(conn)
        except sqlite3.Error as e:
            print(f"Error de base de datos: {e}")
        except (KeyboardInterrupt, EOFError):
            print("\nPrograma interrumpido.")
            break

    conn.close()


if __name__ == "__main__":
    main()
