# Drone IBag151

Solution for *Algoritmos y Estructuras de Datos II — Unidad 07 — TP 15: CMake & GTest*.

The assignment asks for an object-oriented drone ("IBag151") with a console
interface, a class diagram, SOLID/GRASP design, and one incremental unit test
per activity.

> **Status:** work in progress. The build system and all eleven drone
> activities with their unit tests are in place (S0–S11). The console
> adapter, diagrams and design documents are added in later increments.

## Layout

```
include/ibag151/   Domain ports and concrete types
src/               Implementations and the console entry point
tests/             One test file per activity
cmake/             Development dependencies (GoogleTest via FetchContent)
docs/              Requirements, glossary, refactoring notes and UML
scripts/           Demo console sessions
```

## Requirements

- CMake >= 3.20
- A C++17 compiler (GCC or Clang)
- `make` and network access on the first configure (GoogleTest is fetched)
- Optional: `clang-format`, `clang-tidy`, `plantuml`

## Usage

The `Makefile` is the only interface needed for everyday work:

```sh
make            # list the available targets
make build      # configure and compile everything
make test       # run the unit tests with CTest
make run        # run the console demo script
make check      # formatting check + build + tests
make dist       # package the sources for submission
```

The CMake tree lives in `build/` and is not committed.

## Activities

| # | Activity | Interface method | Test | Status |
|---|---|---|---|---|
| 1 | Despegar | `Drone::takeOff` | `tests/test_despegar.cpp` | Done |
| 2 | Aterrizar | `Drone::land` | `tests/test_aterrizar.cpp` | Done |
| 3 | Elevar | `Drone::ascend` | `tests/test_elevar.cpp` | Done |
| 4 | Bajar | `Drone::descend` | `tests/test_bajar.cpp` | Done |
| 5 | Girar a la derecha | `Drone::turnRight` | `tests/test_girar_derecha.cpp` | Done |
| 6 | Girar a la izquierda | `Drone::turnLeft` | `tests/test_girar_izquierda.cpp` | Done |
| 7 | Acelerar | `Drone::accelerate` | `tests/test_acelerar.cpp` | Done |
| 8 | Frenar | `Drone::brake` | `tests/test_frenar.cpp` | Done |
| 9 | Descargar el paquete | `Drone::unloadPackage` | `tests/test_descargar_paquete.cpp` | Done |
| 10 | Sacar foto de la recepción | `Drone::takeReceptionPhoto` | `tests/test_sacar_foto.cpp` | Done |
| 11 | Notificar la entrega | `Drone::notifyDelivery` | `tests/test_notificar_entrega.cpp` | Done |

## Design notes

- `Drone` is the port the rest of the program depends on; `DroneIbag151` is the
  concrete implementation. State is private and only changes through validated
  operations, raising `DroneError` when a transition is invalid.
- The interface grows one activity at a time, driven by a failing test first.
- GoogleTest is pinned to `v1.18.0` in `cmake/dependencies.cmake`; it is a
  development-only dependency and is not vendored in the repository.
