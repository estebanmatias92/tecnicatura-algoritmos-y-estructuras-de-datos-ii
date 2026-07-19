import pytest

from consultorio import (
    TelefonoFaltanteError,
    TurnoSuperpuestoError,
    TransicionInvalidaError,
    PacienteInactivoError,
)


@pytest.fixture
def consultorio_con_paciente(consultorio):
    p = consultorio.registrar_paciente(
        {
            "dni": "123",
            "nombre": "Juan",
            "apellido": "Perez",
            "telefono": "555-1234",
        }
    )
    return consultorio, p


class TestAsignarTurno:
    def test_asignar_turno_valido(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        t = c.asignar_turno(
            paciente_id=p.id,
            odontologo_id=1,
            fecha="2026-07-15",
            hora="10:00",
            motivo="Consulta",
        )
        assert t.id > 0
        assert t.estado == "Pendiente"
        assert t.paciente_nombre == "Juan Perez"

    def test_rechaza_sin_telefono(self, consultorio):
        p = consultorio.registrar_paciente(
            {
                "dni": "999",
                "nombre": "Sin",
                "apellido": "Telefono",
            }
        )
        with pytest.raises(TelefonoFaltanteError):
            consultorio.asignar_turno(
                paciente_id=p.id,
                odontologo_id=1,
                fecha="2026-07-15",
                hora="10:00",
                motivo="Test",
            )

    def test_rechaza_superposicion(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Primero")
        with pytest.raises(TurnoSuperpuestoError):
            c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Segundo")

    def test_permite_misma_fecha_distinta_hora(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Primero")
        t = c.asignar_turno(p.id, 1, "2026-07-15", "11:00", "Segundo")
        assert t.id > 0

    def test_rechaza_paciente_inactivo(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.eliminar_paciente(p.id)
        with pytest.raises(PacienteInactivoError):
            c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Test")


class TestEstadoTurno:
    def test_confirmar_turno(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
        t2 = c.confirmar_turno(t.id)
        assert t2.estado == "Confirmado"

    def test_cancelar_turno(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
        t2 = c.cancelar_turno(t.id)
        assert t2.estado == "Cancelado"

    def test_cancelar_desde_confirmado(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
        c.confirmar_turno(t.id)
        t2 = c.cancelar_turno(t.id)
        assert t2.estado == "Cancelado"

    def test_no_confirma_cancelado(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
        c.cancelar_turno(t.id)
        with pytest.raises(TransicionInvalidaError):
            c.confirmar_turno(t.id)

    def test_no_cancela_cancelado(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
        c.cancelar_turno(t.id)
        with pytest.raises(TransicionInvalidaError):
            c.cancelar_turno(t.id)


class TestListarTurnos:
    def test_listar_vacio(self, consultorio):
        assert consultorio.listar_turnos() == []

    def test_listar_incluye_datos_paciente(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
        turnos = c.listar_turnos()
        assert len(turnos) == 1
        assert turnos[0].paciente_nombre == "Juan Perez"
        assert turnos[0].odontologo_nombre is not None
