# Diagrama de Contexto — Saca Muela

System Boundary del sistema de gestión odontológica.

```mermaid
---
config:
  theme: 'base'
---
graph TD
    subgraph "Sistema Saca Muela"
        SM[Sistema de Gestión<br>Odontológica]
    end

    A[Recepcionista] -->|Registra, busca,<br>modifica pacientes| SM
    A -->|Asigna y gestiona<br>turnos| SM
    A -->|Consulta historia<br>clínica| SM

    B[Odontólogo] -->|Consulta agenda<br>de turnos| SM
    B -->|Registra historia<br>clínica| SM
    B -->|Visualiza datos<br>del paciente| SM

    DB[(Base de Datos<br>SQLite3)] <-->|Persistencia local| SM

    SM -->|Listados y<br>reportes| A
    SM -->|Historial clínico<br>completo| B

    style A fill:#e1f5fe
    style B fill:#e1f5fe
    style DB fill:#fff3e0
    style SM fill:#e8f5e9
```

## Actores del Sistema

| Actor | Descripción | Responsabilidades |
| :--- | :--- | :--- |
| **Recepcionista** | Personal administrativo del consultorio | CRUD de pacientes, gestión de turnos, consulta de historia clínica |
| **Odontólogo** | Profesional de salud dental | Consulta de agenda, registro de historia clínica, visualización de datos del paciente |

## Fuera del Sistema (explícitamente excluido)

- Facturación / cobros
- Gestión de stock de insumos
- Módulo de estadísticas avanzadas
- Acceso remoto / web
- Gestión de usuarios con roles diferenciados (se asigna un único perfil por estación de trabajo)
