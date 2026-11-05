# Reglas de vuelo y de entrega

El dron combina dos máquinas de estado independientes:

- **Vuelo:** `Landed` (en tierra) y `Flying` (en vuelo).
- **Entrega:** `WithPackage` → `PackageUnloaded` → `ReceptionPhotographed` →
  `DeliveryNotified`.

El diagrama está en [`diagrams/delivery-states.puml`](diagrams/delivery-states.puml).

## Invariantes

- La altitud, la velocidad y el rumbo nunca son negativos.
- La altitud solo es distinta de 0 mientras el dron está en vuelo.
- El paquete solo puede descargarse una vez.
- La foto solo puede tomarse después de descargar el paquete.
- La notificación solo puede emitirse después de la foto.
- Toda transición inválida lanza `DroneError` sin modificar el estado.

## Operaciones de vuelo

| Operación | Precondición | Efecto | Error |
|---|---|---|---|
| `takeOff()` | `Landed` | `Flying` | Ya está en vuelo |
| `land()` | `Flying` | `Landed`, altitud 0, velocidad 0 | Ya está en tierra |
| `ascend(n)` | `Flying`, `n > 0` | `altitude += n` | En tierra o `n <= 0` |
| `descend(n)` | `Flying`, `n > 0`, `n <= altitude` | `altitude -= n` | En tierra, `n <= 0` o cruzando el suelo |
| `turnRight()` | `Flying` | `heading = (heading + 90) % 360` | En tierra |
| `turnLeft()` | `Flying` | `heading = (heading + 270) % 360` | En tierra |
| `accelerate(n)` | `Flying`, `n > 0` | `speed += n` | En tierra o `n <= 0` |
| `brake(n)` | `Flying`, `n > 0` | `speed = max(0, speed - n)` | En tierra o `n <= 0` |

## Operaciones de entrega

| Operación | Precondición | Efecto | Error |
|---|---|---|---|
| `unloadPackage()` | `Landed`, `WithPackage` | `PackageUnloaded` | En vuelo o paquete ya descargado |
| `takeReceptionPhoto()` | `Landed`, `PackageUnloaded` | `ReceptionPhotographed` | En vuelo, paquete a bordo o foto ya tomada |
| `notifyDelivery()` | `Landed`, `ReceptionPhotographed` | `DeliveryNotified` | En vuelo, sin foto o notificación repetida |

## Secuencia de una entrega

```text
despegar
elevar 20
girar derecha
bajar 20
aterrizar
descargar paquete
sacar foto
notificar entrega
```

La secuencia completa se ejecuta con `make run` usando
[`scripts/demo.txt`](../scripts/demo.txt).
