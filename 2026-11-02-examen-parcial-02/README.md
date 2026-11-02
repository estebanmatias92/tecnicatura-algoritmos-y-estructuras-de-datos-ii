# Examen Parcial 02 — Productos de Goma

> Algoritmos y Estructuras de Datos II — Unidad 07. Fecha: 2026-11-02.

Aplicación de consola (CLI de menú interactivo) que permite gestionar la compra de
materia prima ("Productos de Goma"): cargar artículos, cargar proveedores y cargar pedidos,
y mostrar los pedidos agrupados por proveedor. Persistencia de proveedores en MariaDB
con catálogo de artículos y pedidos de demostración sembrados desde SQL.

## Stack y dependencias

- C++17, `g++`, STL únicamente.
- `libmariadb` (MariaDB Connector/C) a través de `pkg-config` — única dependencia
  externa de ejecución.
- `CMake` genera el build; `Make` orquesta; `GoogleTest 1.18` (instalado a nivel
  sistema, `find_package(GTest REQUIRED)`) prueba; `CTest` ejecuta.
- MariaDB se levanta en Docker con `docker-compose.yml`.
- `gcov` + `gcovr` (vía `nix-shell -p gcovr`) miden la cobertura.

## Requisitos previos

```bash
g++ cmake make pkg-config libmariadb-dev docker docker-compose
```

Para cobertura:

```bash
nix-shell -p gcovr
```

## Estructura del proyecto

```text
CMakeLists.txt            # configuración del build (CMake)
Makefile                  # task runner (targets abajo)
include/*.hpp             # cabeceras del dominio, servicios, repositorios y consola
src/*.cpp                 # implementación (dominio, servicios, adaptadores MariaDB, main)
tests/*.cpp               # pruebas GoogleTest
db/init/01-schema.sql     # esquema relacional
db/init/02-seed.sql       # datos de demostración (catálogo + pedidos)
docker-compose.yml        # contenedor MariaDB
build/                    # artefactos de build (gitignorado)
docs/                     # especificaciones, ADR, diagramas
```

## Targets de `make`

| Target | Descripción |
| -------- | ------------- |
| `all` / `build` | Configura con CMake y compila (`Debug`, `-Wall -Wextra`, cero advertencias). |
| `run` | Ejecuta la app (`build/parcial02`). Requiere MariaDB arriba (`docker compose up -d`). |
| `test` | Pruebas unitarias con CTest. **No necesita Docker**. |
| `test-integration` | Pruebas de integración (`-L integration`). Requiere MariaDB arriba. |
| `coverage` | Cobertura de líneas con `gcov`/`gcovr` sobre `src/`. Excluye `main.cpp`, los adaptadores MariaDB (cubiertos por `test-integration`) y el bucle del menú (`Console::run`, marcado con `GCOVR_EXCL`). Umbral: ≥ 80 %. |
| `clean` | Borra el directorio `build/`. |

## Levantar MariaDB

Desde la raíz del proyecto:

```bash
docker compose up -d
```

Esto crea el contenedor `parcial02-mariadb`, aplica `db/init/01-schema.sql` y
`db/init/02-seed.sql` en el primer arranque, y expone el puerto 3306.

Las credenciales se toman de variables de entorno con valores por defecto solo para
desarrollo (ninguna credencial real se versiona):

| Variable | Default |
| ---------- | --------- |
| `MARIADB_HOST` | `127.0.0.1` |
| `MARIADB_PORT` | `3306` |
| `MARIADB_DATABASE` | `parcial02` |
| `MARIADB_USER` | `parcial02` |
| `MARIADB_PASSWORD` | `parcial02-pass` |

Si la base no está disponible al iniciar, la app imprime `MSG-003` y `MSG-004` y
termina con código `1` sin mostrar el menú (RN-017 / AC-017).

## Correr las pruebas

Pruebas unitarias (sin Docker):

```bash
make test
```

Pruebas de integración (requiere `docker compose up -d` previo):

```bash
make test-integration
```

Ejecutar la app (requiere MariaDB arriba):

```bash
docker compose up -d
make run
```

## Cobertura

```bash
make coverage
```

Genera el build con instrumentación `gcov`, ejecuta las pruebas unitarias e imprime
el reporte de `gcovr` sobre `src/`. Umbral exigido por RNF-011: ≥ 80 % de líneas
sobre `src/` (excluyendo `main.cpp`, los adaptadores MariaDB y el bucle del menú).

## Antes y después (refactoring)

El historial demuestra el paso de la versión "antes" (clase `App` en memoria) a la
versión "después" (RAII, IoC, SOLID, GRASP: `Console`, servicios, repositorios
genéricos, `MessageCatalog`, adaptadores MariaDB):

- Tag `parcial02-antes`: versión inicial.
- Tag `parcial02-final`: versión refactorizada (HEAD).

Ver `docs/refactoring.md` y los diagramas de `docs/diagrams/`.

## Notas

- `make test` no necesita Docker; `make test-integration` y `make run` sí.
- Los gitlinks sucios del práctico hermano `2026-10-22-practico-cmake-gtest/` son
  ajenos a este trabajo y no se tocan.
