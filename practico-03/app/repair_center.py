# Consigna 3.2 - Repair Center (ABM con listado Treeview + SQLite)

import tkinter as tk
from tkinter import ttk, messagebox
from app.database import (
    create_pedido,
    get_pedidos,
    update_pedido,
    delete_pedido,
)


class RepairCenter:
    def __init__(self, parent):
        self.ventana = tk.Toplevel(parent)
        self.ventana.title("Repair Center - Gestion de Pedidos")
        self.ventana.geometry("700x550")
        self.ventana.resizable(False, False)

        frame_form = tk.LabelFrame(self.ventana, text="Datos del Pedido", padx=10, pady=10)
        frame_form.pack(fill="x", padx=10, pady=5)

        tk.Label(frame_form, text="Cliente:").grid(row=0, column=0, sticky="w", pady=2)
        self.entry_cliente = tk.Entry(frame_form, width=40)
        self.entry_cliente.grid(row=0, column=1, pady=2)

        tk.Label(frame_form, text="Direccion:").grid(row=1, column=0, sticky="w", pady=2)
        self.entry_direccion = tk.Entry(frame_form, width=40)
        self.entry_direccion.grid(row=1, column=1, pady=2)

        tk.Label(frame_form, text="Inconveniente:").grid(row=2, column=0, sticky="w", pady=2)
        self.entry_inconveniente = tk.Entry(frame_form, width=40)
        self.entry_inconveniente.grid(row=2, column=1, pady=2)

        tk.Label(frame_form, text="Tecnico:").grid(row=3, column=0, sticky="w", pady=2)
        self.entry_tecnico = tk.Entry(frame_form, width=40)
        self.entry_tecnico.grid(row=3, column=1, pady=2)

        tk.Label(frame_form, text="Visita (AAAA-MM-DD HH:MM):").grid(row=4, column=0, sticky="w", pady=2)
        self.entry_visita = tk.Entry(frame_form, width=40)
        self.entry_visita.grid(row=4, column=1, pady=2)

        frame_botones = tk.Frame(frame_form)
        frame_botones.grid(row=5, column=0, columnspan=2, pady=10)

        tk.Button(frame_botones, text="Crear", command=self.crear_pedido, width=10).pack(side="left", padx=3)
        tk.Button(frame_botones, text="Modificar", command=self.modificar_pedido, width=10).pack(side="left", padx=3)
        tk.Button(frame_botones, text="Eliminar", command=self.eliminar_pedido, width=10).pack(side="left", padx=3)
        tk.Button(frame_botones, text="Limpiar", command=self.limpiar_campos, width=10).pack(side="left", padx=3)

        frame_lista = tk.LabelFrame(self.ventana, text="Pedidos Registrados", padx=10, pady=10)
        frame_lista.pack(fill="both", expand=True, padx=10, pady=5)

        columns = ("id", "cliente", "direccion", "inconveniente", "tecnico", "visita")
        self.tree = ttk.Treeview(frame_lista, columns=columns, show="headings", height=10)

        self.tree.heading("id", text="ID")
        self.tree.heading("cliente", text="Cliente")
        self.tree.heading("direccion", text="Direccion")
        self.tree.heading("inconveniente", text="Inconveniente")
        self.tree.heading("tecnico", text="Tecnico")
        self.tree.heading("visita", text="Visita")

        self.tree.column("id", width=30)
        self.tree.column("cliente", width=120)
        self.tree.column("direccion", width=120)
        self.tree.column("inconveniente", width=120)
        self.tree.column("tecnico", width=100)
        self.tree.column("visita", width=120)

        scrollbar = ttk.Scrollbar(frame_lista, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscrollcommand=scrollbar.set)

        self.tree.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

        self.tree.bind("<<TreeviewSelect>>", self.seleccionar_pedido)
        self.cargar_pedidos()
        self.pedido_seleccionado_id = None

    def cargar_pedidos(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        pedidos = get_pedidos()
        for p in pedidos:
            self.tree.insert(
                "", "end",
                values=(p["id"], p["cliente"], p["direccion"],
                        p["inconveniente"], p["tecnico"], p["visita"]),
            )

    def crear_pedido(self):
        datos = self._obtener_datos_form()
        if datos:
            create_pedido(*datos)
            self.limpiar_campos()
            self.cargar_pedidos()
            messagebox.showinfo("Exito", "Pedido creado correctamente")

    def modificar_pedido(self):
        if not self.pedido_seleccionado_id:
            messagebox.showwarning("Atencion", "Seleccione un pedido de la lista")
            return
        datos = self._obtener_datos_form()
        if datos:
            update_pedido(self.pedido_seleccionado_id, *datos)
            self.limpiar_campos()
            self.cargar_pedidos()
            messagebox.showinfo("Exito", "Pedido modificado correctamente")

    def eliminar_pedido(self):
        if not self.pedido_seleccionado_id:
            messagebox.showwarning("Atencion", "Seleccione un pedido de la lista")
            return
        if messagebox.askyesno("Confirmar", "¿Eliminar este pedido?"):
            delete_pedido(self.pedido_seleccionado_id)
            self.limpiar_campos()
            self.cargar_pedidos()
            messagebox.showinfo("Exito", "Pedido eliminado correctamente")

    def limpiar_campos(self):
        self.entry_cliente.delete(0, tk.END)
        self.entry_direccion.delete(0, tk.END)
        self.entry_inconveniente.delete(0, tk.END)
        self.entry_tecnico.delete(0, tk.END)
        self.entry_visita.delete(0, tk.END)
        self.pedido_seleccionado_id = None

    def seleccionar_pedido(self, event):
        seleccion = self.tree.selection()
        if not seleccion:
            return
        valores = self.tree.item(seleccion[0], "values")
        self.pedido_seleccionado_id = int(valores[0])
        self.entry_cliente.delete(0, tk.END)
        self.entry_cliente.insert(0, valores[1])
        self.entry_direccion.delete(0, tk.END)
        self.entry_direccion.insert(0, valores[2])
        self.entry_inconveniente.delete(0, tk.END)
        self.entry_inconveniente.insert(0, valores[3])
        self.entry_tecnico.delete(0, tk.END)
        self.entry_tecnico.insert(0, valores[4])
        self.entry_visita.delete(0, tk.END)
        self.entry_visita.insert(0, valores[5])

    def _obtener_datos_form(self):
        cliente = self.entry_cliente.get().strip()
        direccion = self.entry_direccion.get().strip()
        inconveniente = self.entry_inconveniente.get().strip()
        tecnico = self.entry_tecnico.get().strip()
        visita = self.entry_visita.get().strip()
        if not cliente or not direccion:
            messagebox.showerror("Error", "Cliente y Direccion son obligatorios")
            return None
        return (cliente, direccion, inconveniente, tecnico, visita)
