# Consigna 3.3 - Pantalla de Login (usuario y clave contra SQLite)

import tkinter as tk
from tkinter import messagebox
from app.database import validate_login


class Login:
    def __init__(self, parent, on_success):
        self.on_success = on_success
        self.ventana = tk.Toplevel(parent)
        self.ventana.title("Inicio de Sesion")
        self.ventana.geometry("300x200")
        self.ventana.resizable(False, False)

        tk.Label(self.ventana, text="Repair Center", font=("Arial", 14)).pack(pady=(20, 10))

        tk.Label(self.ventana, text="Usuario:").pack()
        self.entry_usuario = tk.Entry(self.ventana)
        self.entry_usuario.pack()
        self.entry_usuario.focus()

        tk.Label(self.ventana, text="Clave:").pack(pady=(5, 0))
        self.entry_clave = tk.Entry(self.ventana, show="*")
        self.entry_clave.pack()

        tk.Button(self.ventana, text="Ingresar", command=self.validar, width=15).pack(pady=15)
        self.entry_clave.bind("<Return>", lambda e: self.validar())

    def validar(self):
        usuario = self.entry_usuario.get().strip()
        clave = self.entry_clave.get().strip()
        if not usuario or not clave:
            messagebox.showerror("Error", "Ingrese usuario y clave")
            return
        if validate_login(usuario, clave):
            self.ventana.destroy()
            self.on_success()
        else:
            messagebox.showerror("Error", "Usuario o clave incorrectos")
            self.entry_clave.delete(0, tk.END)
            self.entry_usuario.focus()
