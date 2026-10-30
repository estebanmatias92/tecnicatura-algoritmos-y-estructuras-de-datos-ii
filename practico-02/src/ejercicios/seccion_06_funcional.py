from functools import reduce

from src.core.registry import Registry
from src.presentacion.formato import Formato


@Registry.registrar(seccion=6, numero=1, titulo="Cuadrado de todos los elementos (map)")
def ej_6_1():
    Formato.encabezado("Cuadrado con map")
    numeros = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    cuadrados = list(map(lambda x: x ** 2, numeros))
    Formato.resultado(f"Original: {numeros}")
    Formato.resultado(f"Cuadrados: {cuadrados}")


@Registry.registrar(seccion=6, numero=2, titulo="Elementos > 5 en tupla (filter)")
def ej_6_2():
    Formato.encabezado("Mayores a 5 con filter")
    tupla = (1, 5, 8, 3, 9, 2, 10, 4, 7, 6)
    mayores = list(filter(lambda x: x > 5, tupla))
    Formato.resultado(f"Tupla original: {tupla}")
    Formato.resultado(f"Mayores a 5: {mayores}")
    Formato.resultado(f"Cantidad: {len(mayores)}")


@Registry.registrar(seccion=6, numero=3, titulo="Elementos > 5 en tupla (reduce)")
def ej_6_3():
    Formato.encabezado("Mayores a 5 con reduce")
    tupla = (1, 5, 8, 3, 9, 2, 10, 4, 7, 6)
    cantidad = reduce(lambda acc, x: acc + (1 if x > 5 else 0), tupla, 0)
    Formato.resultado(f"Tupla original: {tupla}")
    Formato.resultado(f"Cantidad de elementos > 5: {cantidad}")
