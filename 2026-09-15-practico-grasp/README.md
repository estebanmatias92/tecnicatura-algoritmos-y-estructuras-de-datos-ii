# Practico 11 — Patrones GRASP (Controlador)

> Algoritmos y Estructuras de Datos II — Unidad 04. Calculadora que separa la interfaz de consola de la lógica de la ecuación mediante el patrón **Controller** de GRASP.

El sistema aplica el patrón **Controller** (GRASP) para separar la interfaz de usuario (consola) de la lógica que maneja la ecuación (suma, resta, multiplicación o división).

- **Contexto:** `Controlador` coordina la operación entre `Consola` y `Calculadora`.
- **Information Expert:** `Calculadora` conoce los operandos y ejecuta el cálculo.
- **Low Coupling:** `Consola` depende del `Controlador`, no de `Calculadora`.

## Stack Tecnológico

- **Lenguaje:** C++17
- **Compilador:** g++ (GCC)
- **Build:** GNU Make
- **Dependencias:** STL únicamente (sin librerías externas)

## Arquitectura

El sistema implementa el patrón **Controller** (GRASP) con la siguiente estructura:

- `Consola` — interfaz de usuario (lectura/escritura por consola), sin conocimiento directo de la lógica
- `Controlador` — recibe y coordina la operación desde la UI, delega el cálculo a `Calculadora`
- `Calculadora` — experto en información: conoce los operandos y realiza la operación

Esto permite cambiar la interfaz de usuario (por ejemplo, a una GUI) sin modificar la lógica de cálculo, y viceversa.

## Scaffolding

```
.
├── Makefile
├── README.md
├── .gitignore
├── .task-state.json
├── include/
│   ├── Calculadora.hpp   # Lógica de la ecuación (Information Expert)
│   ├── Controlador.hpp   # Coordinador UI <-> lógica (Controller GRASP)
│   └── Consola.hpp       # Interfaz de consola (UI)
├── src/
│   ├── main.cpp          # Punto de entrada y bucle principal
│   ├── Calculadora.cpp
│   ├── Controlador.cpp
│   └── Consola.cpp
├── obj/                  # Objetos compilados (gitignored)
├── docs/
│   ├── glosario-de-dominio.md
│   ├── registro-necesidades.md
│   └── diagrams/
│       └── diagrama-clases.puml
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

## Aplicación de GRASP

| Patrón GRASP | Aplicación en la calculadora |
|--------------|------------------------------|
| **Controller** | `Controlador` recibe la operación desde la consola y la delega a `Calculadora`; la UI no toca la lógica directamente |
| **Information Expert** | `Calculadora` conoce los operandos y es la encargada de operar |
| **Low Coupling** | `Consola` depende del `Controlador` (interfaz), no de `Calculadora` |
| **Protected Variations** | La interfaz de `Calculadora` aísla a la UI de cambios en el algoritmo |

## Ejemplo de uso

```
$ make run
=== Calculadora GRASP (patron Controller) ===
Operaciones soportadas: +, -, *, /
Escribe 'salir' para terminar.

Ingresa operacion (ej: 5 + 3) o 'salir':
10 / 4
10 / 4 = 2.50

Ingresa operacion (ej: 5 + 3) o 'salir':
6 / 0
Error: Division por cero no permitida

Ingresa operacion (ej: 5 + 3) o 'salir':
salir
Saliendo de la calculadora. ¡Hasta luego!
```

## Autor

Lapenta Carlos Matías — Algoritmos y Estructuras de Datos II
