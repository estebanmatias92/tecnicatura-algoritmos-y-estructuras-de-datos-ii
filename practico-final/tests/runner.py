"""
Test runner mínimo para entornos sin pytest.

Uso:
    PYTHONPATH=/ruta/al/code python3 runner.py
"""
import sqlite3
import sys
import traceback

from consultorio import (
    Consultorio,
    DNIExistenteError,
    PacienteInactivoError,
    TelefonoFaltanteError,
    TransicionInvalidaError,
    TurnoSuperpuestoError,
)

passed = 0
failed = 0


def test(name, fn):
    global passed, failed
    conn = sqlite3.connect(":memory:")
    c = Consultorio(conn)
    c.inicializar()
    try:
        fn(c)
        passed += 1
        print(f"  OK  {name}")
    except AssertionError as e:
        failed += 1
        print(f"  FAIL {name}: {e}")
    except Exception as e:
        failed += 1
        print(f"  FAIL {name}: {type(e).__name__}: {e}")
        traceback.print_exc()
    finally:
        conn.close()


def _paciente(c):
    return c.registrar_paciente({
        "dni": "123", "nombre": "Pac", "apellido": "Dos", "telefono": "555",
    })


# ── Pacientes ──

def test_registrar(c):
    p = c.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B", "telefono": "555"})
    assert p.id > 0 and p.dni == "1"


def test_dni_duplicado(c):
    c.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B"})
    try:
        c.registrar_paciente({"dni": "1", "nombre": "C", "apellido": "D"})
        assert False
    except DNIExistenteError:
        pass


def test_buscar_existente(c):
    c.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B"})
    assert c.buscar_paciente_por_dni("1") is not None


def test_buscar_inexistente(c):
    assert c.buscar_paciente_por_dni("999") is None


def test_listar_vacio(c):
    assert c.listar_pacientes() == []


def test_listar_varios(c):
    c.registrar_paciente({"dni": "1", "nombre": "B", "apellido": "Z"})
    c.registrar_paciente({"dni": "2", "nombre": "A", "apellido": "A"})
    assert len(c.listar_pacientes()) == 2


def test_modificar(c):
    p = c.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B"})
    c.modificar_paciente(p.id, {"dni": "1", "nombre": "A", "apellido": "C"})
    assert c.buscar_paciente_por_dni("1").apellido == "C"


def test_eliminar_logico(c):
    p = c.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B"})
    c.eliminar_paciente(p.id)
    assert c.buscar_paciente_por_dni("1") is None


def test_eliminado_no_aparece(c):
    p = c.registrar_paciente({"dni": "1", "nombre": "A", "apellido": "B"})
    c.registrar_paciente({"dni": "2", "nombre": "C", "apellido": "D"})
    c.eliminar_paciente(p.id)
    assert len(c.listar_pacientes()) == 1


# ── Turnos ──

def test_asignar_turno(c):
    p = _paciente(c)
    t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "Consulta")
    assert t.estado == "Pendiente"
    assert t.paciente_nombre == "Pac Dos"


def test_sin_telefono(c):
    p = c.registrar_paciente({"dni": "999", "nombre": "Sin", "apellido": "Tel"})
    try:
        c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "")
        assert False
    except TelefonoFaltanteError:
        pass


def test_superposicion(c):
    p = _paciente(c)
    c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "P")
    try:
        c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "S")
        assert False
    except TurnoSuperpuestoError:
        pass


def test_distinta_hora(c):
    p = _paciente(c)
    c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "P")
    t = c.asignar_turno(p.id, 1, "2026-07-15", "11:00", "S")
    assert t.id > 0


def test_confirmar(c):
    p = _paciente(c)
    t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "X")
    assert c.confirmar_turno(t.id).estado == "Confirmado"


def test_cancelar(c):
    p = _paciente(c)
    t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "X")
    assert c.cancelar_turno(t.id).estado == "Cancelado"


def test_cancelar_desde_confirmado(c):
    p = _paciente(c)
    t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "X")
    c.confirmar_turno(t.id)
    assert c.cancelar_turno(t.id).estado == "Cancelado"


def test_no_confirma_cancelado(c):
    p = _paciente(c)
    t = c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "X")
    c.cancelar_turno(t.id)
    try:
        c.confirmar_turno(t.id)
        assert False
    except TransicionInvalidaError:
        pass


def test_paciente_inactivo_turno(c):
    p = _paciente(c)
    c.eliminar_paciente(p.id)
    try:
        c.asignar_turno(p.id, 1, "2026-07-15", "10:00", "X")
        assert False
    except PacienteInactivoError:
        pass


# ── Historia Clínica ──

def test_registrar_entrada(c):
    p = _paciente(c)
    c.registrar_entrada_historia(p.id, 1, "Caries", "Empaste", "OK")
    h = c.listar_historia_clinica(p.id)
    assert len(h) == 1
    assert h[0].diagnostico == "Caries"


def test_historial_vacio(c):
    p = _paciente(c)
    assert c.listar_historia_clinica(p.id) == []


def test_paciente_inactivo_historia(c):
    p = _paciente(c)
    c.eliminar_paciente(p.id)
    try:
        c.registrar_entrada_historia(p.id, 1, "X", "Y")
        assert False
    except PacienteInactivoError:
        pass


# ── Odontólogos ──

def test_odontologos_iniciales(c):
    ods = c.listar_odontologos()
    assert len(ods) == 3
    assert all(o.id > 0 and o.nombre for o in ods)


if __name__ == "__main__":
    tests = [
        ("registrar paciente valido", test_registrar),
        ("DNI duplicado rechazado", test_dni_duplicado),
        ("buscar paciente existente", test_buscar_existente),
        ("buscar paciente inexistente", test_buscar_inexistente),
        ("listar pacientes vacio", test_listar_vacio),
        ("listar pacientes varios", test_listar_varios),
        ("modificar paciente", test_modificar),
        ("eliminar logico", test_eliminar_logico),
        ("eliminado no aparece en lista", test_eliminado_no_aparece),
        ("asignar turno valido", test_asignar_turno),
        ("rechaza turno sin telefono", test_sin_telefono),
        ("rechaza superposicion", test_superposicion),
        ("permite distinta hora", test_distinta_hora),
        ("confirmar turno", test_confirmar),
        ("cancelar turno", test_cancelar),
        ("cancelar desde confirmado", test_cancelar_desde_confirmado),
        ("no confirma cancelado", test_no_confirma_cancelado),
        ("rechaza turno con paciente inactivo", test_paciente_inactivo_turno),
        ("registrar entrada historia", test_registrar_entrada),
        ("historial vacio", test_historial_vacio),
        ("rechaza historia con paciente inactivo", test_paciente_inactivo_historia),
        ("odontologos iniciales", test_odontologos_iniciales),
    ]

    print(f"Ejecutando {len(tests)} tests...\n")
    for name, fn in tests:
        test(name, fn)

    print(f"\n{'=' * 40}")
    print(f"Resultados: {passed} pasaron, {failed} fallaron")
    sys.exit(1 if failed else 0)
