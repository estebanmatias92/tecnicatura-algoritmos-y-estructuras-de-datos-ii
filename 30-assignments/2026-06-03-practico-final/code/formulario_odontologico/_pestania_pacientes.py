from tkinter import ttk, messagebox

from consultorio import (
    Consultorio,
    ConsultorioError,
    DNIExistenteError,
    Paciente,
)
from formulario_odontologico._dialogos import DialogoPaciente


class PestaniaPacientes(ttk.Frame):
    def __init__(self, parent, consultorio: Consultorio):
        super().__init__(parent)
        self._consultorio = consultorio
        self._construir()

    def _construir(self):
        frame_busqueda = ttk.Frame(self)
        frame_busqueda.pack(fill="x", padx=10, pady=(10, 0))

        ttk.Label(frame_busqueda, text="Buscar DNI:").pack(side="left")
        self._entry_busqueda = ttk.Entry(frame_busqueda, width=20)
        self._entry_busqueda.pack(side="left", padx=5)
        ttk.Button(frame_busqueda, text="Buscar", command=self._buscar).pack(
            side="left", padx=2
        )
        ttk.Button(frame_busqueda, text="Mostrar Todos", command=self._refrescar).pack(
            side="left", padx=2
        )
        self._entry_busqueda.bind("<Return>", lambda e: self._buscar())

        frame_tree = ttk.Frame(self)
        frame_tree.pack(fill="both", expand=True, padx=10, pady=10)

        columnas = ("dni", "nombre", "apellido", "telefono")
        self._tree = ttk.Treeview(
            frame_tree, columns=columnas, show="headings", selectmode="browse"
        )
        for col, titulo in zip(columnas, ["DNI", "Nombre", "Apellido", "Teléfono"]):
            self._tree.heading(
                col, text=titulo, command=lambda c=col: self._ordenar_por(c)
            )
            self._tree.column(col, width=120)
        self._tree.pack(side="left", fill="both", expand=True)

        scroll = ttk.Scrollbar(frame_tree, orient="vertical", command=self._tree.yview)
        scroll.pack(side="right", fill="y")
        self._tree.configure(yscrollcommand=scroll.set)

        self._tree.bind("<Double-1>", lambda e: self._modificar())

        frame_botones = ttk.Frame(self)
        frame_botones.pack(fill="x", padx=10, pady=(0, 10))
        ttk.Button(frame_botones, text="Nuevo", command=self._nuevo).pack(
            side="left", padx=2
        )
        ttk.Button(frame_botones, text="Modificar", command=self._modificar).pack(
            side="left", padx=2
        )
        ttk.Button(frame_botones, text="Eliminar", command=self._eliminar).pack(
            side="left", padx=2
        )

        self._orden_columna = None
        self._orden_inverso = False
        self._refrescar()

    def _refrescar(self):
        for item in self._tree.get_children():
            self._tree.delete(item)
        try:
            pacientes = self._consultorio.listar_pacientes()
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return
        for p in pacientes:
            self._tree.insert(
                "", "end", values=(p.dni, p.nombre, p.apellido, p.telefono)
            )

    def _buscar(self):
        dni = self._entry_busqueda.get().strip()
        if not dni:
            self._refrescar()
            return
        for item in self._tree.get_children():
            self._tree.delete(item)
        try:
            paciente = self._consultorio.buscar_paciente_por_dni(dni)
        except ConsultorioError as e:
            messagebox.showerror("Error", str(e))
            return
        if paciente:
            self._tree.insert(
                "",
                "end",
                values=(
                    paciente.dni,
                    paciente.nombre,
                    paciente.apellido,
                    paciente.telefono,
                ),
            )
        else:
            messagebox.showinfo(
                "Sin resultados", f"No se encontró paciente con DNI {dni}"
            )

    def _obtener_seleccionado(self) -> Paciente | None:
        seleccion = self._tree.selection()
        if not seleccion:
            messagebox.showwarning(
                "Selección requerida", "Seleccione un paciente de la lista."
            )
            return None
        dni = self._tree.item(seleccion[0], "values")[0]
        try:
            return self._consultorio.buscar_paciente_por_dni(dni)
        except ConsultorioError:
            return None

    def _nuevo(self):
        dialogo = DialogoPaciente(self, "Registrar Paciente")
        if dialogo.resultado:
            try:
                self._consultorio.registrar_paciente(dialogo.resultado)
                self._refrescar()
                messagebox.showinfo("Éxito", "Paciente registrado correctamente.")
            except DNIExistenteError as e:
                messagebox.showerror("DNI duplicado", str(e))
            except ConsultorioError as e:
                messagebox.showerror("Error", str(e))

    def _modificar(self):
        paciente = self._obtener_seleccionado()
        if not paciente:
            return
        dialogo = DialogoPaciente(self, "Modificar Paciente", paciente=paciente)
        if dialogo.resultado:
            try:
                self._consultorio.modificar_paciente(paciente.id, dialogo.resultado)
                self._refrescar()
                messagebox.showinfo("Éxito", "Paciente modificado correctamente.")
            except DNIExistenteError as e:
                messagebox.showerror("DNI duplicado", str(e))
            except ConsultorioError as e:
                messagebox.showerror("Error", str(e))

    def _eliminar(self):
        paciente = self._obtener_seleccionado()
        if not paciente:
            return
        if messagebox.askyesno(
            "Confirmar eliminación",
            f"¿Está seguro de eliminar a {paciente.nombre} {paciente.apellido} (DNI: {paciente.dni})?\n\n"
            "Esta acción es una baja lógica.",
        ):
            try:
                self._consultorio.eliminar_paciente(paciente.id)
                self._refrescar()
                messagebox.showinfo("Éxito", "Paciente eliminado correctamente.")
            except ConsultorioError as e:
                messagebox.showerror("Error", str(e))

    def _ordenar_por(self, columna: str):
        if self._orden_columna == columna:
            self._orden_inverso = not self._orden_inverso
        else:
            self._orden_columna = columna
            self._orden_inverso = False
        items = [
            (self._tree.set(item, columna), item)
            for item in self._tree.get_children("")
        ]
        items.sort(reverse=self._orden_inverso)
        for idx, (_, item) in enumerate(items):
            self._tree.move(item, "", idx)
        self._tree.heading(columna)
