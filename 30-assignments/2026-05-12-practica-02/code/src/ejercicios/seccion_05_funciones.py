from src.core.registry import Registry
from src.presentacion.formato import Formato
from src.utils.entrada import Entrada


def dibujar_rectangulo(ancho: int, altura: int, caracter: str):
    for _ in range(altura):
        print(f"  {caracter * ancho}")


def es_bisiesto(anio: int) -> bool:
    if anio % 400 == 0:
        return True
    if anio % 100 == 0:
        return False
    if anio % 4 == 0:
        return True
    return False


@Registry.registrar(seccion=5, numero=1, titulo="Dibujar rectángulo")
def ej_5_1():
    Formato.encabezado("Rectángulo")
    ancho = Entrada.input_int("Anchura del rectángulo", min_val=1)
    altura = Entrada.input_int("Altura del rectángulo", min_val=1)
    caracter = Entrada.input_str("Carácter a utilizar")
    dibujar_rectangulo(ancho, altura, caracter)


@Registry.registrar(seccion=5, numero=2, titulo="Año bisiesto")
def ej_5_2():
    Formato.encabezado("Año bisiesto")
    anio = Entrada.input_int("Ingrese un año")
    if es_bisiesto(anio):
        Formato.resultado(f"{anio} es bisiesto.")
    else:
        Formato.resultado(f"{anio} no es bisiesto.")


@Registry.registrar(seccion=5, numero=3, titulo="Crear lista de palabras")
def ej_5_3():
    Formato.encabezado("Lista de palabras")
    n = Entrada.input_int("¿Cuántas palabras desea ingresar?", min_val=0)
    palabras: list[str] = []
    for i in range(n):
        palabra = Entrada.input_str(f"Palabra {i + 1}")
        palabras.append(palabra)
    Formato.resultado("Lista creada:")
    Formato.lista(palabras)
