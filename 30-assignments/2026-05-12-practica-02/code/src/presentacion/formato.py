class Formato:

    @staticmethod
    def encabezado(texto: str):
        print()
        print(f"╔══ {texto} ══╗")

    @staticmethod
    def separador():
        print("─" * 50)

    @staticmethod
    def resultado(texto: str):
        print(f"  → {texto}")

    @staticmethod
    def error(texto: str):
        print(f"  ✗ {texto}")

    @staticmethod
    def lista(items: list):
        for i, item in enumerate(items, 1):
            print(f"  {i}. {item}")
