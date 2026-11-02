# Criterios de Aceptación — Parcial 02 (Productos de Goma)

> Un bloque por requisito funcional de `registro-necesidades.md`. Cada bloque nombra el
> `RN-###` que verifica y las `BR-###` que lo respaldan, de modo que la referencia
> funcione en los dos sentidos: del requisito a su aceptación y de la aceptación al
> requisito y a la regla.
>
> Formato: **Dado** (estado inicial) — **Cuando** (acción) — **Entonces** (resultado
> observable). Son la especificación de la que salen los tests de las fases
> posteriores; ningún criterio menciona clases ni funciones concretas.

## RN-001 — Alta de artículo

**AC-001** · Reglas: BR-002, BR-003

- **Dado** un catálogo sin el código `CAU-001`, **cuando** el operador carga
  `CAU-001 / Caucho natural / 1500,00`, **entonces** el artículo queda en el catálogo
  con precio unitario `1500,00`.
- **Dado** un catálogo que ya tiene `CAU-001`, **cuando** se intenta cargar otro
  artículo con ese código, **entonces** el alta se rechaza y se informa el código
  duplicado.
- **Dado** un precio unitario de `0` o negativo, **cuando** se intenta cargar el
  artículo, **entonces** el alta se rechaza y no se crea ningún artículo.

## RN-002 — CRUD de proveedores

**AC-002** · Reglas: BR-004, BR-005, BR-009

- **Dado** un CUIT válido no registrado, **cuando** el operador da de alta el
  proveedor, **entonces** queda disponible para asignarle pedidos.
- **Dado** un CUIT de 10 dígitos o con letras, **cuando** se intenta el alta,
  **entonces** se rechaza y se informa el formato esperado.
- **Dado** un proveedor existente, **cuando** el operador modifica su razón social,
  **entonces** el cambio se ve al listar proveedores y al mostrar sus pedidos.
- **Dado** un proveedor sin pedidos, **cuando** el operador lo elimina, **entonces**
  deja de aparecer en el listado.
- **Dado** un proveedor con al menos un pedido, **cuando** el operador intenta
  eliminarlo, **entonces** la baja se rechaza, se informa cuántos pedidos lo
  referencian y el proveedor sigue existiendo.

## RN-003 — Alta de pedido asignado a un proveedor

**AC-003** · Reglas: BR-006

- **Dado** un proveedor existente, **cuando** el operador crea un pedido para él,
  **entonces** el pedido queda asociado a ese proveedor.
- **Dado** un CUIT que no existe, **cuando** el operador intenta crear el pedido,
  **entonces** se rechaza y se informa que el proveedor no existe.

## RN-004 — Ítems del pedido

**AC-004** · Reglas: BR-007, BR-008

- **Dado** un pedido en carga, **cuando** el operador agrega `CAU-001` con cantidad
  `500`, **entonces** el pedido contiene ese artículo con esa cantidad.
- **Dado** un pedido sin ítems, **cuando** se intenta confirmarlo, **entonces** se
  rechaza y se informa que el pedido debe tener al menos un artículo.
- **Dado** un pedido que ya contiene `CAU-001`, **cuando** el operador agrega otra vez
  `CAU-001`, **entonces** se rechaza la segunda carga e invita a modificar la cantidad
  existente.

## RN-005 — Cantidad válida

**AC-005** · Reglas: BR-001

- **Dado** un pedido en carga, **cuando** el operador ingresa cantidad `0`, **entonces**
  se rechaza y el pedido no cambia.
- **Dado** un pedido en carga, **cuando** el operador ingresa cantidad `-5`,
  **entonces** se rechaza y el pedido no cambia.
- **Dado** un pedido en carga, **cuando** el operador ingresa cantidad `1`, **entonces**
  el artículo se agrega con cantidad `1`.

## RN-006 — Un proveedor por pedido

**AC-006** · Reglas: BR-006

- **Dado** un pedido ya creado para un proveedor, **cuando** el operador intenta
  asignarle un segundo proveedor, **entonces** la operación no existe en el sistema:
  el pedido no ofrece cambiar de proveedor después de creado.

## RN-007 — Mostrar pedidos por proveedor

**AC-007** · Reglas: BR-012

- **Dado** dos proveedores con pedidos, **cuando** el operador pide mostrar los
  pedidos, **entonces** la salida agrupa los pedidos bajo cada proveedor y, dentro de
  cada pedido, lista sus artículos en el orden en que se cargaron, con cantidad,
  precio unitario y subtotal.
