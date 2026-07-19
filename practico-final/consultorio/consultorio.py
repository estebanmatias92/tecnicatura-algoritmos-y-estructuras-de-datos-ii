from __future__ import annotations

import sqlite3

from consultorio._entidades import (
    HistoriaClinica,
    Odontologo,
    Paciente,
    Turno,
)
from consultorio._estado_turno import EstadoTurno
from consultorio._excepciones import ConsultorioError
from consultorio._repositorios import (
    _HistoriaRepo,
    _OdontologoRepo,
    _PacienteRepo,
    _TurnoRepo,
)
from consultorio._validacion import (
    validar_disponibilidad,
    validar_dni_unico,
    validar_odontologo_existe,
    validar_paciente_existe_y_activo,
    validar_telefono_para_turno,
)

_DDL = """
CREATE TABLE IF NOT EXISTS odontologo (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    matricula   TEXT    NOT NULL UNIQUE,
    nombre      TEXT    NOT NULL,
    apellido    TEXT    NOT NULL,
    especialidad TEXT   NOT NULL DEFAULT 'General',
    telefono    TEXT,
    email       TEXT
);

CREATE TABLE IF NOT EXISTS paciente (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    dni         TEXT    NOT NULL UNIQUE,
    nombre      TEXT    NOT NULL,
    apellido    TEXT    NOT NULL,
    telefono    TEXT,
    email       TEXT,
    direccion   TEXT,
    obra_social TEXT,
    activo      INTEGER NOT NULL DEFAULT 1
);

CREATE TABLE IF NOT EXISTS turno (
    id              INTEGER PRIMARY KEY AUTOINCREMENT,
    paciente_id     INTEGER NOT NULL,
    odontologo_id   INTEGER NOT NULL,
    fecha           TEXT    NOT NULL,
    hora            TEXT    NOT NULL,
    motivo          TEXT,
    estado          TEXT    NOT NULL DEFAULT 'Pendiente'
                        CHECK (estado IN ('Pendiente', 'Confirmado', 'Cancelado')),
    FOREIGN KEY (paciente_id)   REFERENCES paciente(id)   ON DELETE RESTRICT,
    FOREIGN KEY (odontologo_id) REFERENCES odontologo(id) ON DELETE RESTRICT
);

CREATE TABLE IF NOT EXISTS historia_clinica (
    id              INTEGER PRIMARY KEY AUTOINCREMENT,
    paciente_id     INTEGER NOT NULL,
    odontologo_id   INTEGER NOT NULL,
    fecha           TEXT    NOT NULL DEFAULT (date('now')),
    diagnostico     TEXT    NOT NULL,
    procedimiento   TEXT    NOT NULL,
    observaciones   TEXT,
    FOREIGN KEY (paciente_id)   REFERENCES paciente(id)   ON DELETE RESTRICT,
    FOREIGN KEY (odontologo_id) REFERENCES odontologo(id) ON DELETE RESTRICT
);

CREATE INDEX IF NOT EXISTS idx_paciente_dni ON paciente(dni);
CREATE INDEX IF NOT EXISTS idx_paciente_activo ON paciente(activo);
CREATE INDEX IF NOT EXISTS idx_turno_fecha ON turno(fecha);
CREATE INDEX IF NOT EXISTS idx_turno_odontologo_fecha ON turno(odontologo_id, fecha);
CREATE INDEX IF NOT EXISTS idx_historia_paciente ON historia_clinica(paciente_id);
"""

_ODONTOLOGOS_INICIALES = [
    ("1234", "Gómez", "Carlos", "Odontología General"),
    ("5678", "Ruiz", "María", "Periodoncia"),
    ("9012", "López", "Fernando", "Endodoncia"),
]


