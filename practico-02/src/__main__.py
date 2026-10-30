from src.core.registry import Registry
from src.core.menu_engine import MenuEngine
from src.presentacion.menus import Menus
from src.presentacion.formato import Formato
from src.utils.entrada import Entrada


def main():
    Registry.importar_modulos_ejercicios()

    while True:
        seccion = Menus.menu_principal()
        if seccion == 0:
            Formato.encabezado("¡Hasta luego!")
            break

        while True:
            opcion = Menus.menu_ejercicios(seccion)
            if opcion == 0:
                Formato.encabezado("¡Hasta luego!")
                return
            if opcion == -1:
                break

            ejercicios = Registry.obtener_por_seccion(seccion)
            ej_dict = {ej["numero"]: ej for ej in ejercicios}
            if opcion in ej_dict:
                print()
                MenuEngine.separador()
                ej_dict[opcion]["func"]()
                MenuEngine.separador()
                MenuEngine.pausa()


if __name__ == "__main__":
    main()
