# Glosario de Dominio — Sistema de Presupuesto de Alojamientos

| Término | Definición |
|---|---|
| **Alojamiento** | Clase abstracta que define la interfaz común para todo tipo de hospedaje. Expone `getDescripcion()` y `calcularPrecio()`. |
| **Hotel** | Implementación concreta de `Alojamiento`. Representa un hotel con precio base. |
| **Hostel** | Posible implementación futura de `Alojamiento`. Hospedaje económico con habitaciones compartidas. |
| **Apartamento** | Posible implementación futura de `Alojamiento`. Alquiler temporario de unidad completa. |
| **Decorator** | Patrón estructural que permite agregar responsabilidades a un objeto dinámicamente. Envuelve al objeto original. |
| **AlojamientoDecorator** | Clase abstracta que implementa `Alojamiento` y contiene una referencia a otro `Alojamiento`. Base de todos los decoradores. |
| **DecoradorConcreto** | Decorador específico (ej: `Piscina`, `Desayuno`, `Gimnasio`, `Wifi`) que agrega una característica y su costo al alojamiento base. |
| **Presupuesto** | Resultado de la combinación de un alojamiento base con cero o más decoradores. Incluye descripción detallada y precio final. |
| **Extensibilidad** | Capacidad del sistema para incorporar nuevos tipos de alojamiento o nuevas características sin modificar código existente (abierto/cerrado). |