class Consultorio:
    def __init__(self, conexion: sqlite3.Connection):
        self._conn = conexion
        self._conn.row_factory = sqlite3.Row
        self._conn.execute("PRAGMA foreign_keys = ON")

        self._pacientes = _PacienteRepo(self._conn)
        self._odontologos = _OdontologoRepo(self._conn)
        self._turnos = _TurnoRepo(self._conn)
        self._historia = _HistoriaRepo(self._conn)

    def inicializar(self):
        for stmt in _DDL.strip().split(";"):
            stmt = stmt.strip()
            if stmt:
                self._conn.execute(stmt + ";")
        self._conn.commit()
        self._sembrar_odontologos()

    def _sembrar_odontologos(self):
        cuenta = self._conn.execute("SELECT COUNT(*) FROM odontologo").fetchone()[0]
        if cuenta == 0:
            for matricula, apellido, nombre, especialidad in _ODONTOLOGOS_INICIALES:
                self._conn.execute(
                    "INSERT INTO odontologo (matricula, nombre, apellido, especialidad) VALUES (?, ?, ?, ?)",
                    (matricula, nombre, apellido, especialidad),
                )
            self._conn.commit()

    # ── Pacientes ──────────────────────────────────────────────

    def registrar_paciente(self, datos: dict) -> Paciente:
        validar_dni_unico(self._conn, datos["dni"])
        self._pacientes.crear(
            dni=datos["dni"],
            nombre=datos["nombre"],
            apellido=datos["apellido"],
            telefono=datos.get("telefono", ""),
            email=datos.get("email", ""),
            direccion=datos.get("direccion", ""),
            obra_social=datos.get("obra_social", ""),
        )
        self._conn.commit()
        p = self._pacientes.buscar_por_dni(datos["dni"])
        assert p is not None
        return p

    def buscar_paciente_por_dni(self, dni: str) -> Paciente | None:
        return self._pacientes.buscar_por_dni(dni)

    def listar_pacientes(self) -> list[Paciente]:
        return self._pacientes.listar()

    def modificar_paciente(self, id: int, datos: dict) -> Paciente:
        validar_dni_unico(self._conn, datos["dni"], excluir_id=id)
        self._pacientes.actualizar(
            id=id,
            dni=datos["dni"],
            nombre=datos["nombre"],
            apellido=datos["apellido"],
            telefono=datos.get("telefono", ""),
            email=datos.get("email", ""),
            direccion=datos.get("direccion", ""),
            obra_social=datos.get("obra_social", ""),
        )
        self._conn.commit()
        p = self._pacientes.buscar_por_dni(datos["dni"])
        assert p is not None
        return p

    def eliminar_paciente(self, id: int) -> None:
        self._pacientes.eliminar_logico(id)
        self._conn.commit()

    # ── Odontólogos ────────────────────────────────────────────

    def listar_odontologos(self) -> list[Odontologo]:
        return self._odontologos.listar()

    # ── Turnos ─────────────────────────────────────────────────

    def asignar_turno(
        self, paciente_id: int, odontologo_id: int, fecha: str, hora: str, motivo: str
    ) -> Turno:
        validar_paciente_existe_y_activo(self._conn, paciente_id)
        validar_telefono_para_turno(self._conn, paciente_id)
        validar_odontologo_existe(self._conn, odontologo_id)
        validar_disponibilidad(self._conn, odontologo_id, fecha, hora)

        id = self._turnos.crear(
            paciente_id=paciente_id,
            odontologo_id=odontologo_id,
            fecha=fecha,
            hora=hora,
            motivo=motivo,
            estado=EstadoTurno.PENDIENTE.value,
        )
        self._conn.commit()
        turnos = self._turnos.listar()
        return next(t for t in turnos if t.id == id)

    def listar_turnos(self) -> list[Turno]:
        return self._turnos.listar()

    def confirmar_turno(self, id: int) -> Turno:
        turno = self._turnos.listar()
        turno = next((t for t in turno if t.id == id), None)
        if not turno:
            raise ConsultorioError("Turno no encontrado")

        actual = EstadoTurno(turno.estado)
        destino = actual.transicionar_a(EstadoTurno.CONFIRMADO)

        self._turnos.cambiar_estado(id, destino.value)
        self._conn.commit()

        turnos = self._turnos.listar()
        return next(t for t in turnos if t.id == id)

    def cancelar_turno(self, id: int) -> Turno:
        turno = self._turnos.listar()
        turno = next((t for t in turno if t.id == id), None)
        if not turno:
            raise ConsultorioError("Turno no encontrado")

        actual = EstadoTurno(turno.estado)
        destino = actual.transicionar_a(EstadoTurno.CANCELADO)

        self._turnos.cambiar_estado(id, destino.value)
        self._conn.commit()

        turnos = self._turnos.listar()
        return next(t for t in turnos if t.id == id)

    # ── Historia Clínica ───────────────────────────────────────

    def registrar_entrada_historia(
        self,
        paciente_id: int,
        odontologo_id: int,
        diagnostico: str,
        procedimiento: str,
        observaciones: str = "",
    ) -> None:
        validar_paciente_existe_y_activo(self._conn, paciente_id)
        validar_odontologo_existe(self._conn, odontologo_id)
        self._historia.crear(
            paciente_id=paciente_id,
            odontologo_id=odontologo_id,
            diagnostico=diagnostico,
            procedimiento=procedimiento,
            observaciones=observaciones,
        )
        self._conn.commit()

    def listar_historia_clinica(self, paciente_id: int) -> list[HistoriaClinica]:
        return self._historia.listar_por_paciente(paciente_id)
