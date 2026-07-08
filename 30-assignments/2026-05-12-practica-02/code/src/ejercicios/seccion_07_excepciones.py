from src.core.registry import Registry
from src.presentacion.formato import Formato


def dividir(a: float, b: float) -> float | None:
    try:
        return a / b
    except ZeroDivisionError:
        Formato.error(f"ZeroDivisionError: No se puede dividir {a} entre cero.")
        return None


def mas_10(x):
    try:
        return x + 10
    except TypeError as e:
        Formato.error(f"TypeError: {e}")
        return None


@Registry.registrar(seccion=7, numero=1, titulo="División entre cero (ZeroDivisionError)")
def ej_7_1():
    Formato.encabezado("ZeroDivisionError")
    resultado = dividir(27, 3)
    Formato.resultado(f"27 / 3 = {resultado}")
    resultado = dividir(27, 0)
    Formato.resultado(f"27 / 0 = {resultado}")


@Registry.registrar(seccion=7, numero=2, titulo="TypeError con mas_10()")
def ej_7_2():
    Formato.encabezado("TypeError")
    resultado = mas_10(5)
    Formato.resultado(f"mas_10(5) = {resultado}")
    resultado = mas_10("cinco")
    Formato.resultado(f'mas_10("cinco") = {resultado}')


@Registry.registrar(seccion=7, numero=3, titulo="IndexError y KeyError")
def ej_7_3():
    Formato.encabezado("IndexError")
    lista = [10, 20, 30]
    try:
        Formato.resultado(f"lista[5] = {lista[5]}")
    except IndexError as e:
        Formato.error(f"IndexError: {e}")

    Formato.encabezado("KeyError")
    diccionario = {"a": 1, "b": 2, "c": 3}
    try:
        Formato.resultado(f"diccionario['z'] = {diccionario['z']}")
    except KeyError as e:
        Formato.error(f"KeyError: La clave '{e}' no existe en el diccionario.")
