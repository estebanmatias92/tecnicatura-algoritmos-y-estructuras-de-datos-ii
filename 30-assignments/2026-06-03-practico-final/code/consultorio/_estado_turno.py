from __future__ import annotations

from enum import Enum

from consultorio._excepciones import TransicionInvalidaError


class EstadoTurno(Enum):
    PENDIENTE = "Pendiente"
    CONFIRMADO = "Confirmado"
    CANCELADO = "Cancelado"

    def transiciones_validas(self) -> set[EstadoTurno]:
        match self:
            case EstadoTurno.PENDIENTE:
                return {EstadoTurno.CONFIRMADO, EstadoTurno.CANCELADO}
            case EstadoTurno.CONFIRMADO:
                return {EstadoTurno.CANCELADO}
            case EstadoTurno.CANCELADO:
                return set()

    def transicionar_a(self, destino: EstadoTurno) -> EstadoTurno:
        if destino not in self.transiciones_validas():
            raise TransicionInvalidaError(self.value, destino.value)
        return destino
