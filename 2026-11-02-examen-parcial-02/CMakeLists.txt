cmake_minimum_required(VERSION 3.16)
project(parcial02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

# GTest instalado a nivel sistema (no vendorizar, no FetchContent)
find_package(GTest REQUIRED)

# libmariadb (Connector/C) vía pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(MARIADB REQUIRED libmariadb)

# Biblioteca core: dominio, servicios, repositorios en memoria
add_library(parcial02_core STATIC
    src/domain_error.cpp
    src/quantity.cpp
    src/money.cpp
    src/date.cpp
    src/cuit.cpp
    src/ordernumber.cpp
    src/article.cpp
    src/supplier.cpp
    src/purchaseorder.cpp
    src/article_catalog.cpp
    src/message_catalog.cpp
    src/supplier_service.cpp
    src/purchase_order_service.cpp
    src/console.cpp
    src/format.cpp
)

target_include_directories(parcial02_core PUBLIC include)

# Ejecutable principal (CLI de menú)
add_executable(parcial02
    src/main.cpp
)

target_link_libraries(parcial02 PRIVATE parcial02_core ${MARIADB_LIBRARIES})
target_include_directories(parcial02 PRIVATE ${MARIADB_INCLUDE_DIRS})

# Pruebas unitarias (GoogleTest, ejecutadas con CTest)
add_executable(parcial02_tests
    tests/test_console.cpp
    tests/test_domain_error.cpp
    tests/test_quantity.cpp
    tests/test_money.cpp
    tests/test_date.cpp
    tests/test_cuit.cpp
    tests/test_ordernumber.cpp
    tests/test_article.cpp
    tests/test_supplier.cpp
    tests/test_purchaseorder.cpp
)

target_link_libraries(parcial02_tests PRIVATE parcial02_core GTest::gtest_main GTest::gtest)

include(GoogleTest)
gtest_discover_tests(parcial02_tests)

enable_testing()
