# ADR-0004 — Persistencia en MariaDB detrás de la interfaz `Repository`

- **Estado:** aceptada
- **Fecha:** 2026-11-02
- **Relacionada:** `ADR-0002` (modelo de pedido), `ADR-0005` (estrategia de pruebas)

## Contexto

La versión inicial del registro de necesidades dejaba la persistencia explícitamente
fuera de alcance: el almacenamiento en memoria alcanzaba para el foco del examen. Al
ampliar el alcance se fija como requisito tener una base de datos real (RN-016,
RNF-010), servida desde un contenedor Docker.

La decisión no es "¿usamos una base?" sino **por dónde entra en el diseño**. El
trabajo tiene que demostrar DIP e IoC, y una base de datos cableada dentro del servicio
es justamente el defecto que la versión "antes" planta a propósito: `Service`
instanciando `new InMemorySupplierRepository()` por dentro.

## Decisión

La persistencia entra **detrás de la interfaz `Repository`**, nunca dentro del
servicio:

```cpp
class SupplierRepository {
public:
    virtual ~SupplierRepository() = default;
    virtual void add(const Supplier& supplier) = 0;
    virtual std::optional<Supplier> findByCuit(const Cuit& cuit) const = 0;
    virtual std::vector<Supplier> all() const = 0;
    virtual void update(const Supplier& supplier) = 0;
    virtual void remove(const Cuit& cuit) = 0;
};
```

Dos implementaciones, elegidas por composición en `main`:

| Implementación | Uso | Por qué |
|----------------|-----|---------|
| `InMemorySupplierRepository` | Unitarias y pruebas de servicio | Rápida, determinista, sin contenedor. Es además el fake que permite probar el servicio sin base. |
| `MariaDbSupplierRepository` | Integración y ejecución real | Habla con MariaDB por `libmariadb`, con sentencias preparadas y una transacción por operación. |

**Infraestructura versionada:**

- `docker-compose.yml` con un servicio `mariadb` y volumen nombrado.
- `db/init/01-schema.sql` y `db/init/02-seed.sql`, montados en
  `docker-entrypoint-initdb.d`, que se aplican solos en el primer arranque.
- Credenciales por variables de entorno (`MARIADB_HOST`, `MARIADB_PORT`,
  `MARIADB_DATABASE`, `MARIADB_USER`, `MARIADB_PASSWORD`), con defaults de desarrollo
  en el `compose` y sin secretos reales versionados.

**Alcance de los datos:** solo `Supplier` se escribe (es la única entidad con CRUD,
RN-011). `Article` y `PurchaseOrder` se **leen del seed** (RN-018) y no se modifican
desde la aplicación.

## Alternativas descartadas

**Solo memoria, con la base como trabajo futuro.** Descartada: deja RNF-010 sin
cumplir y desperdicia el contenedor ya disponible en el entorno.

**SQLite embebido.** Descartada: no necesita servicio, pero el requisito pide una base
servida y el ejercicio de conexión, credenciales y contenedor es parte del valor
didáctico. Además el archivo `.db` terminaría versionado o ignorado, sin esquema
explícito.

**Un microservicio HTTP que envuelva la base.** Descartada: agrega un salto de red y un
contrato de API que la consigna no pide, y esconde el adaptador que queremos mostrar.

**ORM externo (por ejemplo, ODB).** Descartada: rompe RNF-001 (dependencia pesada), y
la traducción fila → objeto es exactamente lo que el adaptador tiene que demostrar.

**Credenciales hardcodeadas en el adaptador.** Descartada por RNF-013: el repositorio
es público y las credenciales de desarrollo se filtran a cualquier copia.

## Consecuencias

- RNF-001 se amplía: `libmariadb` (Connector/C, vía `pkg-config`) es la única
  dependencia externa de ejecución permitida además de la STL.
- `make run` depende de que el contenedor esté arriba; el task runner debe levantar la
  base antes de ejecutar o fallar con un mensaje que lo explique (RN-017).
- Las pruebas se parten en dos: `make test` (solo unitarias, sin Docker) y
  `make test-integration` (requiere MariaDB arriba).
- El esquema se aplica al crear el volumen: para volver al seed hay que recrear el
  volumen (`docker compose down -v`). No hay migraciones automáticas en esta versión.
