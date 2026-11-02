# ADR-0001 — Demostrar el antes/después con tags y commits por principio

- **Estado:** aceptada
- **Fecha:** 2026-11-02
- **Contexto:** RNF-005 exige demostrar el antes y el después de aplicar RAII, IoC,
  SOLID y GRASP. La evidencia es el historial lineal del repositorio y, en particular,
  sus tags.

## Decisión

La demostración del refactoring vive en el **historial lineal de `main`**, no en
branches paralelos:

1. La versión inicial se escribe con los defectos de diseño plantados a propósito.
2. Se marca con el tag `parcial02-antes`.
3. Se aplica **un commit por principio**, en orden: RAII → SRP → DIP/IoC → OCP →
   Information Expert.
4. Se marca la versión final con el tag `parcial02-final`.
5. La evidencia se indexa en `docs/refactoring.md` y en dos diagramas de clases,
   `clases-antes.puml` y `clases-despues.puml`.

El tag `parcial02-antes` marca el punto exacto del código a inspeccionar, y
`git diff parcial02-antes..parcial02-final` da el diff completo sin que nadie tenga
que reconstruirlo.

## Defectos plantados en la versión "antes"

Estos defectos no son accidentes: se eligen de antemano para que el "después"
tenga algo concreto que corregir. La consigna habilita el primero de ellos al
permitir que artículos y pedidos estén hardcodeados.

| # | Defecto en "antes" | Refactoring en "después" | Principio |
|---|--------------------|--------------------------|-----------|
| 1 | `new Supplier*` con `delete` manual y riesgo de fuga | `std::vector<std::unique_ptr<Supplier>>` | RAII |
| 2 | Una clase que hace entrada/salida, almacenamiento y validación a la vez | División en `Console`, `Repository` y `Service` | SRP / GRASP Controller |
| 3 | El `Service` instancia `new InMemorySupplierRepository()` adentro | Inyección por constructor | DIP / IoC |
| 4 | Almacenamiento y búsqueda por código reescritos a mano en cada entidad | `Repository<T>` reutilizable; las tres entidades la usan sin modificarse | OCP |
| 5 | `cout` de pedidos disperso en `main` | `PurchaseOrder::show()` / `operator<<` | GRASP Information Expert |

## Alternativas descartadas

**Branch de comparación vivo** (`parcial-02-sin-refactor` mantenido sin refactorizar,
`main` refactorizado). Descartada: al integrar el estado sin refactorizar a `main` y
luego refactorizar encima, `main` ya contiene ambos estados en su historia y el branch
resulta redundante — es `main~N`. Además exige escribir el resumen de diffs a mano igual.

**Dos árboles de código** (`src/antes/` y `src/despues/`, compilables por separado).
Descartada: duplica el mantenimiento y hace parecer que se escribieron dos programas
distintos en lugar de refactorizar uno.

**Un único commit grande de refactoring.** Descartada por la más grave: un diff de
cientos de líneas no permite atribuir ningún cambio a ningún principio, que es
exactamente lo que el RNF-005 pide demostrar.

**Solo diagramas, sin historia en git.** Descartada como estrategia principal, pero
se conserva como complemento: los dos `.puml` son parte de la demostración porque el
enunciado dice "en diagrama **o** código", y tener ambos es más fuerte que uno.

## Consecuencias

- La historia de `main` no se reescribe nunca: los tags quedan estables y enlazables.
- Cada commit de refactoring debe ser **atribuible a un único principio**, lo que
  obliga a un orden de trabajo disciplinado y a no mezclar mejoras.
- El lector necesita un punto de entrada; sin `docs/refactoring.md` los tags son
  arqueología. Ese archivo es parte de la decisión, no un extra.
- Los diagramas `.svg` se commitean renderizados para que se vean al navegar el
  repositorio.

## Enmienda 2026-11-02 — alcance del genérico, forma del "antes" y sexto commit

La fase de diseño conservó la decisión de fondo (historial lineal, tags, un commit por
principio) y precisó cuatro cosas que la tabla de defectos dejaba implícitas. Sin esta
enmienda, dos de los cinco refactorings no serían implementables.

