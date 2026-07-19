class ConsultorioError(Exception): ...


class DNIExistenteError(ConsultorioError):
    def __init__(self, dni: str):
        super().__init__(f"Ya existe un paciente con DNI {dni}")


class TelefonoFaltanteError(ConsultorioError):
    def __init__(self):
        super().__init__(
            "El paciente debe tener un teléfono registrado para asignar un turno"
        )


class TurnoSuperpuestoError(ConsultorioError):
    def __init__(self, odontologo: str, fecha: str, hora: str):
        super().__init__(f"{odontologo} ya tiene un turno el {fecha} a las {hora}")


class TransicionInvalidaError(ConsultorioError):
    def __init__(self, actual: str, destino: str):
        super().__init__(f"No se puede cambiar el estado de {actual} a {destino}")
        self.actual = actual
        self.destino = destino


class PacienteInactivoError(ConsultorioError):
    def __init__(self):
        super().__init__("El paciente no existe o está inactivo")


class OdontologoInexistenteError(ConsultorioError):
    def __init__(self):
        super().__init__("El odontólogo no existe")
