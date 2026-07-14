from tkinter import ttk, messagebox

from consultorio import (
    Consultorio,
    ConsultorioError,
    TelefonoFaltanteError,
    TurnoSuperpuestoError,
    TransicionInvalidaError,
)
from formulario_odontologico._dialogos import DialogoAsignarTurno


class PestaniaTurnos(ttk.Frame):
    def __init__(self, parent, consultorio: Consultorio):
        super().__init__(parent)
        self._consultorio = consultorio
        self._construir()

    def _construir(self):
        columnas = ("fecha", "hora", "paciente", "odontologo", "estado")
        self._tree = ttk.Treeview(
            self, columns=columnas, show="headings", selectmode="browse"
        )
        for col, titulo, ancho in [
            ("fecha", "Fecha", 110),
            ("hora", "Hora", 70),
            ("paciente", "Paciente", 180),
            ("odontologo", "Odontólogo", 180),
            ("estado", "Estado", 100),
        ]:
            self._tree.heading(col, text=titulo)
            self._tree.column(col, width=ancho)
        self._tree.pack(fill="both", expand=True, padx=10, pady=10)

        scroll = ttk.Scrollbar(self, orient="vertical", command=self._tree.yview)
        scroll.place(in_=self._tree, relx=1.0, rely=0, relheight=1.0, anchor="ne")
        self._tree.configure(yscrollcommand=scroll.set)

        frame_botones = ttk.Frame(self)
        frame_botones.pack(fill="x", padx=10, pady=(0, 10))
        ttk.Button(frame_botones, text="Asignar Turno", command=self._asignar).pack(
            side="left", padx=2
        )
        ttk.Button(frame_botones, text="Confirmar", command=self._confirmar).pack(
            side="left", padx=2
        )
        ttk.Button(frame_botones, text="Cancelar", command=self._cancelar).pack(
            side="left", padx=2
        )

        self._refrescar()

    def _refrescar(self):
        for item in self._tree.get_children():
            self._tree.delete(item)
        try:
            turnos = self._consultorio.listar_turnos()
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return
        for t in turnos:
            self._tree.insert(
                "",
                "end",
                iid=str(t.id),
                values=(
                    t.fecha,
                    t.hora,
                    t.paciente_nombre,
                    t.odontologo_nombre,
                    t.estado,
                ),
            )

    def _obtener_turno_id(self) -> int | None:
        seleccion = self._tree.selection()
        if not seleccion:
            messagebox.showwarning(
                "Selección requerida", "Seleccione un turno de la lista."
            )
            return None
        return int(seleccion[0])

    def _asignar(self):
        try:
            pacientes = self._consultorio.listar_pacientes()
            odontologos = self._consultorio.listar_odontologos()
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return

        if not pacientes:
            messagebox.showinfo(
                "Sin pacientes",
                "Debe registrar al menos un paciente antes de asignar un turno.",
            )
            return

        dialogo = DialogoAsignarTurno(self, pacientes, odontologos)
        if not dialogo.resultado:
            return

        d = dialogo.resultado
        try:
            self._consultorio.asignar_turno(
                paciente_id=d["paciente_id"],
                odontologo_id=d["odontologo_id"],
                fecha=d["fecha"],
                hora=d["hora"],
                motivo=d["motivo"],
            )
            self._refrescar()
            messagebox.showinfo("Éxito", "Turno asignado correctamente.")
        except TelefonoFaltanteError as e:
            messagebox.showerror("Teléfono requerido", str(e))
        except TurnoSuperpuestoError as e:
            messagebox.showerror("Superposición", str(e))
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
        except Exception as e:
            messagebox.showerror("Error inesperado", str(e))

    def _confirmar(self):
        turno_id = self._obtener_turno_id()
        if not turno_id:
            return
        try:
            self._consultorio.confirmar_turno(turno_id)
            self._refrescar()
            messagebox.showinfo("Éxito", "Turno confirmado.")
        except TransicionInvalidaError as e:
            messagebox.showerror("Transición inválida", str(e))
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))

    def _cancelar(self):
        turno_id = self._obtener_turno_id()
        if not turno_id:
            return
        if messagebox.askyesno(
            "Cancelar turno", "¿Está seguro de cancelar este turno?"
        ):
            try:
                self._consultorio.cancelar_turno(turno_id)
                self._refrescar()
                messagebox.showinfo("Éxito", "Turno cancelado.")
            except TransicionInvalidaError as e:
                messagebox.showerror("Transición inválida", str(e))
            except ConsultorioError as e:
                messagebox.showerror("Error", str(e))
