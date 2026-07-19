# Consigna 7.1 - App Duck Typing: animales con métodos iguales pero implementación diferente


class Perro:
    def __init__(self, nombre: str):
        self.nombre = nombre

    def hablar(self) -> str:
        return f"{self.nombre} dice: ¡Guau!"


class Gato:
    def __init__(self, nombre: str):
        self.nombre = nombre

    def hablar(self) -> str:
        return f"{self.nombre} dice: ¡Miau!"


class Vaca:
    def __init__(self, nombre: str):
        self.nombre = nombre

    def hablar(self) -> str:
        return f"{self.nombre} dice: ¡Muuu!"


class Abeja:
    def __init__(self, nombre: str):
        self.nombre = nombre

    def hablar(self) -> str:
        return f"{self.nombre} dice: ¡Bzzzz!"


class Pato:
    def __init__(self, nombre: str):
        self.nombre = nombre

    def hablar(self) -> str:
        return f"{self.nombre} dice: ¡Cuac!"


def main():
    print("=== Duck Typing en Python ===\n")
    print("A Python no le importa el tipo de los objetos, solo sus métodos.\n")

    # Lista de objetos de distintas clases que tienen el método .hablar()
    animales = [
        Perro("Rex"),
        Gato("Michi"),
        Vaca("Lola"),
        Abeja("Bibi"),
        Pato("Donald"),
    ]

    # Duck Typing: el bucle funciona porque todos implementan .hablar()
    for animal in animales:
        print(animal.hablar())

    print("\n--- Demostración del concepto ---")
    print("Cada objeto en la lista es de una clase distinta.")
    print("Python NO verifica el tipo — solo busca el método .hablar().")
    print("Eso es Duck Typing: 'Si habla como animal, entonces es un animal'.")


if __name__ == "__main__":
    main()
