# ADR-0005 — Pruebas en tres capas y `make test` verde en cada commit del refactoring

- **Estado:** aceptada
- **Fecha:** 2026-11-02
- **Relacionada:** `ADR-0001` (demostración del refactoring), `ADR-0003` (stack), `ADR-0004` (persistencia)

## Contexto

ADR-0001 exige un commit por principio, en orden, sobre un historial lineal. Ese plan
tiene un riesgo concreto: si cada refactoring se hace "a ojo", el quinto commit puede
haber cambiado el comportamiento sin que nadie lo note, y la demostración se vuelve una
afirmación sin evidencia.

La red de seguridad natural es una suite de pruebas que exista **antes** del primer
refactoring y que siga verde después. El curso no tiene convención de tests —ninguna
práctica C++ tiene target `test`—, así que la decisión es nuestra.

## Decisión

**Tres capas, con responsabilidades separadas y un umbral de cobertura.** Las pruebas
se escriben sobre la versión "antes" y acompañan cada commit; ninguna se borra ni se
relaja durante el refactoring.

| Capa | Qué prueba | Aislamiento | Requiere Docker |
|------|------------|-------------|-----------------|
| **Unitaria de dominio** | `Quantity`, `Cuit`, `Money`, `Date`: construcciones válidas, rechazos, operaciones | Ninguno: son value types | No |
| **Unitaria de servicio** | Reglas de `SupplierService` y `PurchaseOrderService` (BR-002 a BR-011) | Repositorio en memoria inyectado | No |
| **De integración** | `MariaDbSupplierRepository` contra un MariaDB real, y `Console` + servicio + repositorio alimentando `istringstream` y leyendo `ostringstream` | Contenedor real / streams en memoria | Sí, solo la de base |

**Regla de oro del refactoring:** después de **cada** commit de principio,
`make test` pasa. Si un commit necesitara cambiar una expectativa de test, ese cambio
va en el mismo commit y se explica en `docs/refactoring.md`; si cambia el
comportamiento observable, no es un refactoring y no entra.

**Cobertura:** ≥ 80 % de líneas sobre `src/` excluyendo `main.cpp` y el bucle del menú,
medida con `gcov`/`gcovr`. El número no es una meta estética: es el control de que las
reglas de negocio del servicio se ejercitan y no solo se compilan.

## Alternativas descartadas

**Sin pruebas, verificación manual por consola.** Descartada: es lo único que hace
imposible afirmar que el "después" conserva el comportamiento del "antes", que es la
mitad de lo que el examen pide demostrar.

**Solo pruebas de integración de punta a punta.** Descartada: cada caso necesita base y
contenedor, los errores llegan sin localización y el ciclo de feedback se vuelve lento
justo cuando más commits hay que validar.

**Solo pruebas unitarias, con todo mockeado.** Descartada: no probaría el adaptador
SQL, que es donde se concentran las traducciones y las transacciones; un repositorio
que compila y devuelve basura pasaría la suite.

**Exigir 100 % de cobertura.** Descartada: obliga a inventar pruebas para ramas
defensivas inalcanzables y premia escribir código con ramas artificiales. 80 % sobre
las clases con reglas es el punto donde la suite deja de ser decorativa.

**GTest desde `FetchContent` o vendorizado.** Descartada: GTest 1.18 está instalado y
expone su config de CMake; bajarlo en cada configuración agrega red al build sin
beneficio (coincide con ADR-0003).

## Consecuencias

- La suite se escribe antes del tag `parcial02-antes` y viaja con la versión inicial.
- `make test` no necesita Docker; `make test-integration` sí, y falla con un mensaje
  claro si el contenedor no está arriba.
- Todo servicio recibe sus dependencias por constructor (ADR-0004): sin eso, las
  unitarias de servicio no existirían.
- `Console` recibe `std::istream&` y `std::ostream&`: la prueba de integración de
  consola es posible sin tocar stdin.
- El umbral de cobertura se verifica en un target aparte (`make coverage`), no en
  `make test`, para que el ciclo corto siga siendo corto.
