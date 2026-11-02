# Domain Docs

How the engineering skills should consume this project's domain documentation when exploring the codebase.

## Before exploring, read these

- **`docs/glosario-de-dominio.md`**: the domain vocabulary (`Article`, `Supplier`, `PurchaseOrder`, `Quantity`, `Money`, `Date`, `Cuit`, `OrderNumber`) and the list of synonyms to avoid. Use these terms in issue titles, hypotheses, test names and code identifiers.
- **`docs/registro-necesidades.md`**: the functional (`RN-###`) and non-functional (`RNF-###`) requirements, plus the explicit out-of-scope list. Cite a requirement ID when a change traces to one.
- **`docs/reglas-de-negocio.md`**: the business rules (`BR-###`), each traced to its `RN-###` and to where it is enforced.
- **`docs/criterios-de-aceptacion.md`**: the Given/When/Then acceptance criteria (`AC-###`) per requirement; this is the source the test phase hangs from.
- **`docs/adr/`**: read ADRs that touch the area you're about to work in. ADR-0001 covers how the before/after refactoring is demonstrated; ADR-0002 covers the purchase order model; ADR-0003 the app type and stack; ADR-0004 the MariaDB persistence; ADR-0005 the test strategy; ADR-0006 the error handling.
- **`docs/especificacion-funcional.md`**: the menu, the contract per operation, the `MSG-###` message catalog and the exact output format. Integration tests assert those texts, so treat message IDs as stable identifiers.

This project follows the course convention rather than the generic `GLOSSARY.md` layout: sibling practices use `docs/glosario-de-dominio.md` and `docs/registro-necesidades.md`, so new docs keep the same names and stay navigable next to them.

If any of these files don't exist, **proceed silently**. Don't flag their absence; don't suggest creating them upfront. The `/domain-modeling` skill (reached via `/grill-with-docs` and `/improve-codebase-architecture`) creates them lazily when terms or decisions actually get resolved.

## File structure

Single-context project (no `GLOSSARY-MAP.md` here, and no monorepo signals):

```
2026-11-02-examen-parcial-02/
├── AGENTS.md
├── CMakeLists.txt
├── Makefile                         ← task runner (DX)
├── docker-compose.yml
├── cmake/                           ← módulos de CMake
├── db/init/                         ← 01-schema.sql, 02-seed.sql
├── include/*.hpp
├── src/*.cpp
├── tests/*.cpp                      ← GTest + CTest
├── build/                           ← artefactos (gitignored)
└── docs/
    ├── consignas.md                 ← consigna original del parcial
    ├── glosario-de-dominio.md       ← vocabulario
    ├── registro-necesidades.md      ← RN / RNF / fuera de alcance
    ├── reglas-de-negocio.md         ← BR trazadas a RN
    ├── criterios-de-aceptacion.md   ← AC en Given/When/Then por RN
    ├── especificacion-funcional.md  ← menú, contrato por operación, catálogo MSG
    ├── refactoring.md               ← índice de la demostración antes/después
    ├── adr/                         ← decisiones con alternativas descartadas
    └── diagrams/                    ← *.puml versionados + *.svg renderizados
```

## Use the glossary's vocabulary

When your output names a domain concept (in an issue title, a refactor proposal, a hypothesis, a test name), use the term as defined in `docs/glosario-de-dominio.md`. Don't drift to synonyms the glossary explicitly avoids.

Code identifiers are in English; user-facing UI strings and documentation stay in Spanish (RNF-007). Don't rename a term to Spanish in code, and don't translate UI copy to English.

If the concept you need isn't in the glossary yet, that's a signal: either you're inventing language the project doesn't use (reconsider) or there's a real gap (note it for `/domain-modeling`).

## Flag ADR conflicts

If your output contradicts an existing ADR, surface it explicitly rather than silently overriding:

> _Contradicts ADR-0001 (tags y commits por principio), but worth reopening because…_
