# Especificación Funcional — Parcial 02 (Productos de Goma)

> Fase 2 del trabajo. Traduce `registro-necesidades.md` (`RN`), `reglas-de-negocio.md`
> (`BR`) y `criterios-de-aceptacion.md` (`AC`) a algo que se pueda implementar y probar
> sin interpretar: **un menú, un contrato por operación, un catálogo de mensajes y un
> formato de salida**. Los tests de la fase 3 assertean los textos de este documento
> como subcadenas; por eso cada mensaje tiene identificador estable.
>
> Este documento no decide principios de diseño (eso vive en `docs/adr/`) ni el modelo
> de clases (eso vive en `docs/diagrams/`). Decide **comportamiento observable**.

## 1. Alcance

| Cubre | No cubre |
|-------|----------|
| Menú principal y opciones | Modelo de clases y sus relaciones (diagramas `.puml`) |
| Contrato de entrada/salida por operación | Esquema relacional y seed (`docs/diagrams/esquema-base.puml`, fase 3) |
| Catálogo de mensajes en español | Estrategia de errores en C++ (`ADR-0006`) |
| Formato exacto de la salida de pedidos | Historia de commits del refactoring (`ADR-0001`) |
| Reglas de lectura y normalización de entrada | Cobertura y capas de prueba (`ADR-0005`) |

## 2. Arranque

1. La aplicación abre la conexión con MariaDB y carga el catálogo de `Article` y los
   `PurchaseOrder` de demostración desde el seed (RN-018).
2. Si la conexión falla, imprime `MSG-003` y luego `MSG-004`, y termina con código
   `1` **sin mostrar el menú** (RN-017, AC-017).
3. El catálogo de artículos y los pedidos del seed son de solo lectura: el menú no
   ofrece editarlos ni eliminarlos (RN-011, AC-018).

El catálogo y los pedidos de demostración son idénticos en la versión "antes" y en la
"después": en la primera viven en código, en la segunda en `db/init/02-seed.sql`. El
comportamiento observable no cambia (ADR-0001).

## 3. Menú principal

Se imprime completo en cada iteración, precedido de una línea en blanco:

```
=== Productos de Goma — Compras de materia prima ===

1. Cargar artículo
2. Cargar proveedor
3. Listar proveedores
4. Modificar proveedor
5. Eliminar proveedor
6. Cargar pedido
7. Mostrar pedidos
0. Salir

Opción: 
```

| Opción | Operación | Requisito |
|--------|-----------|-----------|
| `1` | OP-01 Cargar artículo | RN-001 |
| `2` | OP-02 Cargar proveedor | RN-002 |
| `3` | OP-03 Listar proveedores | RN-002 |
| `4` | OP-04 Modificar proveedor | RN-002 |
| `5` | OP-05 Eliminar proveedor | RN-002, RN-009 |
| `6` | OP-06 Cargar pedido | RN-003, RN-004 |
| `7` | OP-07 Mostrar pedidos | RN-007 |
| `0` | OP-08 Salir | RN-010 |

No existe opción de edición ni de baja de artículos o pedidos (RN-011, AC-011), ni de
cambio de proveedor de un pedido ya creado (AC-006). La ausencia es la implementación
de esas reglas: no hay operación que las viole.

## 4. Reglas de lectura de entrada

Toda lectura es **una línea** (`std::getline`), recortada de espacios al inicio y al
final. Consecuencias:

| Situación | Comportamiento |
|-----------|----------------|
| Fin de entrada (EOF) en cualquier lectura | Equivale a la opción `0`: imprime `MSG-002` y termina con código `0`. Es cómo los tests terminan el bucle. |
| Opción de menú no numérica o fuera de rango | `MSG-001`, se vuelve a pedir la opción. No aborta. |
| Línea vacía donde se espera un valor obligatorio | Se valida como valor vacío (no como EOF): el error lo decide el dominio o el parseo correspondiente. |

**Frontera de responsabilidad:** los errores de **formato** los detecta `Console`
(importe, cantidad no numérica); los errores de **dominio** los detecta el dominio y
`Console` solo los traduce (`ADR-0006`).

