# Domain Docs

How the engineering skills should consume this project's domain documentation when exploring the codebase.

## Before exploring, read these

- **`docs/glosario-de-dominio.md`**: the domain vocabulary (Artículo, Proveedor, Pedido, Renglón de Pedido) and the list of synonyms to avoid. Use these terms in issue titles, hypotheses, test names and code identifiers.
- **`docs/registro-necesidades.md`**: the functional (`RN-###`) and non-functional (`RNF-###`) requirements, plus the explicit out-of-scope list. Cite a requirement ID when a change traces to one.
- **`docs/adr/`**: read ADRs that touch the area you're about to work in. ADR-0001 covers how the before/after refactoring is demonstrated.

This project follows the course convention rather than the generic `GLOSSARY.md` layout: sibling practices use `docs/glosario-de-dominio.md` and `docs/registro-necesidades.md`, so new docs keep the same names and stay navigable next to them.

If any of these files don't exist, **proceed silently**. Don't flag their absence; don't suggest creating them upfront. The `/domain-modeling` skill (reached via `/grill-with-docs` and `/improve-codebase-architecture`) creates them lazily when terms or decisions actually get resolved.

## File structure

Single-context project (no `GLOSSARY-MAP.md` here, and no monorepo signals):

```
2026-11-02-examen-parcial-02/
├── AGENTS.md
├── docs/
│   ├── consignas.md                 ← consigna original del parcial
│   ├── glosario-de-dominio.md       ← vocabulario
│   ├── registro-necesidades.md      ← RN / RNF / fuera de alcance
│   ├── refactoring.md               ← índice de la demostración antes/después
│   ├── adr/                         ← decisiones con alternativas descartadas
│   └── diagrams/                    ← *.puml versionados + *.svg renderizados
├── include/*.hpp
└── src/*.cpp
```

## Use the glossary's vocabulary

When your output names a domain concept (in an issue title, a refactor proposal, a hypothesis, a test name), use the term as defined in `docs/glosario-de-dominio.md`. Don't drift to synonyms the glossary explicitly avoids.

If the concept you need isn't in the glossary yet, that's a signal: either you're inventing language the project doesn't use (reconsider) or there's a real gap (note it for `/domain-modeling`).

## Flag ADR conflicts

If your output contradicts an existing ADR, surface it explicitly rather than silently overriding:

> _Contradicts ADR-0001 (tags y commits por principio), but worth reopening because…_
