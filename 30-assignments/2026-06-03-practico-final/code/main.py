import sqlite3
import sys
from tkinter import messagebox

from consultorio import Consultorio
from formulario_odontologico import FormularioOdontologico


def main():
    ruta_db = sys.argv[1] if len(sys.argv) > 1 else "saca_muela.db"
    try:
        conn = sqlite3.connect(ruta_db)
        consultorio = Consultorio(conn)
        consultorio.inicializar()
    except sqlite3.Error as e:
        messagebox.showerror("Error de base de datos", str(e))
        sys.exit(1)

    app = FormularioOdontologico(consultorio)
    try:
        app.ejecutar()
    finally:
        conn.close()


if __name__ == "__main__":
    main()
