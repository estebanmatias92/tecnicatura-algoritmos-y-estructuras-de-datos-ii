from src.core.registry import Registry
from src.presentacion.formato import Formato


@Registry.registrar(seccion=1, numero=5, titulo="Lanzar consola interactiva")
def ej_1_5():
    Formato.encabezado("Consola Interactiva (REPL)")
    print("""
  Para lanzar la consola interactiva de Python:
    $ python
    $ python3 (en Linux/Mac)

  Una vez dentro, escribe expresiones y se evaluan inmediatamente.
  Para salir: exit() o Ctrl+D (Linux/Mac) o Ctrl+Z (Windows).
""")


@Registry.registrar(seccion=1, numero=6, titulo='Imprimir "Hola Mundo"')
def ej_1_6():
    Formato.encabezado("Hola Mundo")
    print("""  En la consola interactiva:
    >>> print("Hola Mundo")
    Hola Mundo
""")
    print("  Desde un script: python -c 'print(\"Hola Mundo\")'")


@Registry.registrar(seccion=1, numero=7, titulo="Lanzar IDLE y repetir punto 6")
def ej_1_7():
    Formato.encabezado("IDLE")
    print("""
  Para lanzar IDLE:
    $ idle
    $ idle3 (en Linux/Mac)

  IDLE es el IDE incluido con Python. Abre una ventana con consola
  interactiva donde puedes escribir print("Hola Mundo") y ver el resultado.
""")


@Registry.registrar(seccion=1, numero=8, titulo="Añadir repositorio PIP (get-pip.py)")
def ej_1_8():
    Formato.encabezado("Instalar PIP")
    print("""
  Para instalar PIP desde cero:
    $ curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
    $ python get-pip.py

  En Linux con gestor de paquetes:
    $ sudo apt install python3-pip        (Debian/Ubuntu)
    $ sudo dnf install python3-pip        (Fedora)
""")


@Registry.registrar(seccion=1, numero=9, titulo="Actualizar PIP")
def ej_1_9():
    Formato.encabezado("Actualizar PIP")
    print("""
  Actualizacion multiplataforma:
    $ pip install --upgrade pip setuptools

  En Linux (Debian/Ubuntu):
    $ sudo apt update && sudo apt upgrade python3-pip
""")


@Registry.registrar(seccion=1, numero=10, titulo="Probar PIP (list, show, update)")
def ej_1_10():
    Formato.encabezado("Comandos PIP")
    print("""
  $ pip list                # muestra paquetes instalados
  $ pip show <paquete>      # informacion detallada de un paquete
  $ pip install --upgrade <paquete>  # actualizar un paquete
""")
