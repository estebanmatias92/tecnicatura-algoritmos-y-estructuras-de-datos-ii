from src.core.registry import Registry
from src.presentacion.formato import Formato
from src.utils.entrada import Entrada


@Registry.registrar(seccion=2, numero=1, titulo="Crear entorno virtual nuevo")
def ej_2_1():
    Formato.encabezado("Crear entorno virtual")
    print("""
  $ python -m venv mi_entorno

  Esto crea un directorio 'mi_entorno/' con:
    - bin/       (Scripts en Windows) — python, pip
    - lib/       — sitio de paquetes
    - pyvenv.cfg — configuracion del entorno
""")


@Registry.registrar(seccion=2, numero=2, titulo="Activar entorno virtual")
def ej_2_2():
    Formato.encabezado("Activar entorno virtual")
    print(r"""
  Linux/Mac:
    $ source mi_entorno/bin/activate

  Windows:
    $ mi_entorno\Scripts\activate

  Al activarse, el prompt cambia a:
    (mi_entorno) $
""")


@Registry.registrar(seccion=2, numero=3, titulo="Instalar Flask en el entorno")
def ej_2_3():
    Formato.encabezado("Instalar Flask")
    print("""
  Con el entorno activado:
    (mi_entorno) $ pip install flask

  Verificar:
    (mi_entorno) $ pip list
    (mi_entorno) $ python -c "import flask; print(flask.__version__)"
""")


@Registry.registrar(seccion=2, numero=4, titulo="Desactivar entorno virtual")
def ej_2_4():
    Formato.encabezado("Desactivar entorno virtual")
    print("""
  $ deactivate

  El prompt vuelve a la normalidad y los comandos python/pip
  usan la instalacion global del sistema.
""")


@Registry.registrar(seccion=2, numero=5, titulo="Borrar entorno virtual")
def ej_2_5():
    Formato.encabezado("Borrar entorno virtual")
    print("""
  Simplemente eliminar el directorio:
    $ rm -rf mi_entorno/          (Linux/Mac)
    $ rmdir /s mi_entorno         (Windows)

  No deja residuos en el sistema.
""")
