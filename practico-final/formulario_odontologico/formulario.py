from tkinter import ttk, Tk

from consultorio import Consultorio
from formulario_odontologico._pestania_pacientes import PestaniaPacientes
from formulario_odontologico._pestania_turnos import PestaniaTurnos
from formulario_odontologico._pestania_historia import PestaniaHistoriaClinica


class FormularioOdontologico:
    def __init__(self, consultorio: Consultorio):
        self._consultorio = consultorio
        self._ventana = Tk()
        self._ventana.title("Saca Muela — Gestión Odontológica")
        self._ventana.geometry("900x600")
        self._ventana.minsize(800, 500)

        self._notebook = ttk.Notebook(self._ventana)
        self._notebook.pack(fill="both", expand=True, padx=5, pady=5)

        self._pestania_pacientes = PestaniaPacientes(self._notebook, self._consultorio)
        self._pestania_turnos = PestaniaTurnos(self._notebook, self._consultorio)
        self._pestania_historia = PestaniaHistoriaClinica(
            self._notebook, self._consultorio
        )

        self._notebook.add(self._pestania_pacientes, text="Pacientes")
        self._notebook.add(self._pestania_turnos, text="Turnos")
        self._notebook.add(self._pestania_historia, text="Historia Clínica")

        self._ventana.protocol("WM_DELETE_WINDOW", self._salir)

    def ejecutar(self):
        self._ventana.mainloop()

    def _salir(self):
        self._ventana.destroy()