| Dato | Formato aceptado | Rechaza | Mensaje del rechazo |
|------|------------------|---------|---------------------|
| Cantidad | entero decimal positivo: `1`, `500` | `0`, `-5` (numérico fuera de rango) | `MSG-313` |
| Cantidad | — | `1.5`, `abc`, vacío | `MSG-314` |
| Importe | `1500`, `1500,00`, `1500,5` (coma decimal, hasta 2 decimales) | `abc`, `1.500,00`, `1,234`, vacío | `MSG-114` |
| Importe | signo opcional: se acepta `-1` para que el rechazo lo decida el dominio | `-1` (negativo) | `MSG-116` |
| Fecha | `AAAA-MM-DD` exacto, 10 caracteres | otro formato | `MSG-315` |
| Fecha | fecha real del calendario (años bisiestos incluidos) | `2026-02-30`, `2026-13-01` | `MSG-316` |
| CUIT | exactamente 11 dígitos, sin guiones | `2012345678`, `20-12345678-3`, `abc` | `MSG-211` |
| Código de artículo | no vacío | línea vacía | `MSG-111` |
| Razón social | no vacía, **salvo en OP-04** | línea vacía en el alta | `MSG-213` |

Importes: se normalizan a centavos al leerlos (`"1500,5"` → `150050`) y se muestran
siempre con dos decimales y **sin separador de miles** (`1500,00`, `750000,00`), igual
que los importes de los criterios de aceptación (AC-015).

## 5. Contrato por operación

Convención: **Pre** = estado exigido; **Post** = estado resultante; **Errores** = lo
que puede rechazar la operación y el mensaje. Un rechazo no deja estado parcial: la
operación se abandona completa y el menú vuelve a mostrarse.

### OP-01 — Cargar artículo

- Traza: RN-001, BR-002, BR-003, AC-001.
- **Entrada:** código (`MSG-101`), descripción (`MSG-102`), precio unitario (`MSG-103`).
- **Pre:** el catálogo está cargado.
- **Post:** existe un `Article` con ese código y ese precio. `MSG-110`.
- **Errores:** código vacío `MSG-111`; código ya existente `MSG-112`; precio mal
  formado `MSG-114`; precio negativo `MSG-116`; precio `0` `MSG-113`.
- **No valida:** la descripción puede quedar vacía. Ninguna BR lo prohíbe y el enunciado
  no lo pide; agregarlo sería inventar una regla.

### OP-02 — Cargar proveedor

- Traza: RN-002, BR-004, BR-005, AC-002.
- **Entrada:** CUIT (`MSG-201`), razón social (`MSG-202`).
- **Pre:** —
- **Post:** existe un `Supplier` con ese CUIT. `MSG-210`.
- **Errores:** CUIT mal formado `MSG-211`; CUIT ya registrado `MSG-212`; razón social
  vacía `MSG-213`.

### OP-03 — Listar proveedores

- Traza: RN-002, AC-002.
- **Entrada:** ninguna.
- **Post:** imprime `MSG-215` y una línea `MSG-217` por proveedor, **en orden ascendente
  de CUIT** (ordinal del string de 11 dígitos). Si no hay ninguno, `MSG-216`.
- **Errores:** ninguno.

### OP-04 — Modificar proveedor

- Traza: RN-002, BR-004, BR-005, AC-002.
- **Entrada:** CUIT (`MSG-220`), nueva razón social (`MSG-221`, que muestra la actual).
- **Pre:** el CUIT existe (`MSG-214` si no).
- **Post:** la razón social queda actualizada. `MSG-222`.
- **Regla:** el **CUIT no se modifica**: es la identidad del proveedor (BR-004). La
  operación solo cambia la razón social.
- **Línea vacía** en la nueva razón social significa "conservar la actual" (idempotente,
  informa `MSG-222` igual); no puede leerse como razón social vacía porque BR-005 la
  prohíbe y no habría forma de distinguir "no cambio nada" de "ingresé vacío".
- **Errores:** CUIT inexistente `MSG-214`.

### OP-05 — Eliminar proveedor

- Traza: RN-002, RN-009, BR-009, AC-009.
- **Entrada:** CUIT (`MSG-230`).
- **Pre:** el CUIT existe (`MSG-214` si no) y no tiene pedidos asociados.
- **Post:** el proveedor deja de existir; `MSG-231`.
- **Errores:** tiene pedidos `MSG-232`, con la cantidad exacta de pedidos que lo
  referencian; el proveedor sigue existiendo.
