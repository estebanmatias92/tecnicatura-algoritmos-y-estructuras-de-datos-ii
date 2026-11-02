# Registro de Necesidades — Parcial 02 (Productos de Goma)

> Derivado de la consigna del Examen Parcial 02 (ver `consignas.md`). Los requisitos
> funcionales trazan a los cuatro puntos del enunciado; los no funcionales trazan a
> los requerimientos de diseño y a las convenciones del curso. La columna *Origen*
> distingue lo que pide el enunciado de lo que se deriva de él.
>
> Las reglas de negocio que restringen estos requisitos viven en
> `reglas-de-negocio.md` (`BR-###`) y su aceptación en `criterios-de-aceptacion.md`
> (`AC-###`).

## Requisitos funcionales

| ID | Requisito | Prioridad | Origen |
|----|-----------|-----------|--------|
| RN-001 | El sistema debe permitir dar de alta `Article`, con `code`, `description` y `unitPrice`. | Alta | Consigna punto 1 |
| RN-002 | El sistema debe permitir dar de alta, listar, modificar y eliminar `Supplier` (CRUD completo). | Alta | Consigna punto 2 |
| RN-003 | El sistema debe permitir cargar un `PurchaseOrder` asignándolo a un `Supplier` existente. | Alta | Consigna punto 3 |
| RN-004 | Un `PurchaseOrder` debe contener uno o más `Article`, cada uno con su `Quantity`. | Alta | Consigna punto 3 + fidelidad al caso real |
| RN-005 | `Quantity` debe ser mayor que cero; el sistema debe rechazar cualquier cantidad inválida al cargar el pedido. | Alta | Derivado de RN-004 |
| RN-006 | Un `PurchaseOrder` pertenece a un único `Supplier`. | Alta | Consigna punto 3 |
| RN-007 | El sistema debe mostrar por consola los pedidos, agrupados por proveedor, con cantidad, precio unitario, subtotal y total por pedido. | Alta | Consigna punto 4 |
| RN-008 | El sistema debe rechazar la creación de un pedido cuyo `Supplier` o `Article` no existan, informando el motivo. | Media | Derivado de RN-003/RN-004 |
| RN-009 | El sistema debe impedir eliminar un `Supplier` que tenga pedidos asociados. | Media | Derivado de RN-002/RN-006 |
| RN-010 | El sistema debe ofrecer una opción de salida en el menú principal. | Alta | Necesario para operar la app |
| RN-011 | `Article` y `PurchaseOrder` se cargan pero no se editan ni eliminan; solo `Supplier` tiene CRUD completo. | Alta | Consigna, requerimiento 5 |
| RN-012 | El sistema debe asignar a cada `PurchaseOrder` un `OrderNumber` único y autogenerado. | Alta | Derivado de RN-007 (poder nombrar el pedido) |
| RN-013 | El sistema debe registrar la fecha de creación del pedido con la fecha del sistema al momento de crearlo. | Media | Derivado de RN-003 + caso real |
| RN-014 | El sistema debe permitir ingresar la fecha de entrega esperada, rechazando las anteriores a la fecha de creación. | Media | Derivado de RN-013 |
| RN-015 | El sistema debe calcular y mostrar el total del pedido como la suma de `unitPrice × Quantity` de sus ítems. | Media | Derivado de RN-001 + RN-007 |
| RN-016 | El sistema debe persistir los `Supplier` en MariaDB, de modo que las altas, modificaciones y bajas sobrevivan al reinicio de la aplicación. | Alta | Derivado de RN-002 + requisito de stack |
| RN-017 | Si la base de datos no está disponible al iniciar, el sistema debe informar el error por consola y terminar con código distinto de cero. | Alta | Derivado de RN-016 |
| RN-018 | El catálogo de `Article` y los `PurchaseOrder` de demostración deben inicializarse desde un seed versionado. | Alta | RN-011 + RN-016 |

## Requisitos no funcionales

