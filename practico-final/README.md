# Saca Muela — Sistema de Gestión Odontológica

Aplicación de escritorio para digitalizar la gestión de pacientes de un consultorio odontológico.

## Stack Tecnológico

- Python 3.14+
- SQLite3 3.53
- ttk (Tkinter 8.6 themed widgets)
- Black + Ruff (formato y linting)

## Entorno de Desarrollo

Dos alternativas para preparar el entorno:

### Opción A: Nix flakes + direnv (reproducible)

```bash
cd code/
direnv allow      # o: nix develop
```

Aporta: Python con soporte Tkinter, SQLite3, PlantUML, Black y Ruff (todo versionado).

### Opción B: Tradicional (virtualenv + pip)

Requisitos previos del sistema operativo:

- **Debian/Ubuntu:** `sudo apt install python3 python3-tk python3-venv`
- **Arch Linux:** `sudo pacman -S python tk`
- **Fedora:** `sudo dnf install python3 python3-tkinter`

Puesta en marcha:

```bash
cd code/
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements-dev.txt
```

Aporta: Python con soporte Tkinter, Black, Ruff y pytest. SQLite3 viene incluido en la stdlib de Python.

## Arquitectura

Separación estricta en dos capas. La conexión a la base de datos se inyecta desde `main.py` (Dependency Injection):

```text
code/
├── flake.nix                              # Dev shell (Nix)
├── flake.lock                             # Pin de dependencias
├── .envrc                                 # Activación automática
├── .gitignore
├── Makefile                               # CLI targets para el dev (run, test, seed, etc.)
├── main.py                                # Entry point: conexión → Consultorio → GUI
├── scripts/
│   └── seed.py                            # Poblado de datos de prueba en entorno dev
├── consultorio/                           # Capa de datos/negocio (package)
│   ├── __init__.py                        # Re-exporta interfaz pública
│   ├── consultorio.py                     # Facade — orquesta validación, repos, estado
│   ├── _entidades.py                      # Dataclasses: Paciente, Odontologo, Turno, ...
│   ├── _excepciones.py                    # Jerarquía de errores de dominio
│   ├── _estado_turno.py                   # Máquina de estados (Enum + transiciones)
│   ├── _validacion.py                     # Reglas de negocio (DNI único, disponibilidad, ...)
│   ├── _repositorios.py                   # SQL CRUD interno (uno por entidad)
│   └── _mapeadores.py                     # Row → objeto (sqlite3.Row → dataclass)
├── formulario_odontologico/               # Capa de interfaz gráfica (package)
│   ├── __init__.py                        # Re-exporta FormularioOdontologico
│   ├── formulario.py                      # Shell: Tk root + Notebook
│   ├── _pestania_pacientes.py             # Tab Pacientes (CRUD + búsqueda)
│   ├── _pestania_turnos.py                # Tab Turnos (asignar, confirmar, cancelar)
│   ├── _pestania_historia.py              # Tab Historia Clínica (ver + registrar)
│   └── _dialogos.py                       # Todos los modales (Toplevel)
├── tests/                                 # Tests con SQLite  :memory:
│   ├── conftest.py                        # Fixture compartido
│   ├── test_pacientes.py                  # 9 tests
│   ├── test_turnos.py                     # 9 tests (incluye máquina de estados)
│   ├── test_historia_clinica.py           # 5 tests
│   └── test_odontologos.py                # 2 tests
└── docs/                                  # Documentación del proyecto
    ├── glosario-de-dominio.md
    ├── registro-necesidades.md
    ├── modelo-conceptual.md
    ├── software-requirements-specification.md
    ├── checklist-validacion.md
    └── diagrams/
        ├── diagrama-de-contexto.md
        ├── diagrama-casos-de-uso.puml
        ├── diagrama-casos-de-uso.svg
        ├── diagrama-clases-disenio.puml      # Diseño — Clases
        ├── diagrama-clases-disenio.svg
        ├── diagrama-estados-turno.puml       # Diseño — Estados de Turno
        ├── diagrama-estados-turno.svg
        ├── esquema-ddl.sql                   # Diseño — DDL
        ├── secuencias/
        │   └── cu-*.puml / cu-*.svg          # Diseño — Secuencias (CU-01 .. CU-07)
        └── wireframes/
            └── html/index.html               # Wireframes HTML interactivos
```

## Documentación

### Hito 0 — Especificación

