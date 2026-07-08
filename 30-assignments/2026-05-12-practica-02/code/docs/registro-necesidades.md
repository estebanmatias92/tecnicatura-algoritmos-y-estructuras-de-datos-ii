# Registro de Necesidades (Requisitos Funcionales)

## Práctica 02 — Python Estructurado

### Menú Principal (Sistema)

| ID | Descripción | Prioridad |
|---|---|---|
| RN-000 | El sistema debe presentar un menú CLI jerárquico que permita seleccionar sección (1-10) y luego ejercicio dentro de cada sección. | Alta |
| RN-000a | El menú debe permitir volver al nivel anterior y salir del programa. | Alta |

### Sección 1 — Instalación y Entorno

| ID | Descripción | Prioridad |
|---|---|---|
| RN-001 | El sistema debe mostrar la consola interactiva e instrucciones de "Hola Mundo" e IDLE. | Baja (informativo) |
| RN-002 | El sistema debe documentar los comandos PIP: `get-pip.py`, `pip install --upgrade`, `pip list/show/update`. | Baja (informativo) |

### Sección 2 — Aspectos del Lenguaje (Parte Práctica)

| ID | Descripción | Prioridad |
|---|---|---|
| RN-003 | El sistema debe automatizar la creación, activación, instalación de Flask, desactivación y borrado de un entorno virtual. | Media |

### Sección 3 — Colecciones

| ID | Descripción | Prioridad |
|---|---|---|
| RN-004 | Generar una lista con los números del 1 al 100 e imprimirla. | Alta |
| RN-005 | Crear una tupla con meses del año, pedir un número al usuario y mostrar el mes correspondiente o error si está fuera de rango. | Alta |
| RN-006 | Pedir un número y guardar en una lista su tabla de multiplicar del 1 al 10, luego mostrar la lista. | Alta |
| RN-007 | Implementar una agenda telefónica con diccionario (clave=nombre, valor=teléfono), permitiendo agregar contactos hasta que el usuario decida salir, sin admitir nombres repetidos. | Alta |

### Sección 4 — Bucles

| ID | Descripción | Prioridad |
|---|---|---|
| RN-008 | Pedir dos enteros y mostrar qué números son pares e impares desde el primero hasta el segundo. | Alta |
| RN-009 | Pedir un número positivo al usuario repetidamente hasta que ingrese uno válido. | Alta |
| RN-010 | Pedir dos enteros; si el segundo no es mayor que el primero, pedirlo de nuevo; luego mostrar ambos. | Alta |
| RN-011 | Pedir dos enteros y mostrar la lista de números consecutivos entre ellos de menor a mayor. | Alta |

### Sección 5 — Funciones

| ID | Descripción | Prioridad |
|---|---|---|
| RN-012 | Pedir anchura, altura y carácter, y dibujar un rectángulo con esa configuración. | Alta |
| RN-013 | Pedir un año y determinar si es bisiesto (regla: múltiplo de 4, excepto múltiplos de 100 que no lo son, salvo múltiplos de 400). | Alta |
| RN-014 | Pedir un número N, luego solicitar N palabras, almacenarlas en una lista y mostrarla. | Alta |

### Sección 6 — Programación Funcional

| ID | Descripción | Prioridad |
|---|---|---|
| RN-015 | Obtener el cuadrado de todos los elementos de una lista usando `map`. | Alta |
| RN-016 | Contar elementos mayores a 5 en una tupla usando `filter`. | Alta |
| RN-017 | Contar elementos mayores a 5 en una tupla usando `reduce`. | Alta |

### Sección 7 — Excepciones

| ID | Descripción | Prioridad |
|---|---|---|
| RN-018 | Función `dividir(a, b)` que maneje `ZeroDivisionError` y lo capture con un mensaje descriptivo. | Alta |
| RN-019 | Función `mas_10(x)` que maneje `TypeError` si se pasa un string en lugar de número. | Alta |
| RN-020 | Crear lista e iterar más allá del índice para provocar y capturar `IndexError`. | Alta |
| RN-021 | Crear diccionario y buscar clave inexistente para provocar y capturar `KeyError`. | Alta |

### Sección 8 — Archivos

| ID | Descripción | Prioridad |
|---|---|---|
| RN-022 | Abrir (o crear) un fichero en modo lectura/escritura y añadir la frase "Estoy aprendiendo Python". | Alta |
| RN-023 | Abrir el fichero anterior y mostrar: estado, modo, nombre y codificación. | Alta |
| RN-024 | Realizar los ejercicios 1 y 2 usando la estructura `with`. | Alta |

### Sección 9 — Módulos y Paquetes

| ID | Descripción | Prioridad |
|---|---|---|
| RN-025 | Crear un paquete simple con `__init__.py` y al menos un módulo interno. | Alta |
| RN-026 | Crear scripts que importen y usen el paquete desde distintas ubicaciones. | Alta |
| RN-027 | Demostración de sys.path y scripts de nivel superior. | Alta |

### Sección 10 — Testing

| ID | Descripción | Prioridad |
|---|---|---|
| RN-028 | Implementar `funciones.py` con `calcula_media(*args)` y `tests.py` con unittest que la verifique. | Alta |
| RN-029 | Demostrar setUp/tearDown con prints de ejemplo. | Alta |
