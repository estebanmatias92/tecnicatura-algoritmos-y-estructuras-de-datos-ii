# Registro de Necesidades — Practica 05 (Patrones Creacionales)

## Necesidades Funcionales (RN)

| ID | Descripción | Prioridad | Consigna Origen |
|---|---|---|---|
| RN-001 | El sistema debe definir interfaces abstractas para los productos `Chair`, `Sofa` y `CoffeeTable`. | Alta | Marco Práctico — 1 |
| RN-002 | Cada producto abstracto debe declarar las operaciones propias de su tipo (ej: `sitOn()`, `hasLegs()`, `lieOn()`, `hasCushions()`). | Alta | Marco Práctico — 1 |
| RN-003 | El sistema debe implementar productos concretos para la variante **Modern**: `ModernChair`, `ModernSofa`, `ModernCoffeeTable`. | Alta | Marco Práctico — 1 |
| RN-004 | El sistema debe implementar productos concretos para la variante **Victorian**: `VictorianChair`, `VictorianSofa`, `VictorianCoffeeTable`. | Alta | Marco Práctico — 1 |
| RN-005 | El sistema debe implementar productos concretos para la variante **ArtDeco**: `ArtDecoChair`, `ArtDecoSofa`, `ArtDecoCoffeeTable`. | Alta | Marco Práctico — 1 |
| RN-006 | El sistema debe definir una interfaz `MuebleriaFactory` (Fábrica Abstracta) con métodos `createChair()`, `createSofa()` y `createCoffeeTable()`. | Alta | Marco Práctico — 1 |
| RN-007 | El sistema debe implementar fábricas concretas: `ModernFactory`, `VictorianFactory`, `ArtDecoFactory`, cada una creando productos de su variante. | Alta | Marco Práctico — 1 |
| RN-008 | El sistema debe incluir un cliente (`main.cpp`) que demuestre la creación de una familia completa de muebles usando cada fábrica concreta. | Alta | Marco Práctico — 1 |
| RN-009 | El sistema debe compilar con `g++` y un `Makefile` sin dependencias externas. | Alta | Stack definido |

## Necesidades No Funcionales (RNF)

| ID | Descripción |
|---|---|
| RNF-001 | El código debe seguir el patrón **Abstract Factory** según la definición del GoF. |
| RNF-002 | El código debe estar organizado en archivos separados: interfaces (`.hpp`), implementaciones (`.cpp`) y programa principal. |
| RNF-003 | El `Makefile` debe compilar todos los fuentes y producir un binario `muebleria`. |

## Necesidades Teóricas (RT)

| ID | Descripción | Consigna Origen |
|---|---|---|
| RT-001 | Describir los tipos de patrones de software. | Marco Teórico — 1 |
| RT-002 | Definir qué es un patrón de software. | Marco Teórico — 2 |
| RT-003 | Clasificar los patrones de software. | Marco Teórico — 3 |
| RT-004 | Clasificar los patrones de creación y describir cada uno. | Marco Teórico — 4 |
| RT-005 | Dar un ejemplo de uso de cada patrón creacional. | Marco Teórico — 5 |