- [Glosario de Dominio](docs/glosario-de-dominio.md) — términos clave del negocio odontológico
- [Registro de Necesidades](docs/registro-necesidades.md) — necesidades crudas identificadas en la elicitación
- [Modelo Conceptual](docs/modelo-conceptual.md) — entidades, atributos y relaciones del dominio
- [Diagrama de Contexto](docs/diagrams/diagrama-de-contexto.md) — actores, flujos y System Boundary
- [SRS — Especificación de Requisitos de Software](docs/software-requirements-specification.md) — documento principal del Hito 0
- [Checklist de Validación](docs/checklist-validacion.md) — verificación de calidad del SRS

### Hito 1 — Diseño (UML + DDL + Wireframes)

- [Diagrama de Clases de Diseño](docs/diagrams/diagrama-clases-disenio.puml) — clases de la capa de datos y de interfaz, con métodos y relaciones
- [Diagrama de Estados del Turno](docs/diagrams/diagrama-estados-turno.puml) — lifecycle: Pendiente → Confirmado / Cancelado
- [Esquema DDL](docs/diagrams/esquema-ddl.sql) — sentencias CREATE TABLE con constraints, índices y foreign keys
- Diagramas de Secuencia — un PUML por caso de uso (CU-01 a CU-07):
  - [CU-01](docs/diagrams/secuencias/cu-01.puml) — Registrar Paciente
  - [CU-02](docs/diagrams/secuencias/cu-02.puml) — Buscar Paciente por DNI
  - [CU-03](docs/diagrams/secuencias/cu-03.puml) — Listar Pacientes
  - [CU-04](docs/diagrams/secuencias/cu-04.puml) — Modificar Paciente
  - [CU-05](docs/diagrams/secuencias/cu-05.puml) — Eliminar Paciente
  - [CU-06](docs/diagrams/secuencias/cu-06.puml) — Gestionar Turnos
  - [CU-07](docs/diagrams/secuencias/cu-07.puml) — Consultar Historia Clínica
- [Wireframes HTML](docs/diagrams/wireframes/html/index.html) — maquetas interactivas de las pantallas

### Hito 2 — Codificación y Refactorización

- [x] Codificación — Capa de datos/negocio (`consultorio/` package)
- [x] Codificación — Capa de interfaz (`formulario_odontologico/` package)
- [x] Pruebas de integración con SQLite `:memory:` (32 tests)
- [x] Refactorización Deep Module — separación en módulos internos con seams testables
- [x] Máquina de estados explícita para Turno (`_EstadoTurno`)
- [x] Linting (Ruff) + Formato (Black)

## Ejecución

```bash
python3 main.py [ruta_db]
```

Si no se especifica ruta, usa `saca_muela.db` en el directorio actual.

## Tests

```bash
# Desde el directorio code/
PYTHONPATH=. python3 -m pytest tests/ -v

# Sin pytest (test runner mínimo):
PYTHONPATH=. python3 tests/runner.py
```

## Herramientas de Desarrollo

### Makefile

El proyecto incluye un `Makefile` con los comandos más frecuentes del flujo de desarrollo:

| Target       | Comando equivalente                         |
| :----------- | :------------------------------------------ |
| `make run`   | `python3 main.py [DB]`                      |
| `make test`  | `python3 -m pytest tests/ -v`               |
| `make seed`  | `python3 scripts/seed.py [DB]`              |
| `make reset` | Borra la DB y ejecuta `make seed`           |
| `make lint`  | `ruff check .`                              |
| `make format`| `black .`                                   |

La variable `DB` permite elegir el archivo de base de datos:

```bash
make run DB=test.db
make seed DB=test.db
```

### Seed de datos de prueba

El script `scripts/seed.py` puebla la base de datos con datos realistas para desarrollo:

- **6 pacientes** con perfiles variados (con/sin obra social, con/sin teléfono)
- **Turnos** en distintos estados (Pendiente, Confirmado, Cancelado)
- **Entradas de historia clínica** para varios pacientes

```bash
make seed                  # usa saca_muela.db por defecto
make seed DB=dev.db        # o sobre una DB específica
```

El seed utiliza la API pública de `Consultorio`, respetando la separación de capas y las reglas de dominio (ej. un paciente sin teléfono no recibe turno).

## Autor

Lapenta, Carlos Matías — Algoritmos y Estructuras de Datos II
