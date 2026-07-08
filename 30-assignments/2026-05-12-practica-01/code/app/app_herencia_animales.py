# Consigna 2.1 - Desarrollar una APP por consola con herencia Animal
# Consigna 2.2 - Implementar la Herencia (Perro, Vaca, Abeja heredan de Animal)
# Consigna 2.3 - Implementar __bases__ y __subclasses__()
# Consigna 2.4 - Implementar super()
# Consigna 2.5 - Crear Objetos y mostrar por consola
# Consigna 3.1 - Implementar dos métodos en alguna Clase y usar @property
# Consigna 3.2 - Implementar Encapsulamiento vía _variable / __variable
# Consigna 3.3 - Implementar los setter()


class Animal:
    """Clase base que demuestra encapsulamiento y @property."""

    # Atributo de clase
    clasificacion = "Animal"

    def __init__(self, nombre: str, edad: int):
        # Atributo público
        self.nombre = nombre
        # Atributo encapsulado (convención "protegido")
        self._sonido = ""
        # Atributo con name mangling (privado)
        self.__edad = edad

    # --- @property y setter (Consignas 3.1, 3.3) ---

    @property
    def edad(self) -> int:
        """Getter: expone __edad como propiedad."""
        return self.__edad

    @edad.setter
    def edad(self, valor: int) -> None:
        """Setter: valida que la edad sea positiva."""
        if valor < 0:
            raise ValueError("La edad no puede ser negativa.")
        self.__edad = valor

    @property
    def sonido(self) -> str:
        """Getter para atributo protegido _sonido."""
        return self._sonido

    @sonido.setter
    def sonido(self, valor: str) -> None:
        """Setter para _sonido."""
        self._sonido = valor

    # --- Métodos a sobrescribir ---

    def hablar(self) -> str:
        return f"{self.nombre} hace un sonido genérico."

    def moverse(self) -> str:
        return f"{self.nombre} se mueve de forma genérica."

    def describirme(self) -> str:
        # Consigna 2.4 - Uso de super() (en este caso no hay herencia, pero se demuestra el concepto)
        return f"Soy {self.nombre}, un {self.clasificacion} de {self.edad} años."


class Perro(Animal):
    def __init__(self, nombre: str, edad: int, raza: str = "Mestizo"):
        # Consigna 2.4 - super() para extender el constructor
        super().__init__(nombre, edad)
        self.raza = raza
        self._sonido = "Guau!"

    def hablar(self) -> str:
        return f"{self.nombre} dice: {self._sonido}"

    def moverse(self) -> str:
        return f"{self.nombre} camina con 4 patas."


class Vaca(Animal):
    def __init__(self, nombre: str, edad: int):
        super().__init__(nombre, edad)
        self._sonido = "Muuu!"

    def hablar(self) -> str:
        return f"{self.nombre} dice: {self._sonido}"

    def moverse(self) -> str:
        return f"{self.nombre} camina con 4 patas."


class Abeja(Animal):
    def __init__(self, nombre: str, edad: int):
        super().__init__(nombre, edad)
        self._sonido = "Bzzzz!"

    def hablar(self) -> str:
        return f"{self.nombre} dice: {self._sonido}"

    def moverse(self) -> str:
        return f"{self.nombre} vuela."


def main():
    print("=== App de Herencia Animal ===\n")

    # Crear objetos (Consigna 2.5)
    perro = Perro("Rex", 5, "Labrador")
    vaca = Vaca("Lola", 3)
    abeja = Abeja("Bibi", 1)

    animales = [perro, vaca, abeja]

    # Demostrar métodos polimórficos
    for animal in animales:
        print(animal.describirme())
        print(animal.hablar())
        print(animal.moverse())
        print()

    # Consigna 2.3 - __bases__ y __subclasses__()
    print("=== __bases__ y __subclasses__() ===\n")
    print(f"Clases base de Perro: {Perro.__bases__}")
    print(f"Clases base de Vaca: {Vaca.__bases__}")
    print(f"Clases base de Abeja: {Abeja.__bases__}")
    print(f"Subclases de Animal: {Animal.__subclasses__()}")

    # Demostrar @property y setter (Consignas 3.1, 3.3)
    print("\n=== @property y setters ===\n")
    print(f"Edad de {perro.nombre} (vía @property): {perro.edad}")
    perro.edad = 6  # Usa el setter
    print(f"Edad actualizada de {perro.nombre}: {perro.edad}")

    print(f"Sonido de {vaca.nombre} (vía @property): {vaca.sonido}")

    # Demostrar encapsulamiento (Consigna 3.2)
    print("\n=== Encapsulamiento ===\n")
    print(f"Atributo protegido _sonido accesible (convención): {perro._sonido}")
    try:
        print(perro.__edad)  # Error por name mangling
    except AttributeError as e:
        print(f"Atributo privado __edad NO accesible directamente: {e}")
        # Pero se puede acceder via name mangling (demostración)
        print(f"Acceso vía name mangling: {perro._Animal__edad}")


if __name__ == "__main__":
    main()
