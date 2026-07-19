from src.core.registry import Registry
from src.presentacion.formato import Formato
from src.utils.entrada import Entrada


@Registry.registrar(seccion=4, numero=1, titulo="Pares e impares entre dos números")
def ej_4_1():
    Formato.encabezado("Pares e impares")
    a = Entrada.input_int("Ingrese el primer número")
    b = Entrada.input_int("Ingrese el segundo número")
    inicio, fin = (a, b) if a <= b else (b, a)
    pares = [str(n) for n in range(inicio, fin + 1) if n % 2 == 0]
    impares = [str(n) for n in range(inicio, fin + 1) if n % 2 != 0]
    Formato.resultado(f"Pares: {', '.join(pares)}")
    Formato.resultado(f"Impares: {', '.join(impares)}")


@Registry.registrar(seccion=4, numero=2, titulo="Pedir número positivo hasta que sea válido")
def ej_4_2():
    Formato.encabezado("Número positivo")
    while True:
        num = Entrada.input_int("Ingrese un número positivo")
        if num > 0:
            Formato.resultado(f"Número válido: {num}")
            break
        Formato.error("El número debe ser positivo.")


@Registry.registrar(seccion=4, numero=3, titulo="Segundo número mayor que el primero")
def ej_4_3():
    Formato.encabezado("Validar orden")
    a = Entrada.input_int("Ingrese el primer número")
    while True:
        b = Entrada.input_int("Ingrese el segundo número (debe ser mayor que el primero)")
        if b > a:
            Formato.resultado(f"Primero: {a}, Segundo: {b}")
            break
        Formato.error(f"El segundo número debe ser mayor que {a}.")


@Registry.registrar(seccion=4, numero=4, titulo="Números consecutivos entre dos enteros")
def ej_4_4():
    Formato.encabezado("Números consecutivos")
    a = Entrada.input_int("Ingrese el primer número")
    b = Entrada.input_int("Ingrese el segundo número")
    inicio, fin = (a, b) if a <= b else (b, a)
    consecutivos = list(range(inicio, fin + 1))
    Formato.resultado(f"Números entre {inicio} y {fin}:")
    Formato.lista(consecutivos)
