# ADR-0002 — La cantidad es un value type y no existe entidad de línea

- **Estado:** aceptada
- **Fecha:** 2026-11-02
- **Relacionada:** `ADR-0001` (demostración del refactoring)

## Contexto

La consigna pide cargar "Pedidos de Artículos Asignados a los Proveedores" y mostrar
"los pedidos de los artículos". **No menciona cantidades**, y el PDF original cierra
con una nota explícita: *"No 'haga' de más, tampoco de 'Menos'"*.

Al mismo tiempo, un pedido de compra sin cantidades no representa el caso real: no
distingue pedir 5 unidades de caucho de pedir 500. Se decidió priorizar la fidelidad
al caso real, aceptando que la cantidad es una extensión consciente del enunciado y
no un requisito literal.

Quedaba abierto **cómo** modelarla: dentro del pedido como atributo, como entidad
propia, o como tipo con invariantes.

## Decisión

`PurchaseOrder` referencia un `Supplier` y guarda sus artículos como pares:

```cpp
class PurchaseOrder {
    const Supplier* supplier;
    std::vector<std::pair<const Article*, Quantity>> items;
};
```

`Quantity` es un **value type** que valida en su constructor y no admite valores
menores o iguales a cero. Un `Quantity` inválido no puede existir.

```cpp
class Quantity {
public:
    explicit Quantity(unsigned value);   // rechaza 0
    unsigned value() const noexcept;
};
```

**No se introduce** `OrderLine`, `Renglón`, `LineItem` ni equivalente.

## Alternativas descartadas

**A. Sin cantidades** — `std::vector<const Article*>`. Es la lectura más literal del
enunciado y la más segura frente a la nota del PDF. Descartada porque pierde el caso
real: un pedido de compra sin magnitud no es un pedido de compra.

**B. Cantidad como `unsigned` suelto** en el par. Descartada por dos motivos: permite
el `0` y obliga a revalidar en cada punto de uso. Mover la regla al tipo la valida una
sola vez y hace imposible el estado inválido, que es precisamente lo que el trabajo
quiere demostrar con RAII.

**C. Entidad de línea (`OrderLine`) con `article` y `quantity`.** Descartada: la
consigna no la nombra, y con dos campos no se justifica una clase. La nota del PDF
apunta directo a no agregarla. Si en el futuro una línea necesitara precio,
descuento o número de posición, esta decisión habría que revisarla.

## Consecuencias

- El par `pair<const Article*, Quantity>` **preserva el orden de carga**, lo que
  importa para RN-007 (mostrar los pedidos). Un `std::map` ordenaría por clave y, con
  punteros como clave, por dirección de memoria.
- El puntero es **no propietario**: el pedido no es dueño de los artículos, el
  catálogo sí. Por eso el refactoring de RAII aplica al catálogo
  (`vector<unique_ptr<Article>>`), no a las referencias del pedido. Dos pedidos deben
  poder referenciar el mismo `Article`.
- `Quantity` obliga a que `PurchaseOrder` y la interfaz de consola no dupliquen la
  validación de rangos.
- Si se agregara un precio por artículo pedido, el par deja de alcanzar y habría que
  migrar a una estructura con nombre. Es un costo aceptado a cambio de no crear hoy
  una clase que la consigna no pide.