- **Dado** un proveedor sin pedidos, **cuando** se muestran los pedidos, **entonces**
  ese proveedor aparece sin pedidos o no aparece, pero el sistema no falla.
- **Dado** un pedido con dos ítems, **cuando** se muestra, **entonces** se muestra su
  total como la suma de los subtotales.

## RN-008 — Referencias inexistentes

**AC-008** · Reglas: BR-006, BR-007

- **Dado** un pedido en carga, **cuando** el operador agrega un código de artículo que
  no existe, **entonces** se rechaza el ítem y se informa el código buscado.
- **Dado** un proveedor inexistente, **cuando** se intenta crear un pedido,
  **entonces** se rechaza y se informa el motivo.

## RN-009 — Baja de proveedor con pedidos

**AC-009** · Reglas: BR-009

- **Dado** un proveedor con pedidos, **cuando** el operador elige eliminarlo,
  **entonces** el sistema informa cuántos pedidos lo referencian y no borra nada.

## RN-010 — Salida del menú

**AC-010**

- **Dado** el menú principal, **cuando** el operador elige la opción de salida,
  **entonces** el programa termina con código `0` y sin pedir confirmación adicional.

## RN-011 — Alcance del CRUD

**AC-011**

- **Dado** el menú principal, **cuando** el operador lo recorre, **entonces** las
  únicas operaciones de modificación y baja disponibles son sobre proveedores; los
  artículos y los pedidos solo se consultan y se cargan.

## RN-012 — Número de pedido

**AC-012** · Reglas: BR-010

- **Dado** un sistema recién iniciado con pedidos sembrados, **cuando** se crea un
  pedido nuevo, **entonces** recibe un número que no estaba en uso.
- **Dado** dos pedidos creados en la misma sesión, **cuando** se muestran,
  **entonces** sus números son distintos.

## RN-013 — Fecha de creación

**AC-013**

- **Dado** que el operador crea un pedido, **cuando** el pedido queda creado,
  **entonces** su fecha de creación es la fecha del sistema en ese momento y no se
  puede editar.

## RN-014 — Fecha de entrega esperada

**AC-014** · Reglas: BR-011

- **Dado** un pedido nuevo, **cuando** el operador ingresa una fecha de entrega
  posterior a hoy en formato `AAAA-MM-DD`, **entonces** el pedido la registra y se
  muestra junto con el pedido.
- **Dado** un pedido nuevo, **cuando** el operador ingresa una fecha anterior a la de
  creación, **entonces** se rechaza y se informa el motivo.
- **Dado** un pedido nuevo, **cuando** el operador ingresa `2026-02-30`, **entonces**
  se rechaza por fecha inexistente.

## RN-015 — Total del pedido

**AC-015** · Reglas: BR-012

- **Dado** un pedido con `CAU-001 × 2` a `1500,00` y `AZU-002 × 3` a `800,00`,
  **cuando** se muestra, **entonces** los subtotales son `3000,00` y `2400,00` y el
  total es `5400,00`.
- **Dado** que el precio de `CAU-001` cambia en el catálogo, **cuando** se vuelve a
  mostrar el mismo pedido, **entonces** el total refleja el precio nuevo.

## RN-016 — Persistencia de proveedores

**AC-016**

- **Dado** un proveedor dado de alta, **cuando** se cierra la aplicación y se vuelve a
  iniciar, **entonces** el proveedor sigue existiendo con los mismos datos.
- **Dado** un proveedor modificado, **cuando** se reinicia la aplicación,
  **entonces** se ve la versión modificada y no la anterior.
- **Dado** un proveedor eliminado, **cuando** se reinicia la aplicación, **entonces**
  ya no existe.

## RN-017 — Base de datos no disponible

**AC-017**

- **Dado** que el contenedor de MariaDB no está corriendo, **cuando** se inicia la
  aplicación, **entonces** se informa el error de conexión por consola y el proceso
  termina con código distinto de `0`, sin mostrar el menú.

## RN-018 — Datos sembrados

**AC-018**

- **Dado** un entorno recién levantado con `docker compose up`, **cuando** se inicia
  la aplicación, **entonces** el catálogo tiene los artículos del seed y existen los
  pedidos de demostración con sus números.
- **Dado** el menú principal, **cuando** el operador busca editar o eliminar un
  artículo o un pedido, **entonces** esas opciones no existen.
