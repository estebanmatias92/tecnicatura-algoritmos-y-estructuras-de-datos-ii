# ADR 0001 — GoogleTest vía FetchContent

- **Estado:** aceptada
- **Fecha:** 2026-11-05

## Contexto

El TP exige CMake y GTest. Los ejemplos de la cátedra clonan GoogleTest dentro
de `ext/googletest` y lo referencian con rutas relativas, lo que deja la
solución acoplada a esos directorios y a un submodule sin `.gitmodules`.

## Decisión

Declarar GoogleTest como dependencia de desarrollo con `FetchContent`, fijada
en la etiqueta `v1.18.0`, dentro de `cmake/dependencies.cmake`:

```cmake
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
)
```

`BUILD_GMOCK` e `INSTALL_GTEST` se desactivan para reducir tiempos de
configuración y evitar instalaciones accidentales.

## Alternativas consideradas

- **`find_package(GTest)`:** requiere una instalación previa del sistema y
  vuelve la compilación dependiente del entorno.
- **Submodule vendorizado:** agrega peso al repositorio, exige `.gitmodules` y
  arrastra el mismo acoplamiento que los ejemplos de la cátedra.
- **Copia manual en `ext/`:** no es reproducible y no fija versión.

## Consecuencias

- La primera configuración necesita red; las siguientes reutilizan
  `build/_deps/`.
- La versión queda fijada y es visible en un único archivo.
- `build/` y `_deps/` están ignorados por Git.
- La solución se puede clonar y compilar sin depender de los laboratorios.
