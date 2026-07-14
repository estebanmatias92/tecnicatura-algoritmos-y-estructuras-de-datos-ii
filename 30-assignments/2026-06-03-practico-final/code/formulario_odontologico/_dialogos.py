import tkinter as tk
from tkinter import ttk, messagebox

from consultorio import Paciente


class DialogoPaciente(tk.Toplevel):
    def __init__(self, parent, titulo: str, paciente: Paciente | None = None):
        super().__init__(parent)
        self.title(titulo)
        self.resizable(False, False)
        self.transient(parent)
        self.grab_set()

        self.resultado: dict | None = None
        self._paciente = paciente
        self._construir_formulario()
        self._cargar_datos()
        self.wait_window()

    def _construir_formulario(self):
        pad = {"padx": 10, "pady": 4}
        self._campos = {}

        fila = 0
        for label, clave in [
            ("DNI", "dni"),
            ("Nombre", "nombre"),
            ("Apellido", "apellido"),
            ("Teléfono", "telefono"),
            ("Email", "email"),
            ("Dirección", "direccion"),
            ("Obra Social", "obra_social"),
        ]:
            ttk.Label(self, text=label).grid(row=fila, column=0, sticky="e", **pad)
            entry = ttk.Entry(self, width=35)
            entry.grid(row=fila, column=1, **pad)
            self._campos[clave] = entry
            fila += 1

        if self._paciente:
            self._campos["dni"].config(state="readonly")

        fila += 1
        frame_botones = ttk.Frame(self)
        frame_botones.grid(row=fila, column=0, columnspan=2, pady=10)
        ttk.Button(frame_botones, text="Guardar", command=self._guardar).pack(
            side="left", padx=5
        )
        ttk.Button(frame_botones, text="Cancelar", command=self.destroy).pack(
            side="left", padx=5
        )

        self.bind("<Return>", lambda e: self._guardar())
        self.bind("<Escape>", lambda e: self.destroy())

    def _cargar_datos(self):
        if self._paciente:
            for clave, entry in self._campos.items():
                entry.delete(0, tk.END)
                entry.insert(0, getattr(self._paciente, clave, ""))

    def _guardar(self):
        datos = {clave: entry.get().strip() for clave, entry in self._campos.items()}
        if not datos["dni"] or not datos["nombre"] or not datos["apellido"]:
            messagebox.showwarning(
                "Campos incompletos",
                "DNI, Nombre y Apellido son obligatorios.",
                parent=self,
            )
            return
        self.resultado = datos
        self.destroy()


class DialogoSeleccionPaciente(tk.Toplevel):
    def __init__(self, parent, pacientes: list[Paciente]):
        super().__init__(parent)
        self.title("Seleccionar Paciente")
        self.resizable(False, False)
        self.transient(parent)
        self.grab_set()
        self.resultado: Paciente | None = None
        self._pacientes = pacientes

        ttk.Label(self, text="Paciente:").grid(
            row=0, column=0, padx=10, pady=(10, 0), sticky="e"
        )
        self._combo = ttk.Combobox(
            self,
            values=[
                f"{p.id}: {p.nombre} {p.apellido} (DNI: {p.dni})" for p in pacientes
            ],
            state="readonly",
            width=45,
        )
        self._combo.grid(row=0, column=1, padx=10, pady=(10, 0))
        if pacientes:
            self._combo.current(0)
        ttk.Button(self, text="Seleccionar", command=self._seleccionar).grid(
            row=1, column=0, columnspan=2, pady=10
        )
        self.bind("<Return>", lambda e: self._seleccionar())
        self.bind("<Escape>", lambda e: self.destroy())

    def _seleccionar(self):
        if not self._combo.get():
            return
        pid = int(self._combo.get().split(":")[0])
        self.resultado = next(p for p in self._pacientes if p.id == pid)
        self.destroy()


