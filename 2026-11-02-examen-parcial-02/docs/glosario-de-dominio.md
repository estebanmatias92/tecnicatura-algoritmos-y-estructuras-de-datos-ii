# Glosario de Dominio — Parcial 02 (Productos de Goma)

> Vocabulario del sistema de gestión de compra de materia prima. Todo término que
> aparezca en el código, en los issues o en los diagramas debe coincidir con esta tabla.

## Términos del dominio

| Término | Definición |
|---------|------------|
| Artículo | Unidad de materia prima que la empresa compra. Es lo que se carga en el sistema y lo que se pide a un proveedor. Tiene un código identificador y una descripción. |
| Materia Prima | El insumo físico que la empresa transforma en productos de goma (caucho, azufre, negro de humo, aceite). En el sistema **no** es una entidad separada: se modela como `Artículo`. |
| Proveedor | Empresa a la que se le compra materia prima. Es la única entidad con CRUD completo (alta, baja, modificación, listado) en esta versión. Tiene CUIT y razón social. |
| Pedido | Solicitud de compra de uno o más artículos, asignada a **un único** proveedor. Es el objeto que el sistema muestra por consola. |
| Renglón de Pedido | Cada línea de un pedido: un artículo y la cantidad pedida de ese artículo. Un pedido agrupa uno o más renglones. |
| Cantidad | Número de unidades de un artículo dentro de un renglón. Siempre mayor que cero. |
| CRUD | Alta, lectura, modificación y baja de una entidad. En este trabajo solo `Proveedor` lo tiene completo. |
| Hardcodeado | Datos de artículos y pedidos definidos directamente en el código en lugar de cargados por el usuario. Es una concesión permitida por la consigna para la versión inicial. |

## Términos técnicos del diseño

| Término | Definición |
|---------|------------|
| Consola | Interfaz de usuario: lee opciones y escribe resultados por terminal. No conoce reglas de negocio ni almacenamiento. |
| Repositorio | Objeto que guarda y recupera entidades en memoria. Oculta la colección concreta que las contiene. |
| Servicio | Objeto que coordina las operaciones del sistema (crear proveedor, armar pedido) y aplica las reglas de negocio. |
| Versión "antes" | Implementación inicial con los defectos de diseño plantados a propósito, previa al refactoring. Se identifica con el tag `parcial02-antes`. |
| Versión "después" | Implementación refactorizada, con RAII, IoC, SOLID y GRASP aplicados. Se identifica con el tag `parcial02-final`. |

## Términos que NO se usan

Evitar estos sinónimos para no fragmentar el vocabulario:

| No usar | Usar en su lugar | Motivo |
|---------|------------------|--------|
| Producto, Ítem, Insumo | **Artículo** | La consigna usa "artículos"; un segundo nombre para lo mismo confunde el diagrama. |
| Compra, Orden de compra | **Pedido** | El enunciado habla de "pedidos a los proveedores". |
| Detalle, Línea, Ítem de pedido | **Renglón de Pedido** | Término único para la composición `Pedido 1..* Renglón`. |
| Cliente | — | No existe: la empresa es la compradora, no hay clientes en el modelo. |
| Stock, Inventario | — | Fuera de alcance, ver `registro-necesidades.md`. |
