# Glosario de Dominio — Parcial 02 (Productos de Goma)

> Nomenclatura del sistema. Los **identificadores de código son en inglés**; los textos
> de la futura interfaz de usuario y la documentación se mantienen en español.
> La columna "Término en la consigna" mantiene la trazabilidad con el enunciado.

## Términos del dominio

| Término (código) | Término en la consigna | Definición |
|------------------|------------------------|------------|
| `Article` | Artículo | Unidad de materia prima que la empresa compra. Es lo que se carga en el sistema y lo que se pide a un proveedor. Tiene `code`, `description` y `unitPrice`. |
| `RawMaterial` | Materia Prima | El insumo físico que la empresa transforma en productos de goma (caucho, azufre, negro de humo, aceite). **No** es un tipo propio: se modela como `Article`. |
| `Supplier` | Proveedor | Empresa a la que se le compra materia prima. Es la única entidad con CRUD completo en esta versión. Tiene `cuit` y `businessName`. |
| `PurchaseOrder` | Pedido | Solicitud de compra de uno o más `Article`, asignada a **un único** `Supplier`. Tiene `number`, `supplier`, `createdAt`, `expectedDelivery` y sus ítems. Es el objeto que el sistema muestra por consola. |
| `Quantity` | Cantidad | Value type inmutable que representa unidades de un `Article` dentro de un pedido. Garantiza en su constructor que el valor sea mayor que cero, así que un `Quantity` inválido no puede existir. |
| `UnitPrice` | Precio unitario | Importe de una unidad de `Article`, en pesos argentinos. Es `Money` y vive en el artículo, no en el pedido. |
| `Money` | Importe | Value type inmutable que representa dinero en centavos con entero de 64 bits. No admite punto flotante y no conoce moneda: el sistema opera en ARS. |
| `Total` | Total del pedido | Importe derivado de un `PurchaseOrder`: la suma de `unitPrice × quantity` de sus ítems. No se almacena. |
| `Date` | Fecha | Value type que representa un día calendario (día, mes, año). Parsea y valida `AAAA-MM-DD` y rechaza fechas inexistentes como `2026-02-30`. |
| `OrderNumber` | Número de pedido | Identificador único y autogenerado de un `PurchaseOrder`. Es la clave con la que se lo nombra y se lo busca. |
| `Cuit` | CUIT | Clave tributaria de un `Supplier`: exactamente 11 dígitos numéricos. Es su identidad en el sistema. |
| `CRUD` | CRUD | Alta, lectura, modificación y baja de una entidad. Solo `Supplier` lo tiene completo. |
| `Seed` | Hardcodeado / datos iniciales | Datos versionados que pueblan la base al crearse: catálogo de `Article` y pedidos de demostración. Reemplaza a los datos definidos en el código de la versión inicial. |

## Términos técnicos del diseño

| Término (código) | Término en la consigna | Definición |
|------------------|------------------------|------------|
| `Console` | Consola | Interfaz de usuario: lee opciones y escribe resultados por terminal. Recibe sus streams por constructor y no conoce reglas de negocio ni almacenamiento. |
| `Repository` | Repositorio | Interfaz **genérica** (`Repository<T, K>`) que guarda y recupera entidades por clave, ocultando si el almacenamiento es memoria o MariaDB. `MutableRepository<T, K>` es la variante que además modifica y elimina. |
| `SupplierOrders` | — | Vista de lectura que agrupa los pedidos de un proveedor para mostrarlos (RN-007). No es una entidad del dominio: se arma en cada consulta y no se persiste. |
| `OrderNumberSequence` | — | Puerto que entrega el siguiente `OrderNumber` **antes** de persistir el pedido. Lo implementan el repositorio MariaDB y un doble en memoria. |
| `Clock` | — | Puerto que devuelve la fecha del sistema. Se inyecta para que las pruebas de fecha no dependan del día en que corren. |
| `MessageCatalog` | — | Catálogo de textos en español: traduce un `DomainError` a la línea `MSG-###` que ve el operador. |
| `Service` | Servicio | Objeto que coordina las operaciones del sistema (crear un `Supplier`, armar un `PurchaseOrder`) y aplica las reglas de negocio. |
| `Persistence` | Persistencia | Almacenamiento durable en MariaDB. En esta versión aplica a `Supplier`; `Article` y `PurchaseOrder` se leen del seed. |
| `Docker` | — | Plataforma que sirve el contenedor de MariaDB con su esquema y seed. |
| `Coverage` | Cobertura | Porcentaje de líneas de código ejecutadas por las pruebas, medido con `gcov`/`gcovr` sobre `src/`. |
| `TUI` | — | Interfaz de terminal con pantalla completa y control de cursor. Descartada para esta versión (ADR-0003). |
| `BeforeVersion` | Versión "antes" | Implementación inicial con los defectos de diseño plantados a propósito. Tag `parcial02-antes`. |
| `AfterVersion` | Versión "después" | Implementación refactorizada, con RAII, IoC, SOLID y GRASP aplicados. Tag `parcial02-final`. |

## Términos que NO se usan

| No usar | Usar en su lugar | Motivo |
|---------|------------------|--------|
| `Product`, `Item`, `Input` | `Article` | La consigna usa "artículos"; un segundo nombre para lo mismo fragmenta el diagrama. |
| `Purchase`, `Order` | `PurchaseOrder` | `Order` a secas es ambiguo en código (orden de sorting, orden de llamada). |
| `Provider`, `Vendor` | `Supplier` | Un solo nombre para la entidad. |
| `Line`, `LineItem`, `Detail`, `OrderLine` | *(ninguno)* | **No existe una entidad de línea.** El artículo y su cantidad se guardan como un par dentro del pedido. Ver `docs/adr/0002-modelo-de-pedido.md`. |
| `Price` suelto, `float`, `double` para dinero | `Money` / `UnitPrice` | El dinero en punto flotante acumula error de redondeo; `Money` en centavos lo hace imposible. |
| `Result`, `expected`, código de error devuelto | *(ninguno)* | El dominio rechaza con excepciones tipadas: los value types validan en el constructor y no pueden devolver un valor alternativo (`ADR-0006`). |
| `Customer` | — | No existe: la empresa es la compradora, no hay clientes en el modelo. |
| `Stock`, `Inventory` | — | Fuera de alcance, ver `registro-necesidades.md`. |
