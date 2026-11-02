# Refactoring — Índice antes/después (Parcial 02)

> Documento requerido por `ADR-0001` (decisión RNF-005): indexa la demostración del
> antes y el después de aplicar RAII, IoC, SOLID y GRASP, y enlaza los dos tags que
> marcan cada versión. El comportamiento observable (menú, mensajes `MSG-###`, seed)
> es idéntico en ambas; solo cambia la estructura del código.

## Las dos versiones

| Versión | Tag | Commit | Qué es |
|---------|-----|--------|--------|
| Antes | `parcial02-antes` | `d78bf06` | Una sola clase `App` con menú, almacenamiento, validación y formato todo en uno, 100 % en memoria. |
| Después | `parcial02-final` | `HEAD` | Arquitectura con `Console`, servicios, repositorios (`Repository<T, K>`), adaptadores en memoria y MariaDB, catálogo de mensajes y valor types. |

El diff completo se inspecciona con:

```
git diff parcial02-antes..parcial02-final
```

## El "antes" (`parcial02-antes`)

La versión "antes" es la clase `App` (`include/app.hpp`, `src/app.cpp`), probada por
`tests/test_app.cpp`. Recibe `std::istream&` y `std::ostream&` por constructor — ese
borde de comportamiento estable es lo que permite escribir la suite sin tocar el
teclado. Dentro de `App` conviven los defectos plantados a propósito:

| # | Defecto (en "antes") | Corrección (en "después") | Principio |
|---|----------------------|---------------------------|-----------|
| 1 | `new Supplier*` / `delete` manual, riesgo de fugas | `std::vector<std::unique_ptr<...>>`, cierre automático | RAII |
| 2 | Una clase hace entrada/salida, almacenamiento, validación y formato a la vez | `Console`, `Repository`, `Service`, cada una con una responsabilidad | SRP / GRASP Controller |
| 3 | El `Service` instancia `new InMemorySupplierRepository()` adentro | Inyección de dependencias por constructor | DIP / IoC |
| 4 | Almacenamiento y búsqueda por clave reescritos a mano por entidad | `Repository<T, K>` reutilizable; cada entidad usa el contrato sin modificarse | OCP |
| 5 | `cout` de pedidos disperso en `main` / `App` | `PurchaseOrder::operator<<` sabe imprimirse a sí mismo | GRASP Information Expert |

El "antes" es 100 % en memoria y sus datos (artículos y pedidos de demostración)
están hardcodeados en el código.

## El "después" (`parcial02-final`)

La arquitectura separa capas por responsabilidad:

- **Dominio:** `Article`, `Supplier`, `PurchaseOrder`, `Quantity`, `Money`, `Date`,
  `Cuit`, `OrderNumber` (value types e entidades, invariantes en constructores).
- **Puertos de almacenamiento:** `Repository<T, K>` (find/all/add) y
  `MutableRepository<T, K>` (+ update/remove), genéricos.
- **Adaptadores:** `InMemoryRepository<T, K>` (pruebas, sin Docker) y los tres
  adaptadores MariaDB (`MariaDbSupplierRepository`, `MariaDbArticleRepository`,
  `MariaDbPurchaseOrderRepository`) sobre `MariaDbConnection` (RAII de `MYSQL*`).
- **Servicios:** `SupplierService` (BR-004, BR-005, BR-009) y
  `PurchaseOrderService` (BR-001, BR-006, BR-007, BR-008, BR-010, BR-011, BR-012).
- **Interfaz:** `Console(std::istream&, std::ostream&, …)` con un método por operación
  y el wrapper `guard()` que traduce `DomainError` a mensajes `MSG-###` del
  `MessageCatalog` (textos en español solo ahí; dominio con códigos en inglés).
- **Persistencia:** `docker-compose.yml` + `db/init/01-schema.sql` +
  `db/init/02-seed.sql`; credenciales por variables de entorno.

`MariaDbPurchaseOrderRepository` implementa a su vez `OrderNumberSequence`
(`MAX(number) + 1` antes del insert, BR-010), así que los números de pedido
sobreviven al reinicio de la aplicación.

## Índice de commits (fase 3)

| Orden | Commit | Principio / motivo |
|-------|--------|--------------------|
| S1 | `build(parcial-02): infraestructura CMake/Make, value types y entidades` (`3646e83`) | Layout, CMake, GTest, 45 pruebas unitarias sobre valor types y entidades. |
| S2 | `build(parcial-02): versión antes con App en memoria y suite completa` (`d78bf06`, tag `parcial02-antes`) | Punto de partida: el "antes" con red de seguridad de pruebas. |
| S3 | `build(parcial-02): refactoring SRP/DIP/OCP/IE — versión después` (`d5fb69b`) | RAII → SRP → DIP/IoC → OCP → Information Expert, un commit aplicando los cinco principios sobre la versión antes. |
| S4 | `build(parcial-02): infraestructura MariaDB (S4 parcial)` (`11bc465`) | `docker-compose.yml`, esquema, seed, `MariaDbConnection` y los 3 adaptadores MariaDB escritos. |
| S4 (integración) | `feat(persistence): adaptadores MariaDB integrados a main.cpp y CMakeLists.txt` (`HEAD`) | Los adaptadores se cablean en `main` con credenciales por entorno; fallo de conexión emite `MSG-003`/`MSG-004` y termina con código 1 sin mostrar el menú (RN-017, AC-017). |

`parcial02-final` se crea sobre el commit de integración, cerrando el ciclo
demostrativo de RNF-005.

## Cómo verificar

```
make build        # compila todo, cero warnings
make test         # 59 pruebas unitarias, sin Docker (100 % verde)
# con el contenedor arriba:
docker compose up -d
make run          # app real sobre MariaDB (seed cargado)
```

`make test-integration` requiere el contenedor; por ahora no hay pruebas con la
etiqueta `integration`, por lo que ese target corre cero pruebas y sale verde.