class DialogoSeleccionOdontologo(tk.Toplevel):
    def __init__(self, parent, odontologos):
        super().__init__(parent)
        self.title("Seleccionar Odontólogo")
        self.resizable(False, False)
        self.transient(parent)
        self.grab_set()
        self.resultado: int | None = None

        ttk.Label(self, text="Odontólogo actuante:").grid(
            row=0, column=0, padx=10, pady=(10, 0), sticky="e"
        )
        self._combo = ttk.Combobox(
            self,
            values=[
                f"{o.id}: {o.nombre} {o.apellido} ({o.especialidad})"
                for o in odontologos
            ],
            state="readonly",
            width=45,
        )
        self._combo.grid(row=0, column=1, padx=10, pady=(10, 0))
        if odontologos:
            self._combo.current(0)
        ttk.Button(self, text="Aceptar", command=self._aceptar).grid(
            row=1, column=0, columnspan=2, pady=10
        )
        self.bind("<Return>", lambda e: self._aceptar())
        self.bind("<Escape>", lambda e: self.destroy())

    def _aceptar(self):
        if not self._combo.get():
            return
        self.resultado = int(self._combo.get().split(":")[0])
        self.destroy()


class DialogoTurno(tk.Toplevel):
    def __init__(self, parent, paciente: Paciente, odontologos):
        super().__init__(parent)
        self.title("Asignar Turno")
        self.resizable(False, False)
        self.transient(parent)
        self.grab_set()

        self.resultado: dict | None = None
        self._paciente = paciente
        self._odontologos = odontologos
        self._construir_formulario()
        self.wait_window()

    def _construir_formulario(self):
        pad = {"padx": 10, "pady": 4}

        ttk.Label(self, text="Paciente").grid(row=0, column=0, sticky="e", **pad)
        ttk.Label(self, text=f"{self._paciente.nombre} {self._paciente.apellido}").grid(
            row=0, column=1, sticky="w", **pad
        )

        ttk.Label(self, text="Odontólogo").grid(row=1, column=0, sticky="e", **pad)
        self._combo_odontologo = ttk.Combobox(
            self,
            values=[
                f"{o.id}: {o.nombre} {o.apellido} ({o.especialidad})"
                for o in self._odontologos
            ],
            state="readonly",
            width=40,
        )
        self._combo_odontologo.grid(row=1, column=1, **pad)
        if self._odontologos:
            self._combo_odontologo.current(0)

        ttk.Label(self, text="Fecha (YYYY-MM-DD)").grid(
            row=2, column=0, sticky="e", **pad
        )
        self._entry_fecha = ttk.Entry(self, width=20)
        self._entry_fecha.grid(row=2, column=1, sticky="w", **pad)

        ttk.Label(self, text="Hora (HH:MM)").grid(row=3, column=0, sticky="e", **pad)
        self._entry_hora = ttk.Entry(self, width=20)
        self._entry_hora.grid(row=3, column=1, sticky="w", **pad)

        ttk.Label(self, text="Motivo").grid(row=4, column=0, sticky="e", **pad)
        self._entry_motivo = ttk.Entry(self, width=35)
        self._entry_motivo.grid(row=4, column=1, **pad)

        ttk.Button(self, text="Asignar", command=self._guardar).grid(
            row=5, column=0, columnspan=2, pady=10
        )
        self.bind("<Return>", lambda e: self._guardar())
        self.bind("<Escape>", lambda e: self.destroy())

    def _guardar(self):
        if not self._combo_odontologo.get():
            messagebox.showwarning(
                "Odontólogo requerido", "Seleccione un odontólogo.", parent=self
            )
            return
        odontologo_id = int(self._combo_odontologo.get().split(":")[0])
        fecha = self._entry_fecha.get().strip()
        hora = self._entry_hora.get().strip()
        if not fecha or not hora:
            messagebox.showwarning(
                "Campos incompletos", "Fecha y hora son obligatorios.", parent=self
            )
            return
        self.resultado = {
            "paciente_id": self._paciente.id,
            "odontologo_id": odontologo_id,
            "fecha": fecha,
            "hora": hora,
            "motivo": self._entry_motivo.get().strip(),
        }
        self.destroy()