- **No pide confirmación:** ninguna BR ni AC la exige, y AC-010 reserva "sin pedir
  confirmación adicional" para la salida. Agregarla sería inventar una interacción.

### OP-06 — Cargar pedido

- Traza: RN-003 a RN-008, RN-012 a RN-015, BR-001, BR-006, BR-007, BR-008, BR-010,
  BR-011, AC-003 a AC-008, AC-012 a AC-015.
- **Pasos, en este orden:**
  1. Pide CUIT del proveedor (`MSG-301`). Si no existe: `MSG-214`, se abandona el alta.
  2. Pide fecha de entrega esperada (`MSG-302`). Si es anterior a la fecha de creación
     (la del sistema): `MSG-317`, se abandona el alta.
  3. Repite hasta que el código de artículo venga vacío (`MSG-303`):
     - si el código **no existe** en el catálogo: `MSG-115`, **el ítem se rechaza y se
       vuelve a pedir el código** sin abortar el pedido y sin pedir cantidad (AC-008);
     - si el artículo **ya está** en el pedido: `MSG-312`, se rechaza y se vuelve a pedir
       el código, sin sumar cantidades (BR-008);
     - si el código es válido, pide cantidad (`MSG-304`). Si la cantidad es inválida:
       `MSG-313` o `MSG-314`, se rechaza el ítem y se vuelve a pedir el código;
     - si el ítem es válido, se agrega **al final** de la lista y se informa `MSG-310`.
  4. Si el pedido quedó sin ítems: `MSG-311` y **no se crea nada** (AC-004). La
     confirmación del pedido **es** el código vacío; no hay pregunta `S/N` adicional.
- **Post:** el pedido existe con `number` asignado por el repositorio (RN-012),
  `createdAt` = fecha del sistema (RN-013), `expectedDelivery` = la ingresada, el
  proveedor elegido y los ítems **en el orden en que se cargaron**. `MSG-318`.
- **Invariantes que quedan garantizadas:** BR-001, BR-006, BR-007, BR-008, BR-010,
  BR-011.
- **Errores:** proveedor inexistente `MSG-214`; fecha mal formada `MSG-315`; fecha
  inexistente `MSG-316`; fecha anterior a la creación `MSG-317`; pedido sin ítems
  `MSG-311`; artículos ítem por ítem según el paso 3.

### OP-07 — Mostrar pedidos

- Traza: RN-007, RN-015, BR-012, AC-007, AC-015.
- **Entrada:** ninguna.
- **Post:** imprime la salida del §7. Agrupa por proveedor; aparecen solo los proveedores
  **con al menos un pedido** (AC-007 permite ambas variantes y esta es la determinista);
  dentro de cada proveedor los pedidos van en orden ascendente de número; dentro de cada
  pedido los ítems en orden de carga.
- **Total:** se calcula en el momento (`Σ unitPrice × quantity`), no se almacena
  (BR-012). Si el precio del artículo cambia en el catálogo, el total mostrado cambia
  con él (AC-015).
- Si no hay ningún pedido: `MSG-406`.
- **Errores:** ninguno.

### OP-08 — Salir

- Traza: RN-010, AC-010.
- **Post:** imprime `MSG-002` y el proceso termina con código `0`, sin preguntar nada.

## 6. Catálogo de mensajes

Plantillas con `{placeholder}`. El texto en español vive **solo** acá; el dominio emite
códigos en inglés (`ADR-0006`).

### Comunes

| ID | Texto | Cuándo |
|----|-------|--------|
| `MSG-001` | `Opción inválida. Ingresá un número entre 0 y 7.` | Opción de menú no reconocida |
| `MSG-002` | `Hasta luego.` | Salida normal (opción `0` o EOF) |
| `MSG-003` | `No se pudo conectar con la base de datos: {detail}` | Fallo de conexión al arrancar |
| `MSG-004` | `Iniciá el contenedor con: docker compose up -d` | Línea siguiente a `MSG-003` |
| `MSG-005` | `=== Productos de Goma — Compras de materia prima ===` | Encabezado del menú |
| `MSG-006` | `Opción: ` | Prompt del menú |

### Artículos

