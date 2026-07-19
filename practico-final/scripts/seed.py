import sqlite3
import sys
from datetime import date, timedelta

from consultorio import Consultorio, ConsultorioError


_PACIENTES = [
    {"dni": "11222333", "nombre": "Laura", "apellido": "Giménez", "telefono": "341-5550101", "email": "laura.gimenez@mail.com", "direccion": "San Martín 1234", "obra_social": "OSDE"},
    {"dni": "22444555", "nombre": "Martín", "apellido": "Ríos", "telefono": "341-5550202", "email": "martin.rios@mail.com", "direccion": "Belgrano 567", "obra_social": "Swiss Medical"},
    {"dni": "33666777", "nombre": "Sofía", "apellido": "Méndez", "telefono": "341-5550303", "email": "sofia.mendez@mail.com", "direccion": "Sarmiento 890", "obra_social": ""},
    {"dni": "44888999", "nombre": "Diego", "apellido": "Álvarez", "telefono": "341-5550404", "email": "diego.alvarez@mail.com", "direccion": "Urquiza 345", "obra_social": "GALENO"},
    {"dni": "55000111", "nombre": "Carolina", "apellido": "Lencinas", "telefono": "341-5550505", "email": "carolina.lencinas@mail.com", "direccion": "Mitre 678", "obra_social": ""},
    {"dni": "66222333", "nombre": "Roberto", "apellido": "Santos", "telefono": "", "email": "roberto.santos@mail.com", "direccion": "Buenos Aires 901", "obra_social": "OSDE"},
]

_TURNOS = [
    {"dni": "11222333", "odontologo_idx": 0, "dias_desde_hoy": 1, "hora": "09:00", "motivo": "Control de rutina"},
    {"dni": "22444555", "odontologo_idx": 1, "dias_desde_hoy": 1, "hora": "10:30", "motivo": "Dolor de muela"},
    {"dni": "33666777", "odontologo_idx": 0, "dias_desde_hoy": 3, "hora": "14:00", "motivo": "Limpieza dental"},
    {"dni": "44888999", "odontologo_idx": 2, "dias_desde_hoy": 5, "hora": "11:00", "motivo": "Consulta inicial"},
    {"dni": "55000111", "odontologo_idx": 1, "dias_desde_hoy": -2, "hora": "15:30", "motivo": "Revisión de conducto"},
    {"dni": "66222333", "odontologo_idx": 0, "dias_desde_hoy": -5, "hora": "08:30", "motivo": "Urgencia"},
]

_ENTRADAS_HISTORIA = [
    {"dni": "55000111", "odontologo_idx": 1, "dias_desde_hoy": -10, "diagnostico": "Caries profunda en molar inferior izquierdo", "procedimiento": "Empaste de composite", "observaciones": "Paciente con buena tolerancia. Se cita para control en 6 meses."},
    {"dni": "55000111", "odontologo_idx": 1, "dias_desde_hoy": -5, "diagnostico": "Control post-operatorio sin novedades", "procedimiento": "Revisión", "observaciones": ""},
    {"dni": "22444555", "odontologo_idx": 2, "dias_desde_hoy": -20, "diagnostico": "Pulpitis irreversible", "procedimiento": "Endodoncia parcial", "observaciones": "Pendiente segunda sesión."},
    {"dni": "11222333", "odontologo_idx": 0, "dias_desde_hoy": -15, "diagnostico": "Gingivitis generalizada", "procedimiento": "Profilaxis y tartrectomía", "observaciones": "Se recomienda mejorar técnica de cepillado."},
]

_ESTADOS_TURNO = [
    "Confirmado", "Pendiente", "Pendiente", "Pendiente", "Confirmado", "Cancelado",
]


def seed():
    ruta_db = sys.argv[1] if len(sys.argv) > 1 else "saca_muela.db"
    conn = sqlite3.connect(ruta_db)
    consultorio = Consultorio(conn)
    consultorio.inicializar()

    pacientes = {}
    for p in _PACIENTES:
        try:
            paciente = consultorio.registrar_paciente(p)
            pacientes[p["dni"]] = paciente
            print(f"  + Paciente: {paciente.nombre} {paciente.apellido}")
        except ConsultorioError as e:
            print(f"  ! Paciente {p['dni']}: {e}")

    odontologos = consultorio.listar_odontologos()
    hoy = date.today()

    for i, t in enumerate(_TURNOS):
        try:
            fecha = hoy + timedelta(days=t["dias_desde_hoy"])
            turno = consultorio.asignar_turno(
                paciente_id=pacientes[t["dni"]].id,
                odontologo_id=odontologos[t["odontologo_idx"]].id,
                fecha=fecha.isoformat(),
                hora=t["hora"],
                motivo=t["motivo"],
            )
            estado = _ESTADOS_TURNO[i]
            if estado == "Confirmado":
                consultorio.confirmar_turno(turno.id)
            elif estado == "Cancelado":
                consultorio.cancelar_turno(turno.id)
            print(f"  + Turno {i+1}: {t['motivo']} → {estado}")
        except ConsultorioError as e:
            print(f"  ! Turno {i+1}: {e}")

    for e in _ENTRADAS_HISTORIA:
        try:
            fecha = hoy + timedelta(days=e["dias_desde_hoy"])
            consultorio.registrar_entrada_historia(
                paciente_id=pacientes[e["dni"]].id,
                odontologo_id=odontologos[e["odontologo_idx"]].id,
                diagnostico=e["diagnostico"],
                procedimiento=e["procedimiento"],
                observaciones=e["observaciones"],
            )
            print(f"  + Historia: {pacientes[e['dni']].nombre} {pacientes[e['dni']].apellido} — {e['diagnostico'][:40]}...")
        except ConsultorioError as err:
            print(f"  ! Historia: {err}")

    conn.close()
    print(f"\nSeed completado en: {ruta_db}")


if __name__ == "__main__":
    seed()
