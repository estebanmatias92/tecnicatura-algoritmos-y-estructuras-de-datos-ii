from src.core.registry import Registry
from src.core.menu_engine import MenuEngine
from src.presentacion.formato import Formato


SECCIONES = {
    1: "Instalación y Entorno",
    2: "Aspectos del Lenguaje (parte práctica)",
    3: "Colecciones",
    4: "Bucles",
    5: "Funciones",
    6: "Programación Funcional",
    7: "Excepciones",
    8: "Archivos",
    9: "Módulos y Paquetes",
    10: "Testing",
}


class Menus:

    @staticmethod
    def menu_principal() -> int:
        opciones = [(k, v) for k, v in SECCIONES.items()]
        opciones.append((0, "Salir"))
        return MenuEngine.ejecutar_menu(opciones, "PRÁCTICA 02 - PYTHON ESTRUCTURADO")

    @staticmethod
    def menu_ejercicios(seccion: int) -> int:
        nombre_seccion = SECCIONES.get(seccion, f"Sección {seccion}")
        ejercicios = Registry.obtener_por_seccion(seccion)
        if not ejercicios:
            Formato.error(f"No hay ejercicios registrados en la sección {seccion}.")
            return 0
        opciones = [(ej["numero"], f"{ej['numero']}. {ej['titulo']}") for ej in ejercicios]
        opciones.append((-1, "Volver al menú principal"))
        opciones.append((0, "Salir"))
        return MenuEngine.ejecutar_menu(opciones, f"SECCIÓN {seccion} — {nombre_seccion}")