| ID | Texto | Cuándo |
|----|-------|--------|
| `MSG-101` | `Código de artículo: ` | Prompt |
| `MSG-102` | `Descripción: ` | Prompt |
| `MSG-103` | `Precio unitario (por ejemplo 1500,00): ` | Prompt |
| `MSG-110` | `Artículo {code} cargado.` | Alta exitosa |
| `MSG-111` | `El código de artículo no puede estar vacío.` | BR-002 |
| `MSG-112` | `Ya existe un artículo con el código {code}.` | BR-002, unicidad |
| `MSG-113` | `El precio unitario debe ser mayor que cero.` | BR-003 |
| `MSG-114` | `Importe inválido. Usá el formato 1500,00 (coma decimal, hasta dos decimales).` | Parseo |
| `MSG-115` | `No existe un artículo con el código {code}.` | BR-007 |
| `MSG-116` | `El importe no puede ser negativo.` | Invariante de `Money` |

### Proveedores

| ID | Texto | Cuándo |
|----|-------|--------|
| `MSG-201` | `CUIT del proveedor (11 dígitos): ` | Prompt |
| `MSG-202` | `Razón social: ` | Prompt |
| `MSG-210` | `Proveedor {cuit} - {name} cargado.` | Alta exitosa |
| `MSG-211` | `El CUIT debe tener exactamente 11 dígitos numéricos.` | BR-004 |
| `MSG-212` | `Ya existe un proveedor con el CUIT {cuit}.` | BR-004, unicidad |
| `MSG-213` | `La razón social no puede estar vacía.` | BR-005 |
| `MSG-214` | `No existe un proveedor con el CUIT {cuit}.` | BR-006 |
| `MSG-215` | `Proveedores registrados:` | Encabezado del listado |
| `MSG-216` | `No hay proveedores registrados.` | Listado vacío |
| `MSG-217` | `{cuit} - {name}` | Una línea del listado |
| `MSG-220` | `CUIT del proveedor a modificar: ` | Prompt |
| `MSG-221` | `Razón social actual: {name}. Nueva razón social (Enter para conservarla): ` | Prompt |
| `MSG-222` | `Proveedor {cuit} - {name} modificado.` | Modificación exitosa |
| `MSG-230` | `CUIT del proveedor a eliminar: ` | Prompt |
| `MSG-231` | `Proveedor {cuit} - {name} eliminado.` | Baja exitosa |
| `MSG-232` | `No se puede eliminar el proveedor {cuit}: tiene {count} pedido(s) asociado(s).` | BR-009 |

### Pedidos

| ID | Texto | Cuándo |
|----|-------|--------|
| `MSG-301` | `CUIT del proveedor del pedido: ` | Prompt |
| `MSG-302` | `Fecha de entrega esperada (AAAA-MM-DD): ` | Prompt |
| `MSG-303` | `Código de artículo (Enter para terminar): ` | Prompt |
| `MSG-304` | `Cantidad: ` | Prompt |
| `MSG-310` | `Ítem agregado: {code} - {quantity}` | Ítem aceptado |
| `MSG-311` | `El pedido debe tener al menos un artículo.` | BR-007 |
| `MSG-312` | `El artículo {code} ya está en el pedido. Modificá la cantidad del ítem existente.` | BR-008 |
| `MSG-313` | `La cantidad debe ser mayor que cero.` | BR-001 |
| `MSG-314` | `Cantidad inválida. Ingresá un número entero mayor que cero, sin decimales.` | Parseo |
| `MSG-315` | `Fecha inválida. Usá el formato AAAA-MM-DD.` | Parseo de `Date` |
| `MSG-316` | `La fecha {date} no existe en el calendario.` | Calendario |
| `MSG-317` | `La fecha de entrega no puede ser anterior a la fecha de creación ({createdAt}).` | BR-011 |
| `MSG-318` | `Pedido {number} creado para {cuit} - {name}.` | Alta exitosa |

### Salida de pedidos

| ID | Texto | Cuándo |
|----|-------|--------|
| `MSG-401` | `Pedidos por proveedor` | Encabezado |
| `MSG-402` | `Proveedor: {cuit} - {name}` | Encabezado de grupo |
| `MSG-403` | `  Pedido {number} - creado {createdAt} - entrega {expectedDelivery}` | Encabezado de pedido |
| `MSG-404` | `    {code} {description}: {quantity} x {unitPrice} = {subtotal}` | Ítem |
| `MSG-405` | `  Total del pedido: {total}` | Total del pedido |
| `MSG-406` | `No hay pedidos registrados.` | Sin pedidos en el sistema |