**1. El defecto #4 vive del lado del almacenamiento y de la interfaz, no del SQL.** Un
template no puede esconder tres sentencias SQL distintas; el genérico es el contrato, y
cada entidad tiene su adaptador:

```cpp
template <class T, class K>
class Repository {                       // find / all / add
public:
    virtual ~Repository() = default;
    virtual std::optional<T> find(const K& key) const = 0;
    virtual std::vector<T> all() const = 0;
    virtual void add(const T& entity) = 0;
};

template <class T, class K>
class MutableRepository : public Repository<T, K> {   // + update / remove
public:
    virtual void update(const T& entity) = 0;
    virtual void remove(const K& key) = 0;
};
```

`InMemoryRepository<T, K>` implementa las dos interfaces con un extractor de clave;
`MariaDbSupplierRepository`, `MariaDbArticleRepository` y
`MariaDbPurchaseOrderRepository` implementan la de su entidad. El OCP se demuestra
agregando los repositorios de `Article` y de `PurchaseOrder` **sin tocar el template ni
`InMemoryRepository`**. La corrección de fondo es que "las tres entidades usan
`Repository<T>` sin modificarse" describe el **contrato**, no la implementación SQL.
Detalle en la enmienda de `ADR-0004`.

**2. El "antes" es una sola clase `App` con los streams inyectados.** Sin un borde de
comportamiento estable no hay dónde agarrar la suite que `ADR-0005` exige escribir
sobre el "antes": si la lógica vive dentro de `main`, los tests solo pueden invocar
`main()`. `App(std::istream&, std::ostream&)` es ese borde, y **no es uno de los cinco
refactorings**: se documenta como punto de partida en `docs/refactoring.md`, porque
permanece idéntico antes y después. Dentro de `App` conviven el menú, el almacenamiento,
la validación y el formateo, con tres bloques de búsqueda por clave copiados a mano (el
defecto #4 en forma embrionaria) y el formateo de pedidos en su propio `showOrders()`
(el defecto #5). `main` solo construye `App`.

**3. El "antes" es 100 % en memoria y MariaDB entra como sexto commit.** El propio
defecto #3 dice que el defecto es que el servicio instancia
`new InMemorySupplierRepository()`. Si el "antes" hablara con MariaDB, las unitarias de
servicio que `ADR-0005` exige exigirían Docker y el refactoring de DIP no tendría un
puerto que crear. Además la consigna habilita lo hardcodeado y RN-016 es una ampliación
posterior. La persistencia necesita la interfaz que produce DIP, así que va **después**
de ese commit:

| # | Commit | Principio / motivo | Defecto que corrige |
|---|--------|--------------------|---------------------|
| 0 | `test: suite sobre la versión antes` (incluida en el tag) | Red de seguridad | — |
| 1 | `refactor(raii): catálogo y proveedores con unique_ptr` | RAII | #1 |
| 2 | `refactor(srp): separar consola, repositorios y servicios` | SRP / GRASP Controller | #2 |
| 3 | `refactor(dip): inyectar repositorios por constructor` | DIP / IoC | #3 |
| 4 | `refactor(ocp): unificar almacenamiento en Repository<T,K>` | OCP | #4 |
| 5 | `refactor(grasp): mover la impresión de pedidos a PurchaseOrder` | Information Expert | #5 |
| 6 | `feat(persistence): adaptadores MariaDB, compose y seed` | Adaptador de persistencia | — |

El commit 6 no responde a un principio: es la implementación del adaptador que DIP hizo
posible. Se separa para que los cinco commits de refactoring sigan siendo atribuibles a
un principio cada uno. `parcial02-final` se crea después del commit 6.

**4. El dominio es idéntico en las dos versiones.** `Article`, `Supplier`,
`PurchaseOrder`, `Quantity`, `Money`, `Date`, `Cuit` y `OrderNumber` no cambian: el
refactoring altera estructura, no modelo ni comportamiento. Por eso ninguna expectativa
de test cambia entre `parcial02-antes` y `parcial02-final`, y los dos diagramas de clases
difieren solo en el cableado.

