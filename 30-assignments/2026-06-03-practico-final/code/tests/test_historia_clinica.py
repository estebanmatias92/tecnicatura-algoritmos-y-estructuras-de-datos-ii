import pytest

from consultorio import PacienteInactivoError


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


class TestHistoriaClinica:
    def test_registrar_entrada(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.registrar_entrada_historia(
            paciente_id=p.id,
            odontologo_id=1,
            diagnostico="Caries",
            procedimiento="Empaste",
            observaciones="Sin complicaciones",
        )
        historial = c.listar_historia_clinica(p.id)
        assert len(historial) == 1
        assert historial[0].diagnostico == "Caries"
        assert historial[0].odontologo_nombre is not None

    def test_historial_vacio(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        assert c.listar_historia_clinica(p.id) == []

    def test_rechaza_paciente_inactivo(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.eliminar_paciente(p.id)
        with pytest.raises(PacienteInactivoError):
            c.registrar_entrada_historia(
                paciente_id=p.id,
                odontologo_id=1,
                diagnostico="X",
                procedimiento="Y",
            )

    def test_multiples_entradas(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.registrar_entrada_historia(p.id, 1, "Caries", "Empaste")
        c.registrar_entrada_historia(p.id, 1, "Limpieza", "Profilaxis")
        assert len(c.listar_historia_clinica(p.id)) == 2

    def test_historial_orden_cronologico(self, consultorio_con_paciente):
        c, p = consultorio_con_paciente
        c.registrar_entrada_historia(p.id, 1, "A", "Proc A")
        c.registrar_entrada_historia(p.id, 1, "B", "Proc B")
        historial = c.listar_historia_clinica(p.id)
        assert len(historial) == 2
