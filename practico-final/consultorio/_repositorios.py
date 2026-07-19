from __future__ import annotations

import sqlite3

from consultorio._entidades import (
    HistoriaClinica,
    Odontologo,
    Paciente,
    Turno,
)
from consultorio._mapeadores import (
    fila_a_historia,
    fila_a_odontologo,
    fila_a_paciente,
    fila_a_turno,
)


class _PacienteRepo:
    def __init__(self, conn: sqlite3.Connection):
        self._conn = conn

    def crear(
        self,
        dni: str,
        nombre: str,
        apellido: str,
        telefono: str,
        email: str,
        direccion: str,
        obra_social: str,
    ) -> int:
        cursor = self._conn.execute(
            """INSERT INTO paciente (dni, nombre, apellido, telefono, email, direccion, obra_social)
               VALUES (?, ?, ?, ?, ?, ?, ?)""",
            (dni, nombre, apellido, telefono, email, direccion, obra_social),
        )
        return cursor.lastrowid

    def buscar_por_dni(self, dni: str) -> Paciente | None:
        fila = self._conn.execute(
            "SELECT * FROM paciente WHERE dni = ? AND activo = 1", (dni,)
        ).fetchone()
        return fila_a_paciente(fila) if fila else None

    def listar(self) -> list[Paciente]:
        filas = self._conn.execute(
            "SELECT * FROM paciente WHERE activo = 1 ORDER BY apellido, nombre"
        ).fetchall()
        return [fila_a_paciente(f) for f in filas]

    def actualizar(
        self,
        id: int,
        dni: str,
        nombre: str,
        apellido: str,
        telefono: str,
        email: str,
        direccion: str,
        obra_social: str,
    ) -> bool:
        self._conn.execute(
            """UPDATE paciente SET dni=?, nombre=?, apellido=?, telefono=?, email=?, direccion=?, obra_social=?
               WHERE id = ?""",
            (dni, nombre, apellido, telefono, email, direccion, obra_social, id),
        )
        return self._conn.total_changes > 0

    def eliminar_logico(self, id: int) -> bool:
        self._conn.execute("UPDATE paciente SET activo = 0 WHERE id = ?", (id,))
        return self._conn.total_changes > 0


class _OdontologoRepo:
    def __init__(self, conn: sqlite3.Connection):
        self._conn = conn

    def listar(self) -> list[Odontologo]:
        filas = self._conn.execute(
            "SELECT * FROM odontologo ORDER BY apellido, nombre"
        ).fetchall()
        return [fila_a_odontologo(f) for f in filas]


class _TurnoRepo:
    def __init__(self, conn: sqlite3.Connection):
        self._conn = conn

    def crear(
        self,
        paciente_id: int,
        odontologo_id: int,
        fecha: str,
        hora: str,
        motivo: str,
        estado: str,
    ) -> int:
        cursor = self._conn.execute(
            """INSERT INTO turno (paciente_id, odontologo_id, fecha, hora, motivo, estado)
               VALUES (?, ?, ?, ?, ?, ?)""",
            (paciente_id, odontologo_id, fecha, hora, motivo, estado),
        )
        return cursor.lastrowid

    def listar(self) -> list[Turno]:
        filas = self._conn.execute(
            """SELECT t.*, p.nombre AS paciente_nombre, p.apellido AS paciente_apellido,
                      o.nombre AS odontologo_nombre, o.apellido AS odontologo_apellido
               FROM turno t
               JOIN paciente p ON t.paciente_id = p.id
               JOIN odontologo o ON t.odontologo_id = o.id
               ORDER BY t.fecha DESC, t.hora""",
        ).fetchall()
        resultado = []
        for f in filas:
            turno = fila_a_turno(f)
            turno.paciente_nombre = f"{f['paciente_nombre']} {f['paciente_apellido']}"
            turno.odontologo_nombre = (
                f"{f['odontologo_nombre']} {f['odontologo_apellido']}"
            )
            resultado.append(turno)
        return resultado

    def cambiar_estado(self, id: int, nuevo_estado: str) -> bool:
        self._conn.execute(
            "UPDATE turno SET estado = ? WHERE id = ?", (nuevo_estado, id)
        )
        return self._conn.total_changes > 0


class _HistoriaRepo:
    def __init__(self, conn: sqlite3.Connection):
        self._conn = conn

    def crear(
        self,
        paciente_id: int,
        odontologo_id: int,
        diagnostico: str,
        procedimiento: str,
        observaciones: str,
    ) -> int:
        cursor = self._conn.execute(
            """INSERT INTO historia_clinica (paciente_id, odontologo_id, diagnostico, procedimiento, observaciones)
               VALUES (?, ?, ?, ?, ?)""",
            (paciente_id, odontologo_id, diagnostico, procedimiento, observaciones),
        )
        return cursor.lastrowid

    def listar_por_paciente(self, paciente_id: int) -> list[HistoriaClinica]:
        filas = self._conn.execute(
            """SELECT hc.*, o.nombre AS odontologo_nombre, o.apellido AS odontologo_apellido
               FROM historia_clinica hc
               JOIN odontologo o ON hc.odontologo_id = o.id
               WHERE hc.paciente_id = ?
               ORDER BY hc.fecha DESC""",
            (paciente_id,),
        ).fetchall()
        resultado = []
        for f in filas:
            hc = fila_a_historia(f)
            hc.odontologo_nombre = (
                f"{f['odontologo_nombre']} {f['odontologo_apellido']}"
            )
            resultado.append(hc)
        return resultado