- La tabla de ítems del pedido (`purchase_order_items`) es una tabla de unión
  relacional, **no** una entidad de línea en el dominio: ADR-0002 sigue vigente.
- El adaptador es donde se concentran las sentencias SQL; ningún servicio conoce SQL.

## Enmienda 2026-11-02 — interfaces genéricas, pedidos append-only y numeración

La decisión de fondo no cambia (persistencia detrás de `Repository`, dos implementaciones,
infraestructura versionada). La fase de diseño precisó cuatro puntos; el primero
**corrige una afirmación del cuerpo** de este ADR.

**1. Corrección: "solo `Supplier` se escribe" es falso; debe leerse "solo `Supplier` se
modifica y se elimina".** RN-011 dice que `Article` y `PurchaseOrder` *se cargan*, y
AC-003, AC-004 y AC-012 exigen crear pedidos en runtime. El alcance real es:

| Entidad | Operaciones desde la aplicación | Implementación MariaDB |
|---------|--------------------------------|------------------------|
| `Supplier` | alta, baja, modificación, lectura | `MariaDbSupplierRepository` (`MutableRepository`) |
| `Article` | solo lectura | `MariaDbArticleRepository` (`Repository`) |
| `PurchaseOrder` | alta y lectura (append-only) | `MariaDbPurchaseOrderRepository` (`Repository` + `OrderNumberSequence`) |

Si los pedidos no se persistieran, BR-010 ("nunca se reutiliza") se rompería en cada
reinicio: el contador arrancaría de nuevo desde el máximo del seed.

**2. La interfaz es un template con dos niveles.** El bloque de código del cuerpo describe
un `SupplierRepository` nombrado y no-template. La forma acordada es:

```cpp
template <class T, class K>
class Repository {                                     // find / all / add
public:
    virtual ~Repository() = default;
    virtual std::optional<T> find(const K& key) const = 0;
    virtual std::vector<T> all() const = 0;
    virtual void add(const T& entity) = 0;
};

template <class T, class K>
class MutableRepository : public Repository<T, K> {     // + update / remove
public:
    virtual void update(const T& entity) = 0;
    virtual void remove(const K& key) = 0;
};

using SupplierRepository     = MutableRepository<Supplier, Cuit>;
using ArticleRepository      = Repository<Article, std::string>;
using PurchaseOrderRepository = Repository<PurchaseOrder, OrderNumber>;
```

`findByCuit` desaparece como nombre propio: la clave está en la firma (`find(cuit)`) y el
alias conserva la legibilidad. El nivel `MutableRepository` no es decorativo: hace que
RN-011 se cumpla **por tipo** — un `ArticleRepository` no tiene `update` ni `remove` que
alguien pueda llamar por error.

**3. La numeración la asigna el repositorio antes del insert, con un puerto aparte.**

```cpp
class OrderNumberSequence {
public:
    virtual ~OrderNumberSequence() = default;
    virtual OrderNumber nextNumber() = 0;
};
```

`MariaDbPurchaseOrderRepository` implementa `Repository<PurchaseOrder, OrderNumber>` y
`OrderNumberSequence`; `InMemoryOrderNumberSequence` es el doble de prueba. La
implementación SQL es `SELECT COALESCE(MAX(number), 0) + 1 FROM purchase_orders` dentro
de la misma transacción del alta, así que la asignación y el insert son atómicos y un
rollback no quema ni reutiliza números. El seed inserta los números `1..3`, de modo que
el primer pedido nuevo de una sesión recibe el `4`.

Se descarta `AUTO_INCREMENT` (alternativa considerada) porque el número nace recién
después de que la base acepta la fila, mientras que BR-006, BR-007 y BR-011 tienen que
validarse **antes** y `PurchaseOrder` necesita su `number` para existir como objeto
válido. También se descarta una tabla de secuencia dedicada: con un solo operador y una
transacción por alta, `MAX + 1` es correcto y no agrega esquema.

**4. El esquema tiene cuatro tablas.** `suppliers`, `articles`, `purchase_orders` y
`purchase_order_items`. La tabla de ítems tiene clave primaria `(order_number,
article_code)`, que hace cumplir BR-008 en la base, y una columna `position` que
preserva el orden de carga que exige RN-007. Ver `docs/diagrams/esquema-base.puml`.

