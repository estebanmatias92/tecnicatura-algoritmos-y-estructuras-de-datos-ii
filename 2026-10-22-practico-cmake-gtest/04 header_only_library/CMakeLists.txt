# Requiere CMake 3.23 o una versión posterior.
cmake_minimum_required(VERSION 3.23)

# Declara el proyecto "geometry" y habilita el lenguaje C++.
project(geometry LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Crea la biblioteca de interfaz "geo".
# Una biblioteca INTERFACE no compila archivos fuente ni genera un binario;
# sirve para compartir encabezados y configuración con otros objetivos.
add_library(geo INTERFACE)

# Declara un conjunto de encabezados llamado "HEADERS" para "geo".
target_sources(geo INTERFACE
    FILE_SET HEADERS

    # Define la carpeta base desde la que se organizan los encabezados.
    BASE_DIRS
        ${PROJECT_SOURCE_DIR}

    # Agrega "geometry.h" al conjunto de encabezados de la interfaz.
    FILES
        "geometry.h"
)

# Procesa las configuraciones de compilación de estos subdirectorios.
add_subdirectory("shape")
add_subdirectory("square")

# Declara el ejecutable "example1".
add_executable(example1)

# Agrega el archivo fuente principal del ejecutable.
target_sources(example1 PRIVATE "examples/example1.cpp")

# Hace que "example1" use los encabezados y la configuración de "geo".
target_link_libraries(example1 PRIVATE geo)

# Instala la biblioteca de interfaz y su conjunto de encabezados "HEADERS".
install(TARGETS geo FILE_SET HEADERS)


#add_library(geo INTERFACE): Here INTERFACE means it is a header-only library, i.e. this library is not compiled.
#target_sources(): here is declared and mentioned to be an interface header. Any other project linking to this library should be aware of this and its location. The subdirectories using the same technique.geometry.h