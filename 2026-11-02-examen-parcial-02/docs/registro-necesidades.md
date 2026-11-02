# Registro de Necesidades — Parcial 02 (Productos de Goma)

> Derivado de la consigna del Examen Parcial 02 (ver `consignas.md`). Los requisitos
> funcionales trazan a los cuatro puntos del enunciado; los no funcionales trazan a
> los requerimientos de diseño y a las convenciones del curso. La columna *Origen*
> distingue lo que pide el enunciado de lo que se deriva de él.

## Requisitos funcionales

| ID | Requisito | Prioridad | Origen |
|----|-----------|-----------|--------|
| RN-001 | El sistema debe permitir dar de alta `Article`, con `code` y `description`. | Alta | Consigna punto 1 |
| RN-002 | El sistema debe permitir dar de alta, listar, modificar y eliminar `Supplier` (CRUD completo). | Alta | Consigna punto 2 |
| RN-003 | El sistema debe permitir cargar un `PurchaseOrder` asignándolo a un `Supplier` existente. | Alta | Consigna punto 3 |
| RN-004 | Un `PurchaseOrder` debe contener uno o más `Article`, cada uno con su `Quantity`. | Alta | Consigna punto 3 + fidelidad al caso real |
| RN-005 | `Quantity` debe ser mayor que cero; el sistema debe rechazar cualquier cantidad inválida al cargar el pedido. | Alta | Derivado de RN-004 |
| RN-006 | Un `PurchaseOrder` pertenece a un único `Supplier`. | Alta | Consigna punto 3 |
| RN-007 | El sistema debe mostrar por consola los pedidos, agrupados por proveedor. | Alta | Consigna punto 4 |
| RN-008 | El sistema debe rechazar la creación de un pedido cuyo `Supplier` o `Article` no existan, informando el motivo. | Media | Derivado de RN-003/RN-004 |
| RN-009 | El sistema debe impedir eliminar un `Supplier` que tenga pedidos asociados. | Media | Derivado de RN-002/RN-006 |
| RN-010 | El sistema debe ofrecer una opción de salida en el menú principal. | Alta | Necesario para operar la app |
| RN-011 | `Article` y `PurchaseOrder` se cargan pero no se editan ni eliminan; solo `Supplier` tiene CRUD completo. | Alta | Consigna, requerimiento 5 |

## Requisitos no funcionales

| ID | Requisito | Prioridad |
|----|-----------|-----------|
| RNF-001 | El código debe compilar con C++17 y `g++`, usando únicamente la STL. | Alta |
| RNF-002 | El build debe gestionarse con GNU Make, con targets `all`, `run` y `clean`. | Alta |
| RNF-003 | El código debe compilar sin advertencias con `-Wall -Wextra`. | Alta |
| RNF-004 | El layout debe ser `include/*.hpp`, `src/*.cpp` y `obj/` para los objetos. | Alta |
| RNF-005 | El diseño debe demostrar el **antes y el después** de aplicar RAII, IoC, SOLID y GRASP, en diagrama y en código. | Alta |
| RNF-006 | La demostración debe ser navegable en GitHub mediante los tags `parcial02-antes` y `parcial02-final`, con un commit por principio aplicado. | Alta |
| RNF-007 | Los identificadores del código deben estar en inglés; los textos de la interfaz de usuario y la documentación, en español. | Media |
| RNF-008 | Los diagramas deben versionarse como `.puml` en `docs/diagrams/` y commitearse renderizados a `.svg`. | Media |

## Fuera de alcance

Decisiones explícitas para no inventar requisitos que la consigna no pide:

| Tema | Por qué queda afuera |
|------|----------------------|
| Precios, importes y totales del pedido | La consigna no menciona montos; agregarlos ensancha el modelo más allá de lo pedido. |
| Stock o inventario | El sistema gestiona la **compra**, no la existencia en depósito. |
| Estados del pedido (pendiente, recibido, cancelado) | No se pide flujo de aprobación ni recepción. |
| Persistencia en archivos o base de datos | El almacenamiento en memoria alcanza; el foco está en el diseño. |
| Varios proveedores por pedido | RN-006 fija un único proveedor por pedido. |
| Autenticación o usuarios | Aplicación de consola de un solo operador. |

## Decisiones de diseño

| ID | Decisión | Ver |
|----|----------|-----|
| RD-001 | El antes/después se demuestra con tags más un commit por principio, no con branches paralelos. | `docs/adr/0001-demostracion-del-refactoring.md` |
| RD-002 | La cantidad es un value type `Quantity`, sin entidad de línea de pedido. | `docs/adr/0002-modelo-de-pedido.md` |
