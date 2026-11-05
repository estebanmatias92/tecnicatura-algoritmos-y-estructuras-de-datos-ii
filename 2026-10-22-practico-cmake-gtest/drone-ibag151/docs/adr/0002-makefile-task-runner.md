# ADR 0002 — Makefile como task runner

- **Estado:** aceptada
- **Fecha:** 2026-11-05

## Contexto

El flujo de trabajo incluye configurar, compilar, ejecutar pruebas, correr la
demo, formatear, lintar, renderizar diagramas y empaquetar. Escribir los
comandos de CMake/CTest a mano es propenso a errores y difícil de recordar.

## Decisión

Exponer un `Makefile` en la raíz de la solución que actúe como envoltorio
delgado sobre CMake. El objetivo por defecto es `help`, generado a partir de
comentarios `##` en cada target.

Targets principales: `configure`, `build`, `rebuild`, `test`, `run`,
`run-interactive`, `check`, `format`, `format-check`, `lint`, `diagram`,
`clean` y `dist`.

## Alternativas consideradas

- **Comandos manuales de CMake:** cero abstracción, pero más carga cognitiva y
  pasos repetidos.
- **CMake Presets:** buena opción para configuración, pero no cubre ejecución,
  formato, diagramas ni empaquetado.
- **`just` / `task`:** requieren instalar una herramienta adicional; `make` ya
  está disponible en el entorno de la cátedra.

## Consecuencias

- Un único punto de entrada para el trabajo diario.
- CMake sigue siendo la fuente de verdad: los targets solo lo invocan.
- El `Makefile` raíz no se confunde con los `Makefile` generados dentro de
  `build/`.
- Se puede seguir usando VS Code con CMake Tools sin conflicto.
