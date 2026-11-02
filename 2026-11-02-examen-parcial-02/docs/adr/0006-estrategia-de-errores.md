# ADR-0006 — Errores de dominio con excepciones tipadas y textos en la consola

- **Estado:** aceptada
- **Fecha:** 2026-11-02
- **Relacionada:** `ADR-0002` (value types con invariantes), `ADR-0003` (`Console`),
  `ADR-0005` (estrategia de pruebas)

## Contexto

Las reglas de negocio se hacen cumplir en tres lugares distintos: los value types
validadas en el constructor (BR-001, BR-004, BR-011), los repositorios que conocen el
conjunto completo (unicidad de BR-002 y BR-004) y los servicios que coordinan
(BR-009). Todas esas capas tienen que **rechazar** operaciones, y la interfaz tiene que
informar el motivo en español (RNF-007) sin que el dominio sepa de textos.

El rechazo puede ocurrir en un constructor, y un constructor no puede devolver un valor
alternativo. Eso ya está decidido en `ADR-0002`: `Quantity(0)`, `Cuit("123")` y
`Date("2026-02-30")` no construyen un objeto válido. Cualquier estrategia de errores
tiene que convivir con esa decisión.

C++17 no tiene `std::expected`; sí tiene excepciones, y RAII hace que sean seguras de
propagar.

## Decisión

**Excepciones tipadas de tres clases, con un código estable en inglés; los textos en
español viven solo en el catálogo de la consola.**

```cpp
enum class ErrorCode {
    // Invariante del valor o de la operación
    EmptyArticleCode, NonPositiveUnitPrice, NegativeMoney, EmptyBusinessName, CuitFormat,
    NonPositiveQuantity, DateFormat, InvalidCalendarDate, DeliveryBeforeCreation,
    EmptyOrder,
    // Clave inexistente
    UnknownArticle, UnknownSupplier,
    // Depende del conjunto, no del valor solo
    DuplicateArticleCode, DuplicateCuit, DuplicateArticleInOrder, SupplierHasOrders
};

using Fields = std::map<std::string, std::string>;

class DomainError : public std::runtime_error {
public:
    DomainError(ErrorCode code, Fields fields = {});
    ErrorCode code() const noexcept;
    const Fields& fields() const noexcept;
};

class ValidationError : public DomainError {};   // mal por sí solo
class NotFoundError   : public DomainError {};   // la clave no existe
class ConflictError   : public DomainError {};   // válido solo, inválido contra el conjunto
```

`MessageCatalog::translate(const DomainError&)` convierte `(code, fields)` en la
plantilla `MSG-###` correspondiente de `docs/especificacion-funcional.md` y sustituye los
`{placeholder}`. El dominio nunca arma una oración en español; `Console` nunca decide si
algo es válido.

**La distinción entre las tres clases no es cosmética:**

| Clase | Criterio | Ejemplo |
|-------|----------|---------|
| `ValidationError` | El valor está mal **por sí solo**, sin mirar el resto del sistema | `Quantity(0)`, CUIT de 10 dígitos, entrega anterior a la creación |
| `NotFoundError` | El valor está bien formado pero **no existe** | CUIT `20111111112` sin proveedor |
| `ConflictError` | El valor está bien formado y existe, pero **choca con el estado** | código de artículo repetido, artículo repetido en el pedido, proveedor con pedidos |

La frontera es lo que hace que cada rechazo tenga un lugar único: no se valida dos veces
ni se olvida una vez.

**Errores de formato no son errores de dominio.** `Console` es quien parsea el importe
tipeado (`"1500,00"`) y quien detecta que no es un número; no hay excepción para eso,
hay un mensaje directo (`MSG-114`, `MSG-314`). El dominio solo ve valores ya
convertidos.

## Alternativas descartadas

**`Result<T>` / `expected` hecho a mano.** Descartada por dos motivos. El primero es
mecánico: C++17 no lo trae y el curso no tiene esa convención, así que habría que
inventar el vocabulario. El segundo es de diseño: los value types validan en el
constructor (`ADR-0002`), y un constructor no puede devolver `Result<T>` sin convertirse
en factory (`Quantity::make(...)`). Adoptarlo solo movería el `unwrap` a cada llamador y
dejaría el modelo con dos formas de fallar.

**Códigos de error con `bool` y parámetro de salida.** Descartada: contamina todas las
firmas, se puede ignorar el retorno en silencio y no hay forma de transportar el valor
ofensor sin agregar un `out` por cada dato.

**La excepción lleva el mensaje en español.** Descartada: mete texto de interfaz en el
dominio, obliga a que el dominio conozca los formatos de la UI y hace que cualquier
cambio de redacción toque capas que no deberían moverse. Con el catálogo separado, los
tests de servicio assertean el `ErrorCode` y los de consola el texto, que es la misma
separación que `ADR-0005` necesita para sobrevivir al refactoring.

**Excepciones por clase de entidad (`SupplierError`, `ArticleError`).** Descartada:
multiplica las jerarquías sin agregar información; el `ErrorCode` ya dice qué pasó y el
`Fields` ya dice con qué.

## Consecuencias

- Cada rechazo tiene un tipo y un código. El catálogo de mensajes es finito, testeable y
  vive en un solo archivo: agregar un mensaje es agregar una fila y una rama, no tocar
  el dominio.
- Los servicios documentan sus excepciones en el contrato de operación
  (`docs/especificacion-funcional.md` §5), no en comentarios sueltos.
- `Console` necesita un wrapper que capture `DomainError` una sola vez
  (`guard(...)`); sin él, cada método de operación repetiría el mismo `try/catch`.
- Ninguna excepción escapa del bucle del menú: el `main` solo atrapa el fallo de
  conexión inicial (RN-017), que es infraestructura y no dominio.
- `Fields` es un `std::map<std::string, std::string>`: suficiente para los mensajes con
  uno o dos placeholders (`{cuit}`, `{count}`, `{createdAt}`) sin inventar un tipo por
  mensaje.
