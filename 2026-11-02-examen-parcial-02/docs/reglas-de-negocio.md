# Reglas de Negocio — Parcial 02 (Productos de Goma)

> Reglas que el dominio impone por sí mismo, independientes de la interfaz y del
> almacenamiento. Cada regla traza a los requisitos de `registro-necesidades.md` y se
> verifica en `criterios-de-aceptacion.md`.
>
> Una regla de negocio no es un requisito funcional: el requisito pide *qué* debe poder
> hacer el sistema; la regla fija *qué no puede ser verdad* en ningún estado del sistema.
> La columna **Se hace cumplir en** indica dónde se vuelve imposible violarla, para que
> la regla no dependa de que cada punto de uso se acuerde de validarla.

## Catálogo de reglas

| ID | Regla | Tipo | Origen | Se hace cumplir en |
|----|-------|------|--------|--------------------|
| BR-001 | La cantidad de un artículo en un pedido es mayor que cero. | Invariante | RN-005 | `Quantity` (constructor) |
| BR-002 | El código de un artículo no es vacío y es único dentro del catálogo. | Invariante | RN-001 | `Article` + `ArticleRepository` |
| BR-003 | El precio unitario de un artículo es mayor que cero. | Invariante | RN-001 | `Money` + `Article` |
| BR-004 | El CUIT de un proveedor tiene exactamente 11 dígitos numéricos y es único entre proveedores. | Invariante | RN-002 | `Cuit` (constructor) + `SupplierRepository` |
| BR-005 | La razón social de un proveedor no es vacía. | Invariante | RN-002 | `Supplier` |
| BR-006 | Un pedido referencia exactamente un proveedor, y ese proveedor existe. | Invariante | RN-003, RN-006, RN-008 | `PurchaseOrder` + `PurchaseOrderService` |
| BR-007 | Un pedido tiene al menos un artículo, y todos los artículos referenciados existen en el catálogo. | Invariante | RN-004, RN-008 | `PurchaseOrder` + `PurchaseOrderService` |
| BR-008 | Un artículo aparece como máximo una vez por pedido. | Invariante | RN-004 (derivada) | `PurchaseOrderService` |
| BR-009 | No se elimina un proveedor que tenga pedidos asociados. | Prohibición | RN-009 | `SupplierService` |
| BR-010 | El número de pedido es único, se autogenera y nunca se reutiliza. | Invariante | RN-012 | `PurchaseOrderRepository` |
| BR-011 | La fecha de entrega esperada no es anterior a la fecha de creación del pedido. | Invariante | RN-014 | `Date` + `PurchaseOrderService` |
| BR-012 | El total de un pedido es la suma de `unitPrice × quantity` de sus ítems y no se almacena. | Derivada | RN-015 | `PurchaseOrder::total()` |

## Detalle de las reglas no obvias

### BR-002 — Unicidad del código de artículo

La unicidad no puede vivir en `Article`: dos objetos distintos con el mismo `code`
serían ambos válidos por separado. Vive en el repositorio, que es quien conoce el
conjunto completo. El constructor de `Article` solo garantiza que el código no sea
vacío.

### BR-004 — El CUIT como identidad del proveedor

El CUIT es lo que identifica a un proveedor en la realidad, así que se usa como clave
del repositorio. Se valida en el tipo (`Cuit`) y no en el servicio: un `Cuit` con 10
dígitos no puede existir, igual que un `Quantity` igual a cero (ADR-0002). La unicidad
sí requiere el conjunto completo y queda en `SupplierRepository`.

### BR-008 — Un artículo, una vez por pedido

Si el operador carga el mismo artículo dos veces en un pedido, el sistema **rechaza la
segunda carga** y pide modificar la cantidad existente. Alternativa descartada:
sumar las cantidades automáticamente, que hace que un error de tipeo (`5` y `50`) pase
desapercibido y produzca un pedido por 55 unidades.

> Decisión tomada al redactar esta fase, sin contraparte explícita en el enunciado. Si
> se prefiere la suma automática, cambia esta regla y el AC-004, no el modelo.

### BR-009 — Baja de proveedor con pedidos

Borrar un proveedor con pedidos dejaría pedidos apuntando a un proveedor inexistente,
o sea un estado inválido. El sistema informa la cantidad de pedidos asociados y no
ejecuta la baja. Alternativa descartada: borrado en cascada, que destruye pedidos que
son la salida principal del sistema.

### BR-012 — El total es derivado

`PurchaseOrder` no guarda un campo `total`. Guardarlo obliga a recalcularlo en cada
alta, baja o cambio de cantidad, y abre la puerta a que el campo y los ítems se
contradigan. Se calcula al mostrarlo. Consecuencia aceptada: si el precio unitario del
artículo cambia en el catálogo, el total de un pedido viejo cambia con él, porque no
hay histórico de precios (ver ADR-0002, enmienda).
