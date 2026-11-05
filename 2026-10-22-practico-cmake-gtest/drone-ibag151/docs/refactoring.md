# Refactoring: de `Car` a `DroneIbag151`

El laboratorio de la cátedra (`007 IBag`) modela un automóvil con
`Car::accelerate` y `Car::brake`. Este documento registra los olores de diseño
detectados en esa base y las refactorizaciones aplicadas en la solución.

## Punto de partida

```cpp
class Car {
public:
    Car();
    void accelerate(int intensity);
    int brake(int intensity);
    int getSpeed();
    int speed;          // campo público
private:
};

Car::Car() { speed = 10; }

void Car::accelerate(int intensity) {
    speed = speed + intensity;
}

int Car::brake(int intensity) {
    speed = speed - intensity;
    return speed;
}
```

## Olores detectados

| Olor | Evidencia | Consecuencia |
|---|---|---|
| Campo público | `int speed` | Cualquier código puede romper el invariante. |
| Constantes muertas | `ACCELERATION_FACTOR`, `BRAKING_FACTOR` | Documentan una regla que no se aplica. |
| Número mágico | `speed = 10` en el constructor | Estado inicial arbitrario y no justificado. |
| Invariante ausente | `brake` puede dejar velocidad negativa | Estado físicamente imposible. |
| Acoplamiento a la implementación | `main` usa `new Car()` sin `delete` | Fuga de memoria y dependencia del concreto. |
| Duplicación | `Main.cpp` y `Main2.cpp` casi idénticos | Dos programas que divergen con el tiempo. |
| Configuración frágil | `file(GLOB ...)` y rutas relativas a `ext/` | La compilación depende del árbol local. |
| Pruebas acopladas al valor inicial | `EXPECT_EQ(20, ...)` asume `speed = 10` | Cambiar el estado inicial rompe pruebas ajenas. |

## Refactorizaciones aplicadas

1. **Extract Interface / Dependency Inversion.** Se creó el puerto `Drone` con
   las once actividades. `ConsoleInterface` depende de `Drone`, no de la
   implementación concreta.
2. **Encapsulate Field.** `altitude_`, `heading_`, `speed_`, `flight_state_` y
   `delivery_stage_` son privados; solo cambian mediante operaciones validadas.
3. **Replace Magic Number with Constant / Default State.** El estado inicial se
   define explícitamente: tierra, altitud 0, velocidad 0, rumbo 0, con paquete.
4. **Introduce State Machine.** `FlightState` y `DeliveryStage` reemplazan
   banderas sueltas y hacen explícitas las transiciones válidas.
5. **Extract Guard Clauses.** `requireFlying`, `requireLanded`,
   `requirePositive` y `requireDeliveryStage` concentran la validación y
   lanzan `DroneError` con un mensaje uniforme.
6. **Extract Adapter.** `ConsoleInterface` aísla el parseo de texto, los
   valores por defecto y la presentación; no conoce reglas de negocio.
7. **Replace Constructor with Composition Root.** `main` construye el dron y el
   adaptador; no hay `new`/`delete` manuales ni lógica de dominio.
8. **Rename and Move.** `Car` pasa a `DroneIbag151`; las responsabilidades se
   separan en `include/ibag151/`, `src/` y `tests/`.
9. **Test-First.** Cada actividad se incorporó con una prueba en rojo, luego la
   implementación en verde y, cuando hizo falta, un refactor.

## Después

```cpp
class Drone {
public:
    virtual ~Drone() = default;
    virtual void takeOff() = 0;
    virtual void land() = 0;
    virtual void ascend(int meters) = 0;
    virtual void descend(int meters) = 0;
    // ...
};

class DroneIbag151 : public Drone {
    // estado privado, transiciones validadas
};

class ConsoleInterface {
public:
    ConsoleInterface(std::istream& in, std::ostream& out, Drone& drone);
    int run();
};
```

## Resultado

- Un único estado inicial explícito y verificable.
- Operaciones inválidas rechazadas con `DroneError`, sin efectos parciales.
- Adaptador de consola testeable con `std::istringstream` y `std::ostringstream`.
- 57 pruebas ejecutables de forma individual con CTest.
- Diagramas y requisitos versionados junto al código.
