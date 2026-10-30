# TP 08 — Plantillas (Templates) en C++17

> Proyecto de Algoritmos y Estructuras de Datos II — Unidad 04, TP 08 (Templates). Implementa ejercicios teóricos y prácticos de plantillas de funciones y clases en C++17.

## Stack Tecnológico

- **Lenguaje:** C++17
- **Compilador:** g++ (GCC)
- **Build System:** GNU Make
- **Dependencias:** STL únicamente (sin librerías externas)

## Documentación del sistema

- [`docs/requisitos.md`](docs/requisitos.md) — especificaciones / requisitos del TP (no duplicado de consigna)

## Arquitectura

El sistema implementa **plantillas de funciones y clases** (puntos 5-7 de la consigna):

- `convertir<R,A>` — función con dos parámetros de plantilla distintos
- `Caja<T>` — clase con parámetro como variable miembro
- `Convertidor<T,R>` — clase con dos parámetros (constructor `T`, método sin args retorna `R`)
- `menor<T>` — función genérica con operador `<`
- `menorDistintos<T,U>` — variante con argumentos de distinto tipo

Esto permite demostrar declaración, instanciación y especialización de plantillas.

![Diagrama de Clases](docs/diagrams/diagrama-clases.svg)

## Scaffolding

```
code/
├── include/
│   └── templates.hpp             # Declaraciones de plantillas (ejercicios 5-7)
├── src/
│   ├── main.cpp                  # Comprobaciones prácticas (ejercicios 8-10)
├── obj/                          # Objetos compilados (gitignored)
├── docs/
│   ├── requisitos.md             # Especificaciones / requisitos del TP
│   ├── registro-necesidades.md
│   └── diagrams/
│       ├── diagrama-clases.puml
│       └── diagrama-clases.svg
├── Makefile
├── .gitignore
└── README.md
```

## Setup y ejecución

### Prerrequisitos

- g++ con soporte C++17
- GNU Make
- Opcional: PlantUML (para re-renderizar diagramas)

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

Si se modificaron los diagramas, re-renderizar:

```bash
plantuml -tsvg docs/diagrams/*.puml
```

## Autor

Lapenta Carlos Matías — Algoritmos y Estructuras de Datos II
