# Modelo Conceptual — Saca Muela

Diagrama de clases de dominio con entidades, atributos y relaciones del negocio odontológico.

```mermaid
classDiagram
    class Paciente {
        +int id
        +string dni
        +string nombre
        +string apellido
        +string telefono
        +string email
        +string direccion
        +string obraSocial
        +bool activo
        +registrar()
        +modificar()
    }

    class Turno {
        +int id
        +date fecha
        +time hora
        +string motivo
        +string estado
        +asignar()
        +cancelar()
        +confirmar()
    }

    class Odontologo {
        +int id
        +string matricula
        +string nombre
        +string apellido
        +string especialidad
        +string telefono
        +string email
    }

    class HistoriaClinica {
        +int id
        +date fecha
        +string diagnostico
        +string procedimiento
        +string observaciones
        +registrar()
    }

    class Consultorio {
        +string nombre
        +string direccion
        +string telefono
    }

    Paciente "1" --> "*" Turno : solicita
    Odontologo "1" --> "*" Turno : atiende
    Paciente "1" --> "*" HistoriaClinica : posee
    Odontologo "1" --> "*" HistoriaClinica : registra
    Consultorio "1" --> "*" Turno : alberga
```

## Entidades

| Entidad | Descripción |
| :--- | :--- |
| **Paciente** | Persona que recibe atención odontológica. Atributos demográficos y de contacto. |
| **Turno** | Cita programada que vincula paciente, odontólogo, fecha, hora y consultorio. |
| **Odontólogo** | Profesional que brinda la atención. Identificado por matrícula. |
| **HistoriaClínica** | Registro cronológico de diagnósticos, procedimientos y observaciones por paciente. |
| **Consultorio** | Establecimiento físico donde ocurren las atenciones. |

## Reglas de Relación

- Un `Paciente` puede tener **muchos** `Turno`s; un `Turno` pertenece a **un** `Paciente`.
- Un `Odontólogo` puede atender **muchos** `Turno`s; un `Turno` es atendido por **un** `Odontólogo`.
- Un `Paciente` puede tener **muchas** entradas de `HistoriaClinica`; cada entrada pertenece a **un** `Paciente`.
- Un `Odontólogo` puede registrar **muchas** entradas de `HistoriaClinica`; cada entrada es registrada por **un** `Odontólogo`.
