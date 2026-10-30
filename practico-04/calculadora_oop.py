# Consigna 1.7 - Crear una Clase en Python
# Consigna 1.8 - Asignarles atributos de clase e instancia
# Consigna 1.9 - Asignar métodos de Instancia, Clase y estáticos
# Consigna 1.10 - Realizar una calculadora que consuma estos métodos


class Calculadora:
    # --- Atributos de clase ---
    version = "1.0"
    descripcion = "Calculadora orientada a objetos en Python"

    def __init__(self, nombre="Calculadora Genérica"):
        # --- Atributos de instancia ---
        self.nombre = nombre
        self._ultimo_resultado = 0
        self.historial = []

    # --- Métodos de instancia ---

    def sumar(self, a, b):
        resultado = a + b
        self._ultimo_resultado = resultado
        self.historial.append(f"{a} + {b} = {resultado}")
        return resultado

    def restar(self, a, b):
        resultado = a - b
        self._ultimo_resultado = resultado
        self.historial.append(f"{a} - {b} = {resultado}")
        return resultado

    def multiplicar(self, a, b):
        resultado = a * b
        self._ultimo_resultado = resultado
        self.historial.append(f"{a} * {b} = {resultado}")
        return resultado

    def dividir(self, a, b):
        if b == 0:
            raise ValueError("No se puede dividir por cero")
        resultado = a / b
        self._ultimo_resultado = resultado
        self.historial.append(f"{a} / {b} = {resultado}")
        return resultado

    def potencia(self, base, exp):
        resultado = base ** exp
        self._ultimo_resultado = resultado
        self.historial.append(f"{base} ** {exp} = {resultado}")
        return resultado

    def mostrar_historial(self):
        return self.historial

    def obtener_ultimo_resultado(self):
        return self._ultimo_resultado

    # --- Métodos de clase ---

    @classmethod
    def cambiar_version(cls, nueva_version):
        cls.version = nueva_version

    @classmethod
    def crear_calculadora_cientifica(cls):
        return cls("Calculadora Científica")

    @classmethod
    def desde_descripcion(cls, descripcion):
        calc = cls()
        calc.descripcion = descripcion
        return calc

    # --- Métodos estáticos ---

    @staticmethod
    def es_entero(valor):
        return isinstance(valor, int)

    @staticmethod
    def validar_numeros(*args):
        return all(isinstance(a, (int, float)) for a in args)

    @staticmethod
    def sumar_dos(a, b):
        return a + b


if __name__ == "__main__":
    # Consigna 1.10 - Realizar una calculadora que consuma estos métodos
    print("=" * 50)
    print("     DEMOSTRACIÓN - CALCULADORA OOP")
    print("=" * 50)

    # Crear instancia
    calc = Calculadora("Mi Calculadora")
    print(f"\n[1.7] Clase creada: {calc.__class__.__name__}")
    print(f"      Instancia: {calc.nombre}")

    # Atributos de clase
    print(f"\n[1.8] Atributos de clase:")
    print(f"      Versión: {Calculadora.version}")
    print(f"      Descripción: {Calculadora.descripcion}")

    # Atributos de instancia
    print(f"\n[1.8] Atributos de instancia:")
    print(f"      Nombre: {calc.nombre}")
    print(f"      Historial: {calc.historial}")
    print(f"      Último resultado: {calc.obtener_ultimo_resultado()}")

    # Métodos de instancia
    print(f"\n[1.9-1.10] Métodos de instancia:")
    print(f"      5 + 3 = {calc.sumar(5, 3)}")
    print(f"      10 - 4 = {calc.restar(10, 4)}")
    print(f"      6 * 7 = {calc.multiplicar(6, 7)}")
    print(f"      15 / 3 = {calc.dividir(15, 3)}")
    print(f"      2 ** 8 = {calc.potencia(2, 8)}")

    # Método de clase - cambiar atributo de clase
    print(f"\n[1.9-1.10] Métodos de clase:")
    Calculadora.cambiar_version("2.0")
    print(f"      Versión cambiada a: {Calculadora.version}")

    # Método de clase - factory
    calc_cientifica = Calculadora.crear_calculadora_cientifica()
    print(f"      Factory method: {calc_cientifica.nombre}")

    # Método estático
    print(f"\n[1.9-1.10] Métodos estáticos:")
    print(f"      ¿5 es entero? {Calculadora.es_entero(5)}")
    print(f"      ¿3.14 es entero? {Calculadora.es_entero(3.14)}")
    print(f"      ¿Son válidos (5, 3.14)? {Calculadora.validar_numeros(5, 3.14)}")
    print(f"      ¿Son válidos (5, 'hola')? {Calculadora.validar_numeros(5, 'hola')}")

    # Historial
    print(f"\n[1.10] Historial de operaciones:")
    for op in calc.mostrar_historial():
        print(f"      • {op}")

    print(f"\n[1.10] Último resultado acumulado: {calc.obtener_ultimo_resultado()}")
    print("\n" + "=" * 50)
