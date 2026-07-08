# Consigna 6.1 - Desarrollar una App que permita manejar distintos drones
# Consigna 6.2 - Implementar interfaz Abstracta (ABC) para pilotear drones

from abc import ABC, abstractmethod


class Dron(ABC):
    """Clase abstracta que define la interfaz para pilotear cualquier dron."""

    def __init__(self, nombre: str):
        self.nombre = nombre
        self._encendido = False
        self._velocidad = 0

    @abstractmethod
    def despegar(self) -> str:
        pass

    @abstractmethod
    def aterrizar(self) -> str:
        pass

    @abstractmethod
    def acelerar(self) -> str:
        pass

    @abstractmethod
    def frenar(self) -> str:
        pass

    @abstractmethod
    def doblar_izquierda(self) -> str:
        pass

    @abstractmethod
    def doblar_derecha(self) -> str:
        pass

    @abstractmethod
    def sacar_foto(self) -> str:
        pass

    def pilotear(self, comando: str) -> str:
        """Método concreto que enruta comandos según el menú."""
        comandos = {
            "1": self.despegar,
            "2": self.aterrizar,
            "3": self.acelerar,
            "4": self.frenar,
            "5": self.doblar_izquierda,
            "6": self.doblar_derecha,
            "7": self.sacar_foto,
        }
        accion = comandos.get(comando)
        if accion:
            return accion()
        return "Comando no válido."


class Tricoptero(Dron):
    def __init__(self):
        super().__init__("Tricóptero (3 hélices)")

    def despegar(self) -> str:
        self._encendido = True
        return f"🛸 {self.nombre} despegando verticalmente — estable."

    def aterrizar(self) -> str:
        self._encendido = False
        self._velocidad = 0
        return f"🛸 {self.nombre} aterrizando suavemente."

    def acelerar(self) -> str:
        self._velocidad += 10
        return f"🛸 {self.nombre} acelerando a {self._velocidad} km/h."

    def frenar(self) -> str:
        self._velocidad = max(0, self._velocidad - 10)
        return f"🛸 {self.nombre} frenando a {self._velocidad} km/h."

    def doblar_izquierda(self) -> str:
        return f"🛸 {self.nombre} girando a la izquierda (inclinación 15°)."

    def doblar_derecha(self) -> str:
        return f"🛸 {self.nombre} girando a la derecha (inclinación 15°)."

    def sacar_foto(self) -> str:
        return f"📸 {self.nombre} capturando foto — 12 MP."


class Cuadricoptero(Dron):
    def __init__(self):
        super().__init__("Cuadricóptero (4 hélices)")

    def despegar(self) -> str:
        self._encendido = True
        return f"🛸 {self.nombre} despegando — vuelo estable."

    def aterrizar(self) -> str:
        self._encendido = False
        self._velocidad = 0
        return f"🛸 {self.nombre} aterrizando con precisión."

    def acelerar(self) -> str:
        self._velocidad += 15
        return f"🛸 {self.nombre} acelerando a {self._velocidad} km/h."

    def frenar(self) -> str:
        self._velocidad = max(0, self._velocidad - 15)
        return f"🛸 {self.nombre} frenando a {self._velocidad} km/h."

    def doblar_izquierda(self) -> str:
        return f"🛸 {self.nombre} girando a la izquierda (ángulo 20°)."

    def doblar_derecha(self) -> str:
        return f"🛸 {self.nombre} girando a la derecha (ángulo 20°)."

    def sacar_foto(self) -> str:
        return f"📸 {self.nombre} capturando foto — 20 MP con estabilización."


class Hexacoptero(Dron):
    def __init__(self):
        super().__init__("Hexacóptero (6 hélices)")

    def despegar(self) -> str:
        self._encendido = True
        return f"🛸 {self.nombre} despegando — máxima estabilidad."

    def aterrizar(self) -> str:
        self._encendido = False
        self._velocidad = 0
        return f"🛸 {self.nombre} aterrizando con redundancia."

    def acelerar(self) -> str:
        self._velocidad += 20
        return f"🛸 {self.nombre} acelerando a {self._velocidad} km/h."

    def frenar(self) -> str:
        self._velocidad = max(0, self._velocidad - 20)
        return f"🛸 {self.nombre} frenando a {self._velocidad} km/h."

    def doblar_izquierda(self) -> str:
        return f"🛸 {self.nombre} girando a la izquierda (precisión mejorada)."

    def doblar_derecha(self) -> str:
        return f"🛸 {self.nombre} girando a la derecha (precisión mejorada)."

    def sacar_foto(self) -> str:
        return f"📸 {self.nombre} capturando foto — 48 MP con zoom óptico."


