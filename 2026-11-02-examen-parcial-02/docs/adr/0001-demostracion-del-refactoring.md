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
