from src.core.registry import Registry
from src.presentacion.formato import Formato
from src.utils.entrada import Entrada
import sys
import os


@Registry.registrar(seccion=9, numero=1, titulo="Hacer un paquete simple")
def ej_9_1():
    Formato.encabezado("Paquete simple")
    print("""
  Estructura del paquete 'mi_paquete/':
    src/ejercicios/seccion_09_modulos/mi_paquete/
    ├── __init__.py    # inicializador del paquete
    └── operaciones.py # modulo con funciones

  El paquete se importa con:
    from src.ejercicios.seccion_09_modulos.mi_paquete import operaciones
    operaciones.saludar()
""")
    from src.ejercicios.seccion_09_modulos.mi_paquete import operaciones
    operaciones.saludar()
    resultado = operaciones.sumar(5, 3)
    Formato.resultado(f"5 + 3 = {resultado}")


@Registry.registrar(seccion=9, numero=2, titulo="Crear un directorio de aplicaciones")
def ej_9_2():
    Formato.encabezado("Directorio de aplicaciones")
    print("""
  Los scripts de aplicacion pueden ubicarse en un directorio 'scripts/'
  e importar el paquete desde la raiz del proyecto.

  Estructura:
    src/ejercicios/seccion_09_modulos/scripts/
    └── app_ejemplo.py

  Ejecutar con:
    $ python -m src.ejercicios.seccion_09_modulos.scripts.app_ejemplo
""")


@Registry.registrar(seccion=9, numero=3, titulo="Scripts de nivel superior")
def ej_9_3():
    Formato.encabezado("Scripts de nivel superior y sys.path")
    Formato.resultado(f"sys.path actual:")
    for ruta in sys.path:
        print(f"    {ruta}")
    Formato.separador()
    Formato.resultado("""
  Para ejecutar un script de nivel superior que importe modulos del
  proyecto, se debe agregar la raiz del proyecto a sys.path o ejecutar
  como modulo con -m.

  Ejemplo:
    $ cd code/
    $ python -m src.ejercicios.seccion_09_modulos.scripts.app_ejemplo
""")
