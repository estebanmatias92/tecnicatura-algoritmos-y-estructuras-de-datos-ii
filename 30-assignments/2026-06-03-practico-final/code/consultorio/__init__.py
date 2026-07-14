from consultorio._entidades import HistoriaClinica, Odontologo, Paciente, Turno
from consultorio._excepciones import (
    ConsultorioError,
    DNIExistenteError,
    OdontologoInexistenteError,
    PacienteInactivoError,
    TelefonoFaltanteError,
    TransicionInvalidaError,
    TurnoSuperpuestoError,
)
from consultorio.consultorio import Consultorio

__all__ = [
    "Consultorio",
    "Paciente",
    "Odontologo",
    "Turno",
    "HistoriaClinica",
    "ConsultorioError",
    "DNIExistenteError",
    "OdontologoInexistenteError",
    "TelefonoFaltanteError",
    "TurnoSuperpuestoError",
    "TransicionInvalidaError",
    "PacienteInactivoError",
]
