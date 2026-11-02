# ADR-0003 — CLI de menú sobre un núcleo testeable: CMake genera, Make orquesta, GTest prueba

- **Estado:** aceptada
- **Fecha:** 2026-11-02
- **Relacionada:** `ADR-0001` (demostración del refactoring), `ADR-0005` (estrategia de pruebas)

## Contexto

La consigna no fija el tipo de aplicación ni el stack: solo pide C++ y mostrar los
pedidos por consola. Quedaban abiertas dos decisiones que condicionan todo el trabajo
posterior: **qué tipo de aplicación** se construye y **con qué herramientas** se
compila y se prueba.

Del lado de la interfaz, la opción más ambiciosa es una TUI de pantalla completa. Del
lado del build, el curso arrastra dos convenciones distintas: todas las prácticas de
2026 usan GNU Make con `all`/`run`/`clean`, mientras que la práctica inmediatamente
anterior a este examen introduce CMake con GTest vendorizado.

## Decisión

**Una aplicación CLI de menú interactivo**, con la interfaz aislada en un adaptador
`Console` que recibe `std::istream&` y `std::ostream&` por constructor. El núcleo
(dominio + servicios + repositorios) no lee ni escribe por consola.

**Tres herramientas con tres responsabilidades distintas, que se complementan:**

| Herramienta | Rol | Qué aporta |
|-------------|-----|------------|
| **CMake** | Generador del build | `find_package(GTest REQUIRED)`, `enable_testing()`, targets por biblioteca, integración con CTest. Fuente de verdad de la compilación. |
| **Make** | Task runner (DX) | `make all/build/run/test/test-integration/clean`, envolviendo `cmake --build` y `ctest`. Conserva la convención del curso y evita que el operador recuerde comandos de CMake. |
| **GTest** | Framework de pruebas | Unitarias e integración, con `ctest` como ejecutor. |

Las tres son requisito (RNF-002 y RNF-009) y no compiten: CMake *genera*, Make
*orquesta*, GTest *verifica*.

## Alternativas descartadas

**TUI con `ncurses` o `FTXUI`.** Descartada: agrega una dependencia externa de UI que
rompe RNF-001 ("solo STL") y consume el presupuesto de tiempo en dibujar pantallas, no
en el diseño que el examen evalúa. `Console` queda como punto de extensión: una TUI
futura sería otro adaptador, sin tocar servicios ni dominio.

**GUI de escritorio con Qt.** Descartada por el mismo motivo, amplificado: Qt es un
framework completo, con su propio sistema de build y de eventos.

**Aplicación web.** Descartada: exige servidor HTTP, frontend y serialización, tres
capas que la consigna no menciona y que no aportan a la demostración de RAII, IoC,
SOLID y GRASP.

**Solo CMake, sin Makefile.** Descartada: el operador tendría que recordar
`cmake -S . -B build && cmake --build build && ctest --test-dir build`; el Makefile de
una pantalla resuelve eso y mantiene viva la convención que el resto del repositorio
usa.

**Solo GNU Make, sin CMake.** Descartada: sin CMake, enlazar GTest y separar
bibliotecas de tests obliga a escribir a mano rutas de include y linkeo, y cada
dependencia nueva se descubre por prueba y error.

**GTest vendorizado en `ext/`.** Descartada: GTest 1.18 ya está instalado y expone
`GTestConfig.cmake`; versionar el árbol de GoogleTest agrega miles de archivos al
repositorio para fijar una versión que el entorno ya resuelve.

## Consecuencias

- RNF-001 sigue diciendo "STL" y RNF-002 cambia de "GNU Make" a "CMake genera, Make
  orquesta"; el `AGENTS.md` del proyecto se alinea con la nueva regla.
- `Console` debe recibir sus streams por constructor para poder probarse sin teclado;
  esa decisión arrastra a la fase de diseño.
- El menú numérico fija la forma de RN-010 y de las operaciones de RN-002.
- Cualquier interfaz futura (TUI, web) se implementa como otro adaptador de los
  servicios; el núcleo no cambia.