## 7. Formato exacto de la salida de pedidos

Datos del seed (idénticos en las dos versiones del código):

| Proveedor | Pedido | Creado | Entrega | Ítems |
|-----------|--------|--------|---------|-------|
| `20234567891` Insumos Andinos S.R.L. | `2` | 2026-10-22 | 2026-11-10 | `NEG-003` × 50 |
| `27334455669` Química del Plata S.A. | — | — | — | sin pedidos |
| `30712345678` Cauchos del Sur S.A. | `1` | 2026-10-20 | 2026-11-05 | `CAU-001` × 500, `AZU-002` × 200 |
| `30712345678` Cauchos del Sur S.A. | `3` | 2026-10-25 | 2026-11-12 | `ACE-004` × 120 |

Catálogo: `CAU-001` Caucho natural `1500,00`; `AZU-002` Azufre `800,00`;
`NEG-003` Negro de humo `2200,00`; `ACE-004` Aceite de proceso `950,00`.

Salida de OP-07 con ese seed (`27334455669` **no aparece**: no tiene pedidos):

```
Pedidos por proveedor

Proveedor: 20234567891 - Insumos Andinos S.R.L.
  Pedido 2 - creado 2026-10-22 - entrega 2026-11-10
    NEG-003 Negro de humo: 50 x 2200,00 = 110000,00
  Total del pedido: 110000,00

Proveedor: 30712345678 - Cauchos del Sur S.A.
  Pedido 1 - creado 2026-10-20 - entrega 2026-11-05
    CAU-001 Caucho natural: 500 x 1500,00 = 750000,00
    AZU-002 Azufre: 200 x 800,00 = 160000,00
  Total del pedido: 910000,00
  Pedido 3 - creado 2026-10-25 - entrega 2026-11-12
    ACE-004 Aceite de proceso: 120 x 950,00 = 114000,00
  Total del pedido: 114000,00
```

Notas de formato, todas deliberadas:

- Los importes no llevan separador de miles y llevan coma decimal con dos cifras.
- Los grupos se separan con una línea en blanco; no hay línea en blanco después del
  último.
- El CUIT se muestra sin guiones, igual que se almacena y se ingresa.
- El seed crea los pedidos `1`, `2` y `3`, así que el primer pedido nuevo de una sesión
  recibe el número `4` (RN-012, AC-012).

## 8. Trazabilidad

| Operación | RN | BR | AC |
|-----------|----|----|----|
| OP-01 | RN-001, RN-011 | BR-002, BR-003 | AC-001, AC-011 |
| OP-02 | RN-002 | BR-004, BR-005 | AC-002 |
| OP-03 | RN-002 | — | AC-002 |
| OP-04 | RN-002 | BR-004, BR-005 | AC-002 |
| OP-05 | RN-002, RN-009 | BR-009 | AC-002, AC-009 |
| OP-06 | RN-003 a RN-008, RN-012 a RN-015 | BR-001, BR-006, BR-007, BR-008, BR-010, BR-011 | AC-003 a AC-008, AC-012 a AC-015 |
| OP-07 | RN-007, RN-015 | BR-012 | AC-007, AC-015 |
| OP-08 | RN-010 | — | AC-010 |
| Arranque | RN-016, RN-017, RN-018 | — | AC-016, AC-017, AC-018 |

## 9. Contrato de `Console`

La interfaz de usuario es un adaptador sin reglas de negocio. Su forma es lo que hace
testeable el resto del sistema (ADR-0003, ADR-0005):

```cpp
class Console {
public:
    Console(std::istream& in, std::ostream& out,
            SupplierService& suppliers,
            PurchaseOrderService& orders,
            const Repository<Article, std::string>& catalog);

    int run();                    // imprime el menú y despacha; código de salida

    // Una operación por opción del menú: públicas para que los tests
    // las llamen sin recorrer el bucle (el bucle queda excluido de cobertura).
    void createArticle();
    void createSupplier();
    void listSuppliers();
    void updateSupplier();
    void removeSupplier();
    void createOrder();
    void showOrders();
};
```

Reglas:

1. **Un método por opción.** `run()` solo imprime el menú, lee una línea y despacha;
   toda la lógica de cada opción vive en su método.
