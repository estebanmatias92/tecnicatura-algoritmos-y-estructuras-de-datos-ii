class TestOdontologos:
    def test_listar_odontologos_iniciales(self, consultorio):
        odontologos = consultorio.listar_odontologos()
        assert len(odontologos) == 3
        assert odontologos[0].nombre is not None
        assert odontologos[0].especialidad is not None

    def test_odontologos_tienen_id(self, consultorio):
        for o in consultorio.listar_odontologos():
            assert o.id > 0
            assert o.matricula != ""
