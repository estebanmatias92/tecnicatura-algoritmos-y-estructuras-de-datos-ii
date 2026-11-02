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
