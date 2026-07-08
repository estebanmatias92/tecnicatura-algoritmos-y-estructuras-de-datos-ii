class Entrada:

    @staticmethod
    def input_int(mensaje: str, min_val: int | None = None, max_val: int | None = None) -> int:
        while True:
            try:
                valor = int(input(f"  {mensaje}: "))
                if min_val is not None and valor < min_val:
                    print(f"  Debe ingresar un valor mayor o igual a {min_val}.")
                    continue
                if max_val is not None and valor > max_val:
                    print(f"  Debe ingresar un valor menor o igual a {max_val}.")
                    continue
                return valor
            except ValueError:
                print("  Debe ingresar un número entero válido.")

    @staticmethod
    def input_float(mensaje: str) -> float:
        while True:
            try:
                return float(input(f"  {mensaje}: "))
            except ValueError:
                print("  Debe ingresar un número válido.")

    @staticmethod
    def input_si_no(mensaje: str) -> bool:
        while True:
            respuesta = input(f"  {mensaje} (s/n): ").strip().lower()
            if respuesta in ("s", "si", "sí"):
                return True
            if respuesta in ("n", "no"):
                return False
            print("  Responda 's' o 'n'.")

    @staticmethod
    def input_str(mensaje: str) -> str:
        return input(f"  {mensaje}: ").strip()
