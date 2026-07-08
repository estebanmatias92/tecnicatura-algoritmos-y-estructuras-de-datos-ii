from src.core.registry import Registry
from src.presentacion.formato import Formato


@Registry.registrar(seccion=10, numero=1, titulo="Demostrar unittest con setUp/tearDown")
def ej_10_1():
    Formato.encabezado("Testing con unittest")
    print("""
  Los tests estan definidos en:
    src/ejercicios/seccion_10_testing/tests.py

  Para ejecutarlos:
    $ python -m unittest src.ejercicios.seccion_10_testing.tests -v

  Esto ejecutara:
    - test_1: verifica calcula_media([10, 10, 10]) == 10
    - test_2: verifica calcula_media([5, 3, 4]) == 4
    - setUp / tearDown se ejecutan antes/despues de cada test.
""")
