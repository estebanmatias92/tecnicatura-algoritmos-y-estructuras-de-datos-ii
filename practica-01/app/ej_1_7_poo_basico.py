# Consigna 1.7 - Crear una Clase en Python
# Consigna 1.8 - Asignarles atributos de clase e instancia
# Consigna 1.9 - Asignar métodos de Instancia, Clase y estáticos
# Consigna 1.10 - Realizar una calculadora que consuma estos métodos


class Calculadora:
    """Clase que demuestra atributos de clase/instancia y métodos de instancia/clase/estáticos."""

    # Atributo de clase
    version = "1.0"
    descripcion = "Calculadora OOP Demo"

    def __init__(self, nombre: str = "Calculadora Principal"):
        # Atributos de instancia
        self.nombre = nombre
        self._historial: list[str] = []

    # --- Métodos de instancia ---

    def sumar(self, a: float, b: float) -> float:
        resultado = a + b
        self._registrar(f"{a} + {b} = {resultado}")
        return resultado

    def restar(self, a: float, b: float) -> float:
        resultado = a - b
        self._registrar(f"{a} - {b} = {resultado}")
        return resultado

    def multiplicar(self, a: float, b: float) -> float:
        resultado = a * b
        self._registrar(f"{a} * {b} = {resultado}")
        return resultado

    def dividir(self, a: float, b: float) -> float:
        if b == 0:
            raise ValueError("No se puede dividir por cero")
        resultado = a / b
        self._registrar(f"{a} / {b} = {resultado}")
        return resultado

    def _registrar(self, operacion: str) -> None:
        self._historial.append(operacion)

    def mostrar_historial(self) -> list[str]:
        return self._historial.copy()

    # --- Método de clase ---

    @classmethod
    def mostrar_version(cls) -> str:
        return f"{cls.descripcion} — Versión {cls.version}"

    @classmethod
    def crear_calculadora_por_defecto(cls):
        return cls("Calculadora Default")

    # --- Método estático ---

    @staticmethod
    def validar_numeros(a, b) -> bool:
        return isinstance(a, (int, float)) and isinstance(b, (int, float))

    @staticmethod
    def descripcion_tipo() -> str:
        return "Calculadora con atributos de clase/instancia y métodos de instancia/clase/estáticos."


def main():
    print("=== Calculadora OOP ===\n")

    # Uso de atributo de clase
    print(f"Atributo de clase — version: {Calculadora.version}")
    print(f"Atributo de clase — descripcion: {Calculadora.descripcion}")

    # Crear instancias
    calc = Calculadora("Mi Calculadora")
    print(f"\nAtributo de instancia — nombre: {calc.nombre}")

    # Método de clase
    print(f"\nMétodo de clase — {Calculadora.mostrar_version()}")

    # Método estático
    print(f"Método estático — {Calculadora.descripcion_tipo()}")
    print(f"¿Son válidos 5 y 3?: {Calculadora.validar_numeros(5, 3)}")

    # Métodos de instancia
    print("\n--- Operaciones ---")
    print(f"Suma: 10 + 5 = {calc.sumar(10, 5)}")
    print(f"Resta: 10 - 5 = {calc.restar(10, 5)}")
    print(f"Multiplicación: 10 * 5 = {calc.multiplicar(10, 5)}")
    print(f"División: 10 / 5 = {calc.dividir(10, 5)}")

    print("\nHistorial de operaciones:")
    for op in calc.mostrar_historial():
        print(f"  • {op}")

    # Crear instancia usando método de clase
    calc_default = Calculadora.crear_calculadora_por_defecto()
    print(f"\nInstancia creada con método de clase: {calc_default.nombre}")


if __name__ == "__main__":
    main()
