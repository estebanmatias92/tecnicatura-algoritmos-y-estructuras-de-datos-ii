# Glosario de dominio

| Término | Definición |
|---|---|
| **Dron / IBag151** | Vehículo aéreo no tripulado que recibe comandos por consola y realiza una entrega. |
| **Comando** | Línea de texto que la consola envía al dron. |
| **Despegar** | Pasar de `Landed` a `Flying`. |
| **Aterrizar** | Volver a `Landed`, reiniciando altitud y velocidad. |
| **Elevar** | Aumentar la altitud en vuelo. |
| **Bajar** | Reducir la altitud en vuelo sin cruzar el suelo. |
| **Girar** | Cambiar el rumbo en múltiplos de 90°. |
| **Acelerar** | Aumentar la velocidad en vuelo. |
| **Frenar** | Reducir la velocidad en vuelo, con mínimo 0. |
| **Altitud** | Distancia vertical del dron respecto del suelo, en metros. |
| **Rumbo** | Dirección de vuelo en grados: 0 = norte, 90 = este, 180 = sur, 270 = oeste. |
| **Velocidad** | Magnitud escalar de desplazamiento, en unidades arbitrarias. |
| **Paquete** | Carga que el dron transporta hasta la recepción. |
| **Recepción** | Destino donde se descarga el paquete y se toma la foto. |
| **Entrega** | Proceso completo: descargar, fotografiar y notificar. |
| **FlightState** | Estado de vuelo: `Landed` o `Flying`. |
| **DeliveryStage** | Etapa de la entrega: `WithPackage`, `PackageUnloaded`, `ReceptionPhotographed`, `DeliveryNotified`. |
| **DroneError** | Excepción de dominio que señala una transición inválida. |
| **Puerto (`Drone`)** | Interfaz que declara las actividades del dron; el resto del programa depende de ella. |
| **Adaptador (`ConsoleInterface`)** | Traduce texto de consola a llamadas del puerto y presenta resultados. |
| **Composition root (`main`)** | Único lugar que construye las implementaciones concretas y las conecta. |
| **TDD** | Ciclo rojo–verde–refactor: primero la prueba que falla, luego el código que la hace pasar. |
| **GTest** | Framework de pruebas unitarias de Google. |
| **CMake** | Sistema de generación de la compilación, independiente del compilador. |
| **FetchContent** | Módulo de CMake que descarga dependencias en tiempo de configuración. |
