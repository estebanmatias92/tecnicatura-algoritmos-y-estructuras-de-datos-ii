# ADR 0003 — PlantUML para los diagramas UML

- **Estado:** aceptada
- **Fecha:** 2026-11-05

## Contexto

La consigna pide un diagrama de clases en UML. El material de la cátedra usa
DrawIO, cuyo formato binario/XML no se revisa bien en un diff y depende de una
aplicación gráfica.

## Decisión

Modelar los diagramas como texto PlantUML en `docs/diagrams/*.puml` y renderizar
SVG con `make diagram`:

```sh
plantuml -tsvg docs/diagrams/*.puml
```

Se versionan tanto el fuente `.puml` como el `.svg` renderizado.

## Alternativas consideradas

- **DrawIO:** buena herramienta visual, pero el archivo es más difícil de
  mantener y revisar en Git.
- **Mermaid:** se renderiza en GitHub, pero el soporte local y la expresividad
  UML son menores.
- **Graphviz puro:** muy flexible, pero de más bajo nivel para UML.

## Consecuencias

- Los diagramas se revisan como cualquier otro texto.
- Renderizar requiere Java y `plantuml`; si no están instalados, el resto del
  proyecto sigue funcionando.
- El SVG commiteado permite ver el diagrama sin instalar nada.
