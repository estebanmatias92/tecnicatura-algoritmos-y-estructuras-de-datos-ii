class MenuEngine:

    @staticmethod
    def mostrar_titulo(texto: str):
        ancho = 60
        print("=" * ancho)
        print(f"  {texto}")
        print("=" * ancho)

    @staticmethod
    def separador():
        print("-" * 60)

    @staticmethod
    def pausa():
        input("\nPresione Enter para continuar...")

    @staticmethod
    def ejecutar_menu(opciones: list[tuple[int, str]], titulo: str) -> int:
        while True:
            MenuEngine.mostrar_titulo(titulo)
            for codigo, desc in opciones:
                print(f"  [{codigo}] {desc}")
            print()
            try:
                eleccion = int(input("  Seleccione una opción: "))
                codigos = [c for c, _ in opciones]
                if eleccion in codigos:
                    return eleccion
                print(f"\n  Opción inválida. Elija entre {codigos}.")
            except ValueError:
                print("\n  Debe ingresar un número.")
            MenuEngine.pausa()