class Octocoptero(Dron):
    def __init__(self):
        super().__init__("Octocóptero (8 hélices)")

    def despegar(self) -> str:
        self._encendido = True
        return f"🛸 {self.nombre} despegando — potencia profesional."

    def aterrizar(self) -> str:
        self._encendido = False
        self._velocidad = 0
        return f"🛸 {self.nombre} aterrizando con tolerancia a fallos."

    def acelerar(self) -> str:
        self._velocidad += 25
        return f"🛸 {self.nombre} acelerando a {self._velocidad} km/h."

    def frenar(self) -> str:
        self._velocidad = max(0, self._velocidad - 25)
        return f"🛸 {self.nombre} frenando a {self._velocidad} km/h."

    def doblar_izquierda(self) -> str:
        return f"🛸 {self.nombre} girando a la izquierda (radio amplio)."

    def doblar_derecha(self) -> str:
        return f"🛸 {self.nombre} girando a la derecha (radio amplio)."

    def sacar_foto(self) -> str:
        return f"📸 {self.nombre} capturando foto — 64 MP + video 4K."


class Coaxial(Dron):
    def __init__(self):
        super().__init__("Coaxial (hélices coaxiales)")

    def despegar(self) -> str:
        self._encendido = True
        return f"🛸 {self.nombre} despegando — diseño compacto y potente."

    def aterrizar(self) -> str:
        self._encendido = False
        self._velocidad = 0
        return f"🛸 {self.nombre} aterrizando en espacios reducidos."

    def acelerar(self) -> str:
        self._velocidad += 30
        return f"🛸 {self.nombre} acelerando a {self._velocidad} km/h (alta velocidad)."

    def frenar(self) -> str:
        self._velocidad = max(0, self._velocidad - 30)
        return f"🛸 {self.nombre} frenando a {self._velocidad} km/h."

    def doblar_izquierda(self) -> str:
        return f"🛸 {self.nombre} girando a la izquierda (rápido y ágil)."

    def doblar_derecha(self) -> str:
        return f"🛸 {self.nombre} girando a la derecha (rápido y ágil)."

    def sacar_foto(self) -> str:
        return f"📸 {self.nombre} capturando foto — 8 MP (dron de carreras)."


def mostrar_menu(dron: Dron):
    """Muestra el menú de control para el dron activo."""
    print(f"\n=== Pilotando: {dron.nombre} ===")
    print("1. Despegar")
    print("2. Aterrizar")
    print("3. Acelerar")
    print("4. Frenar")
    print("5. Doblar a la izquierda")
    print("6. Doblar a la derecha")
    print("7. Sacar foto")
    print("0. Salir / Cambiar dron")


def seleccionar_dron() -> Dron | None:
    """Menú de selección de dron."""
    drones: list[Dron] = [
        Tricoptero(),
        Cuadricoptero(),
        Hexacoptero(),
        Octocoptero(),
        Coaxial(),
    ]

    print("\n=== SELECCIÓN DE DRON ===")
    for i, d in enumerate(drones, 1):
        print(f"{i}. {d.nombre}")
    print("0. Salir")

    opcion = input("\nSeleccioná un dron: ").strip()
    if opcion == "0":
        return None
    try:
        idx = int(opcion) - 1
        if 0 <= idx < len(drones):
            return drones[idx]
    except ValueError:
        pass
    print("Opción inválida.")
    return seleccionar_dron()


def main():
    print("=== App de Drones — Interfaz Abstracta (ABC) ===\n")

    while True:
        dron = seleccionar_dron()
        if dron is None:
            print("¡Hasta luego!")
            break

        while True:
            mostrar_menu(dron)
            cmd = input("\nComando: ").strip()
            if cmd == "0":
                break
            print(dron.pilotear(cmd))


if __name__ == "__main__":
    main()
