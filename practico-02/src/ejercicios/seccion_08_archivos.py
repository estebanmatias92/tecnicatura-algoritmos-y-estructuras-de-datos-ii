import os

from src.core.registry import Registry
from src.presentacion.formato import Formato


ARCHIVO = "ej_08_archivo.txt"


@Registry.registrar(seccion=8, numero=1, titulo="Abrir fichero y añadir frase")
def ej_8_1():
    Formato.encabezado("Escritura con open/close")
    archivo = open(ARCHIVO, "a+")
    archivo.write("Estoy aprendiendo Python\n")
    archivo.seek(0)
    contenido = archivo.read()
    archivo.close()
    Formato.resultado(f"Contenido del archivo: {contenido}")


@Registry.registrar(seccion=8, numero=2, titulo="Mostrar estado, modo, nombre, codificación")
def ej_8_2():
    Formato.encabezado("Metadatos del archivo")
    archivo = open(ARCHIVO, "r")
    Formato.resultado(f"Estado (closed): {archivo.closed}")
    Formato.resultado(f"Modo: {archivo.mode}")
    Formato.resultado(f"Nombre: {archivo.name}")
    Formato.resultado(f"Codificación: {archivo.encoding}")
    archivo.close()


@Registry.registrar(seccion=8, numero=3, titulo="Ejercicios 1 y 2 con estructura with")
def ej_8_3():
    Formato.encabezado("Uso de with (context manager)")
    with open(ARCHIVO, "a+") as archivo:
        archivo.write("Estoy aprendiendo Python (con with)\n")
        archivo.seek(0)
        contenido = archivo.read()
        Formato.resultado(f"Contenido: {contenido}")
        Formato.resultado(f"Estado (closed): {archivo.closed}")
        Formato.resultado(f"Modo: {archivo.mode}")
        Formato.resultado(f"Nombre: {archivo.name}")
        Formato.resultado(f"Codificación: {archivo.encoding}")

    if os.path.exists(ARCHIVO):
        os.remove(ARCHIVO)
        Formato.resultado(f"Archivo '{ARCHIVO}' eliminado.")
