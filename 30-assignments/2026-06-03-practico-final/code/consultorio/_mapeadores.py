import sqlite3

from consultorio._entidades import (
    HistoriaClinica,
    Odontologo,
    Paciente,
    Turno,
)


def fila_a_paciente(fila: sqlite3.Row) -> Paciente:
    return Paciente(
        id=fila["id"],
        dni=fila["dni"],
        nombre=fila["nombre"],
        apellido=fila["apellido"],
        telefono=fila["telefono"] or "",
        email=fila["email"] or "",
        direccion=fila["direccion"] or "",
        obra_social=fila["obra_social"] or "",
        activo=bool(fila["activo"]),
    )


def fila_a_odontologo(fila: sqlite3.Row) -> Odontologo:
    return Odontologo(
        id=fila["id"],
        matricula=fila["matricula"],
        nombre=fila["nombre"],
        apellido=fila["apellido"],
        especialidad=fila["especialidad"],
        telefono=fila["telefono"] or "",
        email=fila["email"] or "",
    )


def fila_a_turno(fila: sqlite3.Row) -> Turno:
    return Turno(
        id=fila["id"],
        paciente_id=fila["paciente_id"],
        odontologo_id=fila["odontologo_id"],
        fecha=fila["fecha"],
        hora=fila["hora"],
        motivo=fila["motivo"] or "",
        estado=fila["estado"],
        paciente_nombre=fila["paciente_nombre"],
        odontologo_nombre=fila["odontologo_nombre"],
    )


def fila_a_historia(fila: sqlite3.Row) -> HistoriaClinica:
    return HistoriaClinica(
        id=fila["id"],
        paciente_id=fila["paciente_id"],
        odontologo_id=fila["odontologo_id"],
        fecha=fila["fecha"],
        diagnostico=fila["diagnostico"],
        procedimiento=fila["procedimiento"],
        observaciones=fila["observaciones"] or "",
        odontologo_nombre=fila["odontologo_nombre"],
    )