2. **Ningún error escapa.** Un wrapper privado (`guard(...)`) captura `DomainError`,
   pide la traducción al catálogo y la imprime. El bucle nunca recibe una excepción.
3. **EOF es salida limpia** (§4), para que un `istringstream` finito termine el bucle
   sin trucos.
4. **`Console` no conoce SQL ni repositorios mutables**: recibe los dos servicios y, del
   catálogo, solo la vista de lectura que necesita para pedir códigos.
5. El parseo de **importes** vive en `Console` (la coma decimal es presentación); el de
   **fechas** vive en `Date` (ISO no es ambiguo). `Quantity` y `Cuit` validan en su
   constructor y `Console` solo traduce el rechazo.

## 10. Decisiones registradas en esta fase

| # | Decisión | Por qué | Dónde queda |
|---|----------|---------|-------------|
| 1 | Errores con jerarquía de excepciones tipadas y catálogo de mensajes en `Console` | Los value types validan en el constructor, así que el dominio ya lanza; `Result<T>` no existe en C++17 y solo movería el `unwrap` al llamador | `ADR-0006` |
| 2 | `ValidationError` (inválido por sí solo) vs `ConflictError` (inválido contra el conjunto) vs `NotFoundError` | Separa "mal tipeado" de "ya existe" de "no existe", y hace que los tests de servicio assertean tipo, no texto | `ADR-0006` |
| 3 | El número de pedido lo asigna el repositorio **antes** del insert | El agregado tiene que validar BR-006/007/011 antes de persistirse y necesita su número para existir | Enmienda a `ADR-0004` |
| 4 | `Repository<T,K>` + `MutableRepository<T,K>`, con alias por entidad | Es el genérico que el OCP promete, sin fingir que un template esconde tres SQL | Enmiendas a `ADR-0001` y `ADR-0004` |
| 5 | `OrderNumberSequence` como puerto aparte, implementado por el repositorio de pedidos | La numeración es una capacidad de pedidos, no del `Repository` genérico; ISP sin clases gigantes | Enmienda a `ADR-0004` |
| 6 | La versión "antes" es una sola clase `App` con streams inyectados, 100 % en memoria | Es el borde de comportamiento estable que permite escribir la suite sobre "antes", y MariaDB entra cuando DIP crea el puerto | Enmiendas a `ADR-0001` y `ADR-0005` |
| 7 | La confirmación de un pedido es el código de artículo vacío, sin `S/N` | AC-004 solo exige rechazar el pedido sin ítems; un paso extra alarga todos los guiones de test sin agregar una regla | Este documento |
| 8 | La baja de proveedor no pide confirmación | Ninguna BR ni AC la pide; AC-010 reserva "sin confirmación" para la salida | Este documento |
| 9 | La descripción de un artículo puede ser vacía | BR-002 solo prohíbe código vacío; agregar la restricción sería inventar una regla | Este documento |
| 10 | Un proveedor sin pedidos no aparece en OP-07 | AC-007 admite las dos variantes; esta es la que no depende del orden de inserción | Este documento |
| 11 | Orden determinista: proveedores por CUIT ascendente, pedidos por número ascendente, ítems por orden de carga | Sin orden explícito la salida no es asserteable y RN-007 pide el orden de carga de los ítems | Este documento |
| 12 | Reloj inyectable en `PurchaseOrderService` (`std::function<Date()>`, por defecto `Date::today`) | AC-013 y AC-014 dependen de "hoy"; sin puerto los tests de fecha dependen del día en que corren | Este documento |
| 13 | Importes sin separador de miles, coma decimal, dos cifras | Es el formato de los AC (AC-001, AC-015) y no requiere configuración regional | Este documento |

## 11. Qué no hace el sistema

Lista corta de ausencias **deliberadas**, para que no se lean como olvidos. Traza a
`registro-necesidades.md` §Fuera de alcance:

- No edita ni elimina artículos (RN-011).
- No edita ni elimina pedidos, ni cambia el proveedor de un pedido creado (RN-011,
  AC-006).
- No gestiona stock, estados de pedido, recepción de mercancía ni precios históricos
  (BR-012).
- No tiene usuarios, roles ni autenticación.
- No tiene migraciones: el esquema y el seed se aplican al crear el volumen.
