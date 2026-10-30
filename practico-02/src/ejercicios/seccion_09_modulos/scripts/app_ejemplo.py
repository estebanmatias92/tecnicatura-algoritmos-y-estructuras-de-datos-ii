"""
Script de ejemplo que importa el paquete mi_paquete.
Ejecutar desde la raiz del proyecto:
  $ python -m src.ejercicios.seccion_09_modulos.scripts.app_ejemplo
"""
from src.ejercicios.seccion_09_modulos.mi_paquete import operaciones


def main():
    print("=== Script de aplicación (nivel superior) ===")
    operaciones.saludar()
    resultado = operaciones.sumar(10, 20)
    print(f"10 + 20 = {resultado}")


if __name__ == "__main__":
    main()
