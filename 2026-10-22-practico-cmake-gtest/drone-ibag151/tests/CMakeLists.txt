include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)

add_executable(drone_tests
    test_initial_state.cpp
    test_despegar.cpp
    test_aterrizar.cpp
    test_elevar.cpp
    test_bajar.cpp
    test_girar_derecha.cpp
    test_girar_izquierda.cpp
    test_acelerar.cpp
    test_frenar.cpp
    test_descargar_paquete.cpp
    test_sacar_foto.cpp
    test_notificar_entrega.cpp
    test_console_interface.cpp
)

target_link_libraries(drone_tests
    PRIVATE
        ibag151::drone_core
        GTest::gtest_main
)

target_compile_options(drone_tests PRIVATE ${PROJECT_WARNINGS})

include(GoogleTest)
gtest_discover_tests(drone_tests)
