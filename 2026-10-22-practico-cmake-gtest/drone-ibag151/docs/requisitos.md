# Requisitos

Este documento traduce las consignas del TP en reglas de negocio verificables
y criterios de aceptación. Cada criterio está cubierto por al menos una prueba
en `tests/`.

## Reglas de negocio

| ID | Regla |
|---|---|
| BR-01 | El dron comienza en tierra, a altitud 0, velocidad 0, rumbo 0 y con el paquete a bordo. |
| BR-02 | `despegar` solo es válido si el dron está en tierra. Un segundo despegue es un error. |
| BR-03 | `aterrizar` solo es válido en vuelo. Al aterrizar, la altitud y la velocidad vuelven a 0. |
| BR-04 | `elevar n` solo es válido en vuelo, con `n > 0`; la altitud se acumula. |
| BR-05 | `bajar n` solo es válido en vuelo, con `n > 0`, y no puede dejar la altitud por debajo de 0. Alcanzar 0 es válido y el dron sigue en vuelo. |
| BR-06 | `girar derecha` solo es válido en vuelo y suma 90° al rumbo, con aritmética módulo 360. |
| BR-07 | `girar izquierda` solo es válido en vuelo y resta 90° al rumbo, con aritmética módulo 360. |
| BR-08 | `acelerar n` solo es válido en vuelo, con `n > 0`; la velocidad se acumula. |
| BR-09 | `frenar n` solo es válido en vuelo, con `n > 0`; la velocidad nunca queda negativa. |
| BR-10 | `descargar paquete` solo es válido en tierra y con el paquete a bordo. Avanza la entrega a `PackageUnloaded`. |
| BR-11 | `sacar foto` solo es válido en tierra y después de descargar el paquete. Avanza la entrega a `ReceptionPhotographed`. |
| BR-12 | `notificar entrega` solo es válido en tierra y después de la foto. Avanza la entrega a `DeliveryNotified`. Una segunda notificación es un error. |
| BR-13 | Toda operación inválida lanza `DroneError` y no modifica el estado del dron. |
| BR-14 | La consola refleja cada comando recibido, informa `OK` o `ERROR`, y continúa el ciclo salvo ante `salir` o fin de entrada. |
| BR-15 | Los comandos numéricos sin argumento usan 1 como valor por defecto. Un argumento no numérico es un error de uso. |

## Criterios de aceptación

| ID | Criterio | Prueba |
|---|---|---|
| AC-01 | El estado inicial es el de BR-01. | `tests/test_initial_state.cpp` |
| AC-02 | Despegar cambia a `Flying`; repetirlo falla. | `tests/test_despegar.cpp` |
| AC-03 | Aterrizar cambia a `Landed` y reinicia altitud y velocidad. | `tests/test_aterrizar.cpp` |
| AC-04 | Elevar acumula altitud y rechaza valores no positivos. | `tests/test_elevar.cpp` |
| AC-05 | Bajar reduce altitud, permite llegar a 0 y rechaza valores que la crucen. | `tests/test_bajar.cpp` |
| AC-06 | Girar a la derecha suma 90° con wrap-around. | `tests/test_girar_derecha.cpp` |
| AC-07 | Girar a la izquierda resta 90° con wrap-around. | `tests/test_girar_izquierda.cpp` |
| AC-08 | Acelerar acumula velocidad y rechaza valores no positivos. | `tests/test_acelerar.cpp` |
| AC-09 | Frenar reduce velocidad y la acota en 0. | `tests/test_frenar.cpp` |
| AC-10 | Descargar exige tierra y paquete a bordo. | `tests/test_descargar_paquete.cpp` |
| AC-11 | La foto exige tierra y paquete descargado. | `tests/test_sacar_foto.cpp` |
| AC-12 | Notificar exige tierra y foto tomada. | `tests/test_notificar_entrega.cpp` |
| AC-13 | La consola traduce comandos, aplica defaults y reporta errores sin cortar. | `tests/test_console_interface.cpp` |
| AC-14 | Una entrega completa termina en `DeliveryNotified`. | `tests/test_console_interface.cpp` |

## Requisitos no funcionales

| ID | Requisito |
|---|---|
| RNF-01 | C++17, sin extensiones del compilador. |
| RNF-02 | CMake >= 3.20 y GoogleTest fijado en `v1.18.0` vía `FetchContent`. |
| RNF-03 | Sin dependencias de los ejemplos de la cátedra ni bibliotecas vendorizadas. |
| RNF-04 | Una prueba por actividad, ejecutable de forma individual con CTest. |
| RNF-05 | El árbol de compilación y las dependencias descargadas no se versionan. |
