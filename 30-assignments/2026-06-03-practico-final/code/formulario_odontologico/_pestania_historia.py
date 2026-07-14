import tkinter as tk
from tkinter import ttk, messagebox

from consultorio import Consultorio, ConsultorioError
from formulario_odontologico._dialogos import DialogoSeleccionOdontologo


class PestaniaHistoriaClinica(ttk.Frame):
    def __init__(self, parent, consultorio: Consultorio):
        super().__init__(parent)
        self._consultorio = consultorio
        self._paciente_actual: int | None = None
        self._construir()

    def _construir(self):
        frame_seleccion = ttk.Frame(self)
        frame_seleccion.pack(fill="x", padx=10, pady=(10, 0))

        ttk.Label(frame_seleccion, text="Paciente:").pack(side="left")
        self._combo_pacientes = ttk.Combobox(
            frame_seleccion, state="readonly", width=45
        )
        self._combo_pacientes.pack(side="left", padx=5)
        ttk.Button(
            frame_seleccion, text="Ver Historial", command=self._cargar_historial
        ).pack(side="left")
        self._combo_pacientes.bind(
            "<<ComboboxSelected>>", lambda e: self._cargar_historial()
        )

        frame_tree = ttk.Frame(self)
        frame_tree.pack(fill="both", expand=True, padx=10, pady=10)

        columnas = ("fecha", "odontologo", "diagnostico", "procedimiento")
        self._tree = ttk.Treeview(frame_tree, columns=columnas, show="headings")
        for col, titulo, ancho in [
            ("fecha", "Fecha", 110),
            ("odontologo", "Odontólogo", 180),
            ("diagnostico", "Diagnóstico", 250),
            ("procedimiento", "Procedimiento", 250),
        ]:
            self._tree.heading(col, text=titulo)
            self._tree.column(col, width=ancho)
        self._tree.pack(side="left", fill="both", expand=True)

        scroll = ttk.Scrollbar(frame_tree, orient="vertical", command=self._tree.yview)
        scroll.pack(side="right", fill="y")
        self._tree.configure(yscrollcommand=scroll.set)

        frame_form = ttk.LabelFrame(self, text="Nueva entrada")
        frame_form.pack(fill="x", padx=10, pady=(0, 10))

        ttk.Label(frame_form, text="Diagnóstico:").grid(
            row=0, column=0, padx=5, pady=2, sticky="e"
        )
        self._entry_diagnostico = ttk.Entry(frame_form, width=50)
        self._entry_diagnostico.grid(row=0, column=1, padx=5, pady=2)

        ttk.Label(frame_form, text="Procedimiento:").grid(
            row=1, column=0, padx=5, pady=2, sticky="e"
        )
        self._entry_procedimiento = ttk.Entry(frame_form, width=50)
        self._entry_procedimiento.grid(row=1, column=1, padx=5, pady=2)

        ttk.Label(frame_form, text="Observaciones:").grid(
            row=2, column=0, padx=5, pady=2, sticky="e"
        )
        self._entry_observaciones = ttk.Entry(frame_form, width=50)
        self._entry_observaciones.grid(row=2, column=1, padx=5, pady=2)

        frame_botones = ttk.Frame(frame_form)
        frame_botones.grid(row=3, column=0, columnspan=2, pady=5)
        ttk.Button(
            frame_botones, text="Registrar Entrada", command=self._registrar_entrada
        ).pack()

        self._cargar_combo_pacientes()

    def _cargar_combo_pacientes(self):
        try:
            pacientes = self._consultorio.listar_pacientes()
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return
        valores = [f"{p.id}: {p.nombre} {p.apellido} (DNI: {p.dni})" for p in pacientes]
        self._combo_pacientes["values"] = valores
        if valores:
            self._combo_pacientes.current(0)
            self._cargar_historial()

    def _cargar_historial(self, *_args):
        for item in self._tree.get_children():
            self._tree.delete(item)
        seleccion = self._combo_pacientes.get()
        if not seleccion:
            return
        paciente_id = int(seleccion.split(":")[0])
        self._paciente_actual = paciente_id
        try:
            historial = self._consultorio.listar_historia_clinica(paciente_id)
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return
        for hc in historial:
            self._tree.insert(
                "",
                "end",
                values=(
                    hc.fecha,
                    hc.odontologo_nombre,
                    hc.diagnostico,
                    hc.procedimiento,
                ),
            )

    def _registrar_entrada(self):
        if self._paciente_actual is None:
            messagebox.showwarning(
                "Paciente requerido", "Seleccione un paciente primero."
            )
            return
        diagnostico = self._entry_diagnostico.get().strip()
        procedimiento = self._entry_procedimiento.get().strip()
        if not diagnostico or not procedimiento:
            messagebox.showwarning(
                "Campos incompletos", "Diagnóstico y procedimiento son obligatorios."
            )
            return

        try:
            odontologos = self._consultorio.listar_odontologos()
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return
        if not odontologos:
            messagebox.showinfo(
                "Sin odontólogos", "No hay odontólogos registrados en el sistema."
            )
            return

        dialogo = DialogoSeleccionOdontologo(self, odontologos)
        if dialogo.resultado is None:
            return

        try:
            self._consultorio.registrar_entrada_historia(
                paciente_id=self._paciente_actual,
                odontologo_id=dialogo.resultado,
                diagnostico=diagnostico,
                procedimiento=procedimiento,
                observaciones=self._entry_observaciones.get().strip(),
            )
            self._cargar_historial()
            self._entry_diagnostico.delete(0, tk.END)
            self._entry_procedimiento.delete(0, tk.END)
            self._entry_observaciones.delete(0, tk.END)
            messagebox.showinfo("Éxito", "Entrada registrada en la historia clínica.")
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
