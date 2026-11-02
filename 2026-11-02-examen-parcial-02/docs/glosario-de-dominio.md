# Glosario de Dominio — Parcial 02 (Productos de Goma)

> Nomenclatura del sistema. Los **identificadores de código son en inglés**; los textos
> de la futura interfaz de usuario y la documentación se mantienen en español.
> La columna "Término en la consigna" mantiene la trazabilidad con el enunciado.

## Términos del dominio

| Término (código) | Término en la consigna | Definición |
|------------------|------------------------|------------|
| `Article` | Artículo | Unidad de materia prima que la empresa compra. Es lo que se carga en el sistema y lo que se pide a un proveedor. Tiene `code` y `description`. |
| `RawMaterial` | Materia Prima | El insumo físico que la empresa transforma en productos de goma (caucho, azufre, negro de humo, aceite). **No** es un tipo propio: se modela como `Article`. |
| `Supplier` | Proveedor | Empresa a la que se le compra materia prima. Es la única entidad con CRUD completo en esta versión. Tiene `cuit` y `businessName`. |
| `PurchaseOrder` | Pedido | Solicitud de compra de uno o más `Article`, asignada a **un único** `Supplier`. Es el objeto que el sistema muestra por consola. |
| `Quantity` | Cantidad | Value type inmutable que representa unidades de un `Article` dentro de un pedido. Garantiza en su constructor que el valor sea mayor que cero, así que un `Quantity` inválido no puede existir. |
| `CRUD` | CRUD | Alta, lectura, modificación y baja de una entidad. Solo `Supplier` lo tiene completo. |
| `Hardcoded` | Hardcodeado | Datos de `Article` y `PurchaseOrder` definidos en el código en lugar de cargados por el usuario. Es una concesión permitida por la consigna para la versión inicial. |

## Términos técnicos del diseño

| Término (código) | Término en la consigna | Definición |
|------------------|------------------------|------------|
| `Console` | Consola | Interfaz de usuario: lee opciones y escribe resultados por terminal. No conoce reglas de negocio ni almacenamiento. |
| `Repository` | Repositorio | Objeto que guarda y recupera entidades en memoria. Oculta la colección concreta que las contiene. |
| `Service` | Servicio | Objeto que coordina las operaciones del sistema (crear un `Supplier`, armar un `PurchaseOrder`) y aplica las reglas de negocio. |
| `BeforeVersion` | Versión "antes" | Implementación inicial con los defectos de diseño plantados a propósito. Tag `parcial02-antes`. |
| `AfterVersion` | Versión "después" | Implementación refactorizada, con RAII, IoC, SOLID y GRASP aplicados. Tag `parcial02-final`. |

## Términos que NO se usan

| No usar | Usar en su lugar | Motivo |
|---------|------------------|--------|
| `Product`, `Item`, `Input` | `Article` | La consigna usa "artículos"; un segundo nombre para lo mismo fragmenta el diagrama. |
| `Purchase`, `Order` | `PurchaseOrder` | `Order` a secas es ambiguo en código (orden de sorting, orden de llamada). |
| `Provider`, `Vendor` | `Supplier` | Un solo nombre para la entidad. |
| `Line`, `LineItem`, `Detail`, `OrderLine` | *(ninguno)* | **No existe una entidad de línea.** El artículo y su cantidad se guardan como un par dentro del pedido. Ver `docs/adr/0002-modelo-de-pedido.md`. |
| `Customer` | — | No existe: la empresa es la compradora, no hay clientes en el modelo. |
| `Stock`, `Inventory` | — | Fuera de alcance, ver `registro-necesidades.md`. |
