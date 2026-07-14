import sqlite3

from consultorio._excepciones import (
    DNIExistenteError,
    OdontologoInexistenteError,
    PacienteInactivoError,
    TelefonoFaltanteError,
    TurnoSuperpuestoError,
)


def validar_dni_unico(
    conn: sqlite3.Connection, dni: str, excluir_id: int | None = None
) -> None:
    fila = conn.execute("SELECT id FROM paciente WHERE dni = ?", (dni,)).fetchone()
    if fila and (excluir_id is None or fila["id"] != excluir_id):
        raise DNIExistenteError(dni)


def validar_paciente_existe_y_activo(
    conn: sqlite3.Connection, paciente_id: int
) -> None:
    fila = conn.execute(
        "SELECT id FROM paciente WHERE id = ? AND activo = 1", (paciente_id,)
    ).fetchone()
    if not fila:
        raise PacienteInactivoError()


def validar_telefono_para_turno(conn: sqlite3.Connection, paciente_id: int) -> None:
    fila = conn.execute(
        "SELECT telefono FROM paciente WHERE id = ?", (paciente_id,)
    ).fetchone()
    if not fila or not fila["telefono"]:
        raise TelefonoFaltanteError()


def validar_odontologo_existe(
    conn: sqlite3.Connection, odontologo_id: int
) -> tuple[str, str]:
    fila = conn.execute(
        "SELECT nombre, apellido FROM odontologo WHERE id = ?", (odontologo_id,)
    ).fetchone()
    if not fila:
        raise OdontologoInexistenteError()
    return fila["nombre"], fila["apellido"]


def validar_disponibilidad(
    conn: sqlite3.Connection, odontologo_id: int, fecha: str, hora: str
) -> None:
    fila = conn.execute(
        """SELECT id FROM turno
           WHERE odontologo_id = ? AND fecha = ? AND hora = ? AND estado != 'Cancelado'""",
        (odontologo_id, fecha, hora),
    ).fetchone()
    if fila is not None:
        odontologo = conn.execute(
            "SELECT nombre, apellido FROM odontologo WHERE id = ?", (odontologo_id,)
        ).fetchone()
        nombre = f"{odontologo['nombre']} {odontologo['apellido']}"
        raise TurnoSuperpuestoError(nombre, fecha, hora)
