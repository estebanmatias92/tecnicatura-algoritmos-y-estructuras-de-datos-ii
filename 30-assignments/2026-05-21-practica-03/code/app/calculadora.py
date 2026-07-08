# Consigna 3.1 - Calculadora (suma, resta, multiplicacion, division)

import tkinter as tk
from tkinter import messagebox


class Calculadora:
    def __init__(self, parent):
        self.ventana = tk.Toplevel(parent)
        self.ventana.title("Calculadora")
        self.ventana.geometry("300x250")
        self.ventana.resizable(False, False)

        tk.Label(self.ventana, text="Operando A:").pack(pady=(10, 0))
        self.entry_a = tk.Entry(self.ventana)
        self.entry_a.pack()

        tk.Label(self.ventana, text="Operando B:").pack(pady=(5, 0))
        self.entry_b = tk.Entry(self.ventana)
        self.entry_b.pack()

        frame_botones = tk.Frame(self.ventana)
        frame_botones.pack(pady=10)

        tk.Button(frame_botones, text="+", width=5, command=self.sumar).grid(row=0, column=0, padx=2)
        tk.Button(frame_botones, text="-", width=5, command=self.restar).grid(row=0, column=1, padx=2)
        tk.Button(frame_botones, text="*", width=5, command=self.multiplicar).grid(row=0, column=2, padx=2)
        tk.Button(frame_botones, text="/", width=5, command=self.dividir).grid(row=0, column=3, padx=2)

        self.resultado = tk.Label(self.ventana, text="Resultado: ---", font=("Arial", 12))
        self.resultado.pack(pady=10)

    def _obtener_operandos(self):
        try:
            a = float(self.entry_a.get())
            b = float(self.entry_b.get())
            return a, b
        except ValueError:
            messagebox.showerror("Error", "Ingrese numeros validos")
            return None, None

    def sumar(self):
        a, b = self._obtener_operandos()
        if a is not None:
            self.resultado.config(text=f"Resultado: {a + b}")

    def restar(self):
        a, b = self._obtener_operandos()
        if a is not None:
            self.resultado.config(text=f"Resultado: {a - b}")

    def multiplicar(self):
        a, b = self._obtener_operandos()
        if a is not None:
            self.resultado.config(text=f"Resultado: {a * b}")

    def dividir(self):
        a, b = self._obtener_operandos()
        if a is not None:
            try:
                self.resultado.config(text=f"Resultado: {a / b}")
            except ZeroDivisionError:
                messagebox.showerror("Error", "No se puede dividir por cero")


if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()
    app = Calculadora(root)
    root.mainloop()
