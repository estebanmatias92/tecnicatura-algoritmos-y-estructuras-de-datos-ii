# Define la versión mínima de CMake necesaria para procesar este archivo (si usas 3.10 quitas la advertencia amarilla de deprecación).
cmake_minimum_required(VERSION 3.5)

# Establece el nombre del proyecto como "modio" y crea internamente la variable ${PROJECT_SOURCE_DIR} con la ruta raíz del proyecto.
project(modio)

# Configura el compilador para que utilice el estándar C++11 (equivalente a pasar el flag -std=c++11).
set (CMAKE_CXX_STANDARD 11)

# Busca los archivos especificados (Main.cpp, Myfunctions.cpp y Myfunctions.h) y guarda la lista con sus rutas completas en la variable TEST_SRC_FILES_ONE.
file(GLOB TEST_SRC_FILES_ONE ${PROJECT_SOURCE_DIR}/src/Main.cpp ${PROJECT_SOURCE_DIR}/librerias/Myfunctions.cpp ${PROJECT_SOURCE_DIR}/encabezado/Myfunctions.h)

# Crea un primer archivo ejecutable llamado "Uno" compilando los archivos fuente almacenados en la variable ${TEST_SRC_FILES_ONE}.
add_executable(Uno ${TEST_SRC_FILES_ONE})


# Agrupa los mismos archivos fuente y cabeceras del programa principal dentro de una nueva variable llamada TEST_SRC_FILES_PPAL.
file(GLOB TEST_SRC_FILES_PPAL ${PROJECT_SOURCE_DIR}/src/Main.cpp ${PROJECT_SOURCE_DIR}/librerias/Myfunctions.cpp ${PROJECT_SOURCE_DIR}/encabezado/Myfunctions.h)

# Crea un segundo archivo ejecutable llamado "Principal" a partir de los archivos guardados en ${TEST_SRC_FILES_PPAL}.
add_executable(Principal ${TEST_SRC_FILES_PPAL})



  # Imprime el mensaje informativo "Testing enabled" en la consola cuando ejecutas el comando cmake.
  message("Testing enabled")

  # Busca el archivo de pruebas (Test.cpp) y todos los archivos .cpp dentro de "librerias/" (sin incluir Main.cpp para no tener dos funciones main) y los guarda en TEST_SRC_FILES.
  file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/testUnit/Test.cpp ${PROJECT_SOURCE_DIR}/librerias/*.cpp )

  # Línea comentada (ignorada por CMake): buscaría todos los .cpp de la carpeta src/.
  #file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
  
  # Incorpora la subcarpeta "ext/googletest" al proceso de compilación para que CMake procese su propio CMakeLists.txt y compile GoogleTest.
  add_subdirectory(ext/googletest)

  # Habilita el sistema de pruebas CTest en este directorio para poder ejecutar luego "make test" o "ctest".
  enable_testing()

  # Agrega las carpetas de encabezados (.h) de GoogleTest a las rutas de búsqueda del compilador para que reconozca #include <gtest/gtest.h>.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  # Crea el ejecutable de pruebas llamado "runUnitTests" compilando Test.cpp junto con las funciones de la carpeta librerias/.
  add_executable(runUnitTests ${TEST_SRC_FILES})

  # Enlaza (linkea) el ejecutable "runUnitTests" con las librerías "gtest" (núcleo de GoogleTest) y "gtest_main" (que provee un main() automático para correr los tests).
  target_link_libraries(runUnitTests gtest gtest_main)

  # Registra el ejecutable "runUnitTests" dentro de CTest bajo el nombre de prueba "UnitTests".
  add_test(UnitTests runUnitTests)
