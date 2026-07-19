from dataclasses import dataclass


@dataclass
class Paciente:
    id: int = 0
    dni: str = ""
    nombre: str = ""
    apellido: str = ""
    telefono: str = ""
    email: str = ""
    direccion: str = ""
    obra_social: str = ""
    activo: bool = True


@dataclass
class Odontologo:
    id: int = 0
    matricula: str = ""
    nombre: str = ""
    apellido: str = ""
    especialidad: str = ""
    telefono: str = ""
    email: str = ""


@dataclass
class Turno:
    id: int = 0
    paciente_id: int = 0
    odontologo_id: int = 0
    fecha: str = ""
    hora: str = ""
    motivo: str = ""
    estado: str = "Pendiente"
    paciente_nombre: str = ""
    odontologo_nombre: str = ""


@dataclass
class HistoriaClinica:
    id: int = 0
    paciente_id: int = 0
    odontologo_id: int = 0
    fecha: str = ""
    diagnostico: str = ""
    procedimiento: str = ""
    observaciones: str = ""
    odontologo_nombre: str = ""
