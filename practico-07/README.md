# Practico 07 — Patrones de Comportamiento (Strategy)

> Algoritmos y Estructuras de Datos II — Unidad 04. Aplicación de navegación que calcula ruta según medio de transporte mediante el patrón **Strategy**.

El sistema implementa el patrón **Strategy** (GoF) para variar el algoritmo de navegación en tiempo de ejecución sin modificar la clase `Navigator`.

- **Contexto:** `Navigator` mantiene una referencia a `Strategy`.
- **Interfaz:** `Strategy` define `executeAlgorithm()`.
- **Estrategias concretas:** `Coche`, `Peaton`, `TransportePublico`.

## Stack Tecnológico

- **Lenguaje:** C++17
- **Compilador:** g++ (GCC)
- **Build:** GNU Make
- **Dependencias:** STL únicamente (sin librerías externas)

## Arquitectura

Se aplica el patrón **Strategy** con la siguiente estructura:

- `Navigator` — contexto que delega la ejecución a la estrategia actual (`setStrategy` / `getStrategy`)
- `Strategy` — interfaz abstracta (`executeAlgorithm()`)
- `Coche`, `Peaton`, `TransportePublico` — estrategias concretas que implementan algoritmos de navegación específicos

Esto permite cambiar el medio de transporte (y su algoritmo de ruta) sin alterar `Navigator`.

## Scaffolding

```
.
├── Makefile
├── README.md
├── .gitignore
├── include/
│   ├── Strategy.hpp
│   ├── Navigator.hpp
│   ├── Coche.hpp
│   ├── Peaton.hpp
│   └── TransportePublico.hpp
├── src/
│   ├── main.cpp
│   ├── Navigator.cpp
│   ├── Coche.cpp
│   ├── Peaton.cpp
│   └── TransportePublico.cpp
├── obj/                # Objetos compilados (gitignored)
```

## Setup y ejecución

### Prerrequisitos

- `g++` con soporte C++17
- `make`

### Compilación

```bash
make
```

### Ejecución

```bash
make run
```

### Limpieza

```bash
make clean
```

## Autor

Lapenta Carlos Matías — Algoritmos y Estructuras de Datos II
