-- Saca Muela — Esquema de Base de Datos
-- SQLite3 DDL v1.0

PRAGMA journal_mode = WAL;
PRAGMA foreign_keys = ON;

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
