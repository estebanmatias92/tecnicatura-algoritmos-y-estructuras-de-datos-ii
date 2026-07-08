from src.core.registry import Registry
from src.presentacion.formato import Formato
from src.utils.entrada import Entrada


@Registry.registrar(seccion=3, numero=1, titulo="Lista del 1 al 100")
def ej_3_1():
    Formato.encabezado("Lista del 1 al 100")
    numeros = list(range(1, 101))
    print(f"  Lista creada con {len(numeros)} elementos.")
    Formato.lista(numeros)


@Registry.registrar(seccion=3, numero=2, titulo="Tupla con meses del año")
def ej_3_2():
    Formato.encabezado("Meses del año")
    meses = (
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre",
    )
    num = Entrada.input_int("Ingrese un número (1-12)", min_val=1, max_val=12)
    Formato.resultado(f"Mes {num}: {meses[num - 1]}")


@Registry.registrar(seccion=3, numero=3, titulo="Tabla de multiplicar")
def ej_3_3():
    Formato.encabezado("Tabla de multiplicar")
    num = Entrada.input_int("Ingrese un número")
    tabla = [num * i for i in range(1, 11)]
    Formato.resultado(f"Tabla del {num}:")
    Formato.lista(tabla)


@Registry.registrar(seccion=3, numero=4, titulo="Agenda telefónica (diccionario)")
def ej_3_4():
    Formato.encabezado("Agenda Telefónica")
    agenda: dict[str, str] = {}
    while True:
        nombre = Entrada.input_str("Nombre del contacto (o Enter para salir)")
        if not nombre:
            break
        if nombre in agenda:
            Formato.error("Ese nombre ya existe en la agenda.")
            continue
        telefono = Entrada.input_str("Teléfono")
        agenda[nombre] = telefono
        Formato.resultado(f"Contacto '{nombre}' agregado.")
    Formato.separador()
    if agenda:
        Formato.encabezado("Contactos registrados")
        for nom, tel in agenda.items():
            print(f"  {nom}: {tel}")
    else:
        Formato.resultado("No se registraron contactos.")