| ID | Requisito | Prioridad |
|----|-----------|-----------|
| RNF-001 | El código debe compilar con C++17 y `g++`, usando STL y `libmariadb` (MariaDB Connector/C) como única dependencia externa de ejecución. | Alta |
| RNF-002 | CMake debe generar el build y Make debe actuar como task runner, con targets `all`, `build`, `run`, `test`, `test-integration` y `clean`. | Alta |
| RNF-003 | El código debe compilar sin advertencias con `-Wall -Wextra`. | Alta |
| RNF-004 | El layout debe ser `CMakeLists.txt`, `cmake/`, `include/*.hpp`, `src/*.cpp`, `tests/`, `db/` y el directorio de build fuera del árbol versionado. | Alta |
| RNF-005 | El diseño debe demostrar el **antes y el después** de aplicar RAII, IoC, SOLID y GRASP, en diagrama y en código. | Alta |
| RNF-006 | La demostración debe ser navegable en el historial mediante los tags `parcial02-antes` y `parcial02-final`, con un commit por principio aplicado. | Alta |
| RNF-007 | Los identificadores del código deben estar en inglés; los textos de la interfaz de usuario y la documentación, en español. | Media |
| RNF-008 | Los diagramas deben versionarse como `.puml` en `docs/diagrams/` y commitearse renderizados a `.svg`. | Media |
| RNF-009 | Las pruebas deben escribirse con GoogleTest, obtenido por `find_package(GTest REQUIRED)` y ejecutado con CTest. | Alta |
| RNF-010 | MariaDB debe servirse desde un contenedor Docker versionado con un `docker-compose.yml` en el proyecto. | Alta |
| RNF-011 | La cobertura de líneas debe ser ≥ 80 % sobre `Quantity`, `Cuit`, `Money`, `Date`, los repositorios y los servicios; `main.cpp` y el bucle del menú quedan excluidos. | Media |
| RNF-012 | El esquema y el seed deben vivir en `db/init/*.sql` y aplicarse automáticamente en el primer arranque del contenedor. | Media |
| RNF-013 | Las credenciales de la base deben tomarse de variables de entorno, con valores por defecto solo para desarrollo; ninguna credencial real se versiona. | Media |

## Fuera de alcance

Decisiones explícitas para no inventar requisitos que la consigna no pide:

| Tema | Por qué queda afuera |
|------|----------------------|
| Histórico de precios y facturación | El precio unitario vive en el artículo y el total se recalcula; congelar el precio por pedido exigiría una entidad de línea (ver ADR-0002). |
| Stock o inventario | El sistema gestiona la **compra**, no la existencia en depósito. |
| Estados del pedido (pendiente, recibido, cancelado) y recepción de mercadería | No se pide flujo de aprobación ni recepción. |
| Edición y baja de pedidos o artículos | RN-011: solo `Supplier` tiene CRUD completo. |
| Varios proveedores por pedido | RN-006 fija un único proveedor por pedido. |
| Autenticación, usuarios y roles | Aplicación de consola de un solo operador. |
| TUI o interfaz gráfica | Decisión de ADR-0003: CLI de menú; una TUI futura sería otro adaptador de `Console`. |
| Migraciones automáticas de esquema | El esquema se aplica al crear el volumen; recrearlo es la forma de re-sembrar. |
| CI/CD y despliegue | El trabajo se verifica localmente con `make` y `docker compose`. |

## Decisiones de diseño

| ID | Decisión | Ver |
|----|----------|-----|
| RD-001 | El antes/después se demuestra con tags más un commit por principio, no con branches paralelos. | `docs/adr/0001-demostracion-del-refactoring.md` |
| RD-002 | La cantidad es un value type `Quantity`, sin entidad de línea de pedido; el precio vive en `Article` como `Money`. | `docs/adr/0002-modelo-de-pedido.md` |
| RD-003 | Aplicación CLI de menú interactivo sobre un núcleo testeable; CMake genera, Make orquesta, GTest prueba. | `docs/adr/0003-tipo-de-aplicacion-y-stack.md` |
| RD-004 | La persistencia entra por `Repository`: implementación en memoria para unitarios y MariaDB en Docker para integración. | `docs/adr/0004-persistencia-en-mariadb.md` |
| RD-005 | Pruebas en tres capas (unitarias, de integración y cobertura), con `make test` verde en cada commit del refactoring. | `docs/adr/0005-estrategia-de-pruebas.md` |
