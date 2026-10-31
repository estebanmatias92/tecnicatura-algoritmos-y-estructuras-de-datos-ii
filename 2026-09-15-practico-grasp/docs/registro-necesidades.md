# Registro de Necesidades — Calculadora GRASP

## Requisitos funcionales

| ID | Requisito | Prioridad |
|----|-----------|-----------|
| RN-001 | El sistema debe leer una operación aritmética desde la consola en formato `numero operador numero`. | Alta |
| RN-002 | El sistema debe soportar las operaciones suma (`+`), resta (`-`), multiplicación (`*`) y división (`/`). | Alta |
| RN-003 | El sistema debe separar la interfaz de consola de la lógica de cálculo mediante el patrón Controller de GRASP. | Alta |
| RN-004 | El sistema debe mostrar el resultado de la operación por consola. | Alta |
| RN-005 | El sistema debe rechazar la división por cero con un mensaje de error claro. | Alta |
| RN-006 | El sistema debe rechazar operadores inválidos con un mensaje de error claro. | Media |
| RN-007 | El sistema debe permitir salir escribiendo `salir`. | Media |

## Requisitos no funcionales

| ID | Requisito | Prioridad |
|----|-----------|-----------|
| RNF-001 | El código debe compilar con C++17 y `g++` sin advertencias (`-Wall -Wextra`). | Alta |
| RNF-002 | El build debe gestionarse con GNU Make. | Alta |
| RNF-003 | No se deben usar librerías externas; solo STL. | Alta |
