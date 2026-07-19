# Registro de Necesidades

## Ejercicio 3.1 — Calculadora Tkinter

| ID | Descripción | Prioridad |
|---|---|---|
| RN-001 | El sistema debe mostrar una ventana con interfaz gráfica para calculadora básica usando Tkinter | Alta |
| RN-002 | Debe permitir ingresar dos números (operador A y operador B) mediante Entry | Alta |
| RN-003 | Debe realizar las operaciones: suma, resta, multiplicación y división | Alta |
| RN-004 | Debe manejar la división por cero mostrando un mensaje de error sin crashear | Alta |
| RN-005 | Debe mostrar el resultado en la misma ventana | Alta |

## Ejercicio 3.2 — Repair Center (CRUD + SQLite)

| ID | Descripción | Prioridad |
|---|---|---|
| RN-006 | El sistema debe administrar pedidos de servicio técnico de un Repair Center | Alta |
| RN-007 | Cada pedido debe registrar: Apellido y Nombre del Cliente | Alta |
| RN-008 | Cada pedido debe registrar: Dirección (calle y altura) | Alta |
| RN-009 | Cada pedido debe registrar: Inconveniente o problema reportado | Alta |
| RN-010 | Cada pedido debe registrar: Técnico asignado | Alta |
| RN-011 | Cada pedido debe registrar: Fecha y hora de la visita agendada | Alta |
| RN-012 | El sistema debe persistir todos los pedidos en una base de datos SQLite | Alta |
| RN-013 | La GUI debe permitir crear un nuevo pedido de servicio | Alta |
| RN-014 | La GUI debe permitir listar todos los pedidos en un widget Treeview | Alta |
| RN-015 | La GUI debe permitir modificar un pedido seleccionado | Alta |
| RN-016 | La GUI debe permitir eliminar un pedido seleccionado | Alta |
| RN-017 | La GUI debe permitir limpiar los campos del formulario | Media |

## Ejercicio 3.3 — Login Screen

| ID | Descripción | Prioridad |
|---|---|---|
| RN-018 | El sistema debe mostrar una pantalla de inicio de sesión (usuario y clave) antes de acceder al Repair Center | Alta |
| RN-019 | Las credenciales deben almacenarse en una tabla SQLite `usuarios` | Alta |
| RN-020 | Debe validar las credenciales contra la base de datos | Alta |
| RN-021 | Si las credenciales son correctas, debe cerrar el login y abrir el dashboard del Repair Center | Alta |
| RN-022 | Si son incorrectas, debe mostrar un mensaje de error y permitir reintentar | Alta |
| RN-023 | Debe existir un usuario por defecto (`admin` / `admin123`) creado al inicializar la base de datos | Alta |

## Generales

| ID | Descripción | Prioridad |
|---|---|---|
| RN-024 | El stack debe ser Python 3 exclusivamente con biblioteca estándar (tkinter, sqlite3) | Alta |
| RN-025 | La aplicación debe tener un menú principal tipo dashboard para acceder a Calculadora y Repair Center | Alta |
