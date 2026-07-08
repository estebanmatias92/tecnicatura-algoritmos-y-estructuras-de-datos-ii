# Saca Muela — Sistema de Gestión Odontológica

Aplicación de escritorio para digitalizar la gestión de pacientes de un consultorio odontológico.

## Stack Tecnológico

- Python 3.x
- SQLite3
- ttk (Tkinter themed widgets)

## Arquitectura

Separación estricta en dos capas:

```text
code/
├── consultorio.py              # Capa de datos/negocio
├── formulario_odontologico.py   # Capa de interfaz gráfica
└── docs/                        # Documentación del proyecto
```

## Documentación

- [Glosario de Dominio](glosario-de-dominio.md) — términos clave del negocio odontológico
- [Registro de Necesidades](registro-necesidades.md) — necesidades crudas identificadas en la elicitación
- [Modelo Conceptual](modelo-conceptual.md) — entidades, atributos y relaciones del dominio
- [Diagrama de Contexto](diagrama-de-contexto.md) — actores, flujos y System Boundary
- [SRS — Especificación de Requisitos de Software](04-projects/prj-tecnicatura-superior-sistemas/year/02/algoritmos-y-estructuras-de-datos-ii/30-assignments/2026-06-03-practico-final/code/docs/software-requirements-specification.md) — documento principal del Hito 0
- [Checklist de Validación](checklist-validacion.md) — verificación de calidad del SRS

## Milestones

| Hito   | Descripción                      | Estado       |
| :----- | :------------------------------- | :----------- |
| Hito 0 | Especificación de Requerimientos | ✅ Completado |
| Hito 1 | Diseño del Sistema (UML)         | ⬜ Pendiente  |
| Hito 2 | Codificación e Implementación    | ⬜ Pendiente  |

## Autor

Lapenta, Carlos Matías — Algoritmos y Estructuras de Datos II
