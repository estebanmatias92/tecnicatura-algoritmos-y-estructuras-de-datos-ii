import pytest

from consultorio import DNIExistenteError, Paciente


class TestRegistrarPaciente:
    def test_registrar_paciente_valido(self, consultorio):
        p = consultorio.registrar_paciente(
            {
                "dni": "12345678",
                "nombre": "Juan",
                "apellido": "Perez",
                "telefono": "555-1234",
                "email": "juan@test.com",
            }
        )
        assert isinstance(p, Paciente)
        assert p.id > 0
        assert p.dni == "12345678"
        assert p.nombre == "Juan"
        assert p.activo is True

    def test_dni_duplicado_rechazado(self, consultorio):
        consultorio.registrar_paciente({"dni": "123", "nombre": "A", "apellido": "B"})
        with pytest.raises(DNIExistenteError):
            consultorio.registrar_paciente(
                {"dni": "123", "nombre": "C", "apellido": "D"}
            )

    def test_dni_duplicado_permite_mismo_paciente_modificar(self, consultorio):
        p = consultorio.registrar_paciente(
            {"dni": "123", "nombre": "A", "apellido": "B"}
        )
        consultorio.modificar_paciente(
            p.id, {"dni": "123", "nombre": "A", "apellido": "C"}
        )
        result = consultorio.buscar_paciente_por_dni("123")
        assert result.apellido == "C"


class TestBuscarPaciente:
    def test_buscar_por_dni_existente(self, consultorio):
        consultorio.registrar_paciente({"dni": "111", "nombre": "A", "apellido": "B"})
        p = consultorio.buscar_paciente_por_dni("111")
        assert p is not None
        assert p.dni == "111"

    def test_buscar_por_dni_inexistente(self, consultorio):
        p = consultorio.buscar_paciente_por_dni("999")
        assert p is None

    def test_buscar_paciente_eliminado_no_aparece(self, consultorio):
        p = consultorio.registrar_paciente(
            {"dni": "111", "nombre": "A", "apellido": "B"}
        )
        consultorio.eliminar_paciente(p.id)
        result = consultorio.buscar_paciente_por_dni("111")
        assert result is None


class TestListarPacientes:
    def test_listar_vacio(self, consultorio):
        assert consultorio.listar_pacientes() == []

    def test_listar_varios(self, consultorio):
        consultorio.registrar_paciente({"dni": "1", "nombre": "B", "apellido": "Z"})
        consultorio.registrar_paciente({"dni": "2", "nombre": "A", "apellido": "A"})
        pacientes = consultorio.listar_pacientes()
        assert len(pacientes) == 2

    def test_listar_no_incluye_eliminados(self, consultorio):
        p = consultorio.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B"})
        consultorio.registrar_paciente({"dni": "2", "nombre": "C", "apellido": "D"})
        consultorio.eliminar_paciente(p.id)
        assert len(consultorio.listar_pacientes()) == 1


class TestModificarPaciente:
    def test_modificar_campos(self, consultorio):
        p = consultorio.registrar_paciente(
            {"dni": "123", "nombre": "A", "apellido": "B"}
        )
        consultorio.modificar_paciente(
            p.id,
            {
                "dni": "123",
                "nombre": "Nuevo",
                "apellido": "Nombre",
                "telefono": "999",
            },
        )
        result = consultorio.buscar_paciente_por_dni("123")
        assert result.nombre == "Nuevo"
        assert result.telefono == "999"

    def test_modificar_dni_duplicado_rechazado(self, consultorio):
        consultorio.registrar_paciente({"dni": "111", "nombre": "A", "apellido": "B"})
        p2 = consultorio.registrar_paciente(
            {"dni": "222", "nombre": "C", "apellido": "D"}
        )
        with pytest.raises(DNIExistenteError):
            consultorio.modificar_paciente(
                p2.id, {"dni": "111", "nombre": "C", "apellido": "D"}
            )


class TestEliminarPaciente:
    def test_eliminar_logico(self, consultorio):
        p = consultorio.registrar_paciente(
            {"dni": "123", "nombre": "A", "apellido": "B"}
        )
        consultorio.eliminar_paciente(p.id)
        assert consultorio.buscar_paciente_por_dni("123") is None

    def test_eliminar_no_borra_fisicamente(self, consultorio):
        p = consultorio.registrar_paciente(
            {"dni": "123", "nombre": "A", "apellido": "B"}
        )
        consultorio.eliminar_paciente(p.id)
        # Se puede re-registrar con mismo DNI? NO si es UNIQUE, pero la baja lógica mantiene el registro
        with pytest.raises(DNIExistenteError):
            consultorio.registrar_paciente(
                {"dni": "123", "nombre": "C", "apellido": "D"}
            )
