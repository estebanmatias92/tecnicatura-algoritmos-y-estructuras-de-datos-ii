# Consigna 3.3 - Dashboard unificado con menu principal
# Consigna 3.2 - Acceso a Repair Center desde el menu
# Consigna 3.1 - Acceso a Calculadora desde el menu

import tkinter as tk
from app.database import init_db, seed_admin
from app.login import Login
from app.calculadora import Calculadora
from app.repair_center import RepairCenter


class MainApp:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Sistema de Gestion - Repair Center")
        self.root.geometry("400x300")
        self.root.resizable(False, False)
        self._init_system()
        self._show_login()

    def _init_system(self):
        init_db()
        seed_admin()

    def _show_login(self):
        self.root.withdraw()
        Login(self.root, self._on_login_success)

    def _on_login_success(self):
        self.root.deiconify()
        self._build_dashboard()

    def _build_dashboard(self):
        for widget in self.root.winfo_children():
            widget.destroy()

        tk.Label(
            self.root,
            text="Panel Principal",
            font=("Arial", 16),
        ).pack(pady=(30, 20))

        tk.Button(
            self.root,
            text="Calculadora",
            command=self.abrir_calculadora,
            width=25,
            height=2,
        ).pack(pady=5)

        tk.Button(
            self.root,
            text="Repair Center",
            command=self.abrir_repair_center,
            width=25,
            height=2,
        ).pack(pady=5)

        tk.Button(
            self.root,
            text="Salir",
            command=self.root.quit,
            width=25,
            height=2,
        ).pack(pady=5)

    def abrir_calculadora(self):
        Calculadora(self.root)

    def abrir_repair_center(self):
        RepairCenter(self.root)

    def ejecutar(self):
        self.root.mainloop()


if __name__ == "__main__":
    app = MainApp()
    app.ejecutar()