class DialogoAsignarTurno(tk.Toplevel):
    def __init__(self, parent, pacientes, odontologos):
        super().__init__(parent)
        self.title("Asignar Turno")
        self.resizable(False, False)
        self.transient(parent)
        self.grab_set()

        self.resultado: dict | None = None
        self._pacientes = pacientes
        self._odontologos = odontologos
        self._construir_formulario()
        self.wait_window()

    def _construir_formulario(self):
        pad = {"padx": 10, "pady": 4}

        ttk.Label(self, text="Paciente").grid(row=0, column=0, sticky="e", **pad)
        self._combo_paciente = ttk.Combobox(
            self,
            values=[
                f"{p.id}: {p.nombre} {p.apellido} (DNI: {p.dni})"
                for p in self._pacientes
            ],
            state="readonly",
            width=45,
        )
        self._combo_paciente.grid(row=0, column=1, **pad)
        if self._pacientes:
            self._combo_paciente.current(0)

        ttk.Label(self, text="Odontólogo").grid(row=1, column=0, sticky="e", **pad)
        self._combo_odontologo = ttk.Combobox(
            self,
            values=[
                f"{o.id}: {o.nombre} {o.apellido} ({o.especialidad})"
                for o in self._odontologos
            ],
            state="readonly",
            width=45,
        )
        self._combo_odontologo.grid(row=1, column=1, **pad)
        if self._odontologos:
            self._combo_odontologo.current(0)

        ttk.Label(self, text="Fecha (YYYY-MM-DD)").grid(
            row=2, column=0, sticky="e", **pad
        )
        self._entry_fecha = ttk.Entry(self, width=25)
        self._entry_fecha.grid(row=2, column=1, sticky="w", **pad)

        ttk.Label(self, text="Hora (HH:MM)").grid(row=3, column=0, sticky="e", **pad)
        self._entry_hora = ttk.Entry(self, width=25)
        self._entry_hora.grid(row=3, column=1, sticky="w", **pad)

        ttk.Label(self, text="Motivo").grid(row=4, column=0, sticky="e", **pad)
        self._entry_motivo = ttk.Entry(self, width=45)
        self._entry_motivo.grid(row=4, column=1, **pad)

        frame_botones = ttk.Frame(self)
        frame_botones.grid(row=5, column=0, columnspan=2, pady=10)
        ttk.Button(frame_botones, text="Asignar", command=self._guardar).pack(
            side="left", padx=5
        )
        ttk.Button(frame_botones, text="Cancelar", command=self.destroy).pack(
            side="left", padx=5
        )

        self.bind("<Return>", lambda e: self._guardar())
        self.bind("<Escape>", lambda e: self.destroy())

    def _guardar(self):
        if not self._combo_paciente.get():
            messagebox.showwarning(
                "Paciente requerido", "Seleccione un paciente.", parent=self
            )
            return
        if not self._combo_odontologo.get():
            messagebox.showwarning(
                "Odontólogo requerido", "Seleccione un odontólogo.", parent=self
            )
            return

        paciente_id = int(self._combo_paciente.get().split(":")[0])
        odontologo_id = int(self._combo_odontologo.get().split(":")[0])
        fecha = self._entry_fecha.get().strip()
        hora = self._entry_hora.get().strip()

        if not fecha or not hora:
            messagebox.showwarning(
                "Campos incompletos", "Fecha y hora son obligatorios.", parent=self
            )
            return

        self.resultado = {
            "paciente_id": paciente_id,
            "odontologo_id": odontologo_id,
            "fecha": fecha,
            "hora": hora,
            "motivo": self._entry_motivo.get().strip(),
        }
        self.destroy()
