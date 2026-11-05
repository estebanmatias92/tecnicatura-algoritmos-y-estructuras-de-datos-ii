# Drone IBag151

Solution for *Algoritmos y Estructuras de Datos II — Unidad 07 — TP 15: CMake & GTest*.

The assignment asks for an object-oriented drone ("IBag151") with a console
interface, a class diagram, SOLID/GRASP design, and one incremental unit test
per activity.

> **Status:** implementation complete for the assignment scope. Build system,
> the eleven drone activities, the console adapter, 57 unit tests, design
> documents and UML diagrams are in place.

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

## Console commands

The console reads one command per line and echoes it as "sent to the drone":

| Command | Effect |
|---|---|
| `despegar` | Take off |
| `aterrizar` | Land (resets altitude and speed) |
| `elevar [metros]` | Gain altitude (default 1 m) |
| `bajar [metros]` | Lose altitude (default 1 m) |
| `girar derecha` / `girar izquierda` | Rotate 90° |
| `acelerar [unidades]` | Increase speed (default 1) |
| `frenar [unidades]` | Reduce speed, clamped at 0 (default 1) |
| `descargar paquete` | Unload the package after landing |
| `sacar foto` | Take the reception photo |
| `notificar entrega` | Notify the delivery |
| `estado` | Print flight and delivery status |
| `ayuda` | Print the command list |
| `salir` | End the session |

`make run` feeds `scripts/demo.txt`, a complete scripted delivery. Use
`make run-interactive` to type commands yourself.

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

## Documentation

- [Consignas del TP](docs/consignas.md)
- [Requisitos y criterios de aceptación](docs/requisitos.md)
- [Reglas de vuelo y de entrega](docs/reglas-de-vuelo.md)
- [Glosario de dominio](docs/glosario-de-dominio.md)
- [Refactoring: de `Car` a `DroneIbag151`](docs/refactoring.md)
- ADRs: [FetchContent](docs/adr/0001-fetchcontent-gtest.md),
  [Makefile](docs/adr/0002-makefile-task-runner.md),
  [PlantUML](docs/adr/0003-puml-para-uml.md)

## UML

- [Diagrama de clases](docs/diagrams/drone-ibag151.svg)
  ([fuente](docs/diagrams/drone-ibag151.puml))
- [Flujo de consola](docs/diagrams/console-flow.svg)
  ([fuente](docs/diagrams/console-flow.puml))
- [Estados de vuelo y entrega](docs/diagrams/delivery-states.svg)
  ([fuente](docs/diagrams/delivery-states.puml))

Regenerate them with `make diagram`.

## Design notes

- `Drone` is the port the rest of the program depends on; `DroneIbag151` is the
  concrete implementation. State is private and only changes through validated
  operations, raising `DroneError` when a transition is invalid.
- `ConsoleInterface` is an adapter that receives the streams and the port by
  constructor, so it can be tested with string streams and never touches
  global `std::cin`/`std::cout`.
- The interface grew one activity at a time, each one driven by a failing test
  first.
- GoogleTest is pinned to `v1.18.0` in `cmake/dependencies.cmake`; it is a
  development-only dependency and is not vendored in the repository.
