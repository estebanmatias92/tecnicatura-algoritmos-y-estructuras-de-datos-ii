#include "ibag151/drone_ibag151.hpp"

#include <algorithm>

namespace ibag151 {

void DroneIbag151::takeOff() {
    if (flight_state_ == FlightState::Flying) {
        throw DroneError("el drone ya esta en vuelo");
    }

    flight_state_ = FlightState::Flying;
}

void DroneIbag151::land() {
    if (flight_state_ == FlightState::Landed) {
        throw DroneError("el drone ya esta en tierra");
    }

    flight_state_ = FlightState::Landed;
    altitude_ = 0;
    speed_ = 0;
}

void DroneIbag151::ascend(int meters) {
    requireFlying("elevar");
    requirePositive(meters, "elevar");

    altitude_ += meters;
}

void DroneIbag151::descend(int meters) {
    requireFlying("bajar");
    requirePositive(meters, "bajar");

    if (meters > altitude_) {
        throw DroneError("no se puede bajar por debajo del suelo");
    }

    altitude_ -= meters;
}

void DroneIbag151::turnRight() {
    requireFlying("girar a la derecha");

    heading_ = (heading_ + 90) % 360;
}

void DroneIbag151::turnLeft() {
    requireFlying("girar a la izquierda");

    heading_ = (heading_ + 270) % 360;
}

void DroneIbag151::accelerate(int amount) {
    requireFlying("acelerar");
    requirePositive(amount, "acelerar");

    speed_ += amount;
}

void DroneIbag151::brake(int amount) {
    requireFlying("frenar");
    requirePositive(amount, "frenar");

    speed_ = std::max(0, speed_ - amount);
}

void DroneIbag151::unloadPackage() {
    requireLanded("descargar el paquete");
    requireDeliveryStage(DeliveryStage::WithPackage, "descargar el paquete");

    delivery_stage_ = DeliveryStage::PackageUnloaded;
}

void DroneIbag151::takeReceptionPhoto() {
    requireLanded("sacar la foto de la recepcion");
    requireDeliveryStage(DeliveryStage::PackageUnloaded, "sacar la foto de la recepcion");

    delivery_stage_ = DeliveryStage::ReceptionPhotographed;
}

void DroneIbag151::notifyDelivery() {
    requireLanded("notificar la entrega");
    requireDeliveryStage(DeliveryStage::ReceptionPhotographed, "notificar la entrega");

    delivery_stage_ = DeliveryStage::DeliveryNotified;
}

void DroneIbag151::requireFlying(const char* action) const {
    if (flight_state_ != FlightState::Flying) {
        throw DroneError(std::string("el drone debe estar en vuelo para ") + action);
    }
}

void DroneIbag151::requireLanded(const char* action) const {
    if (flight_state_ != FlightState::Landed) {
        throw DroneError(std::string("el drone debe estar en tierra para ") + action);
    }
}

void DroneIbag151::requirePositive(int amount, const char* action) const {
    if (amount <= 0) {
        throw DroneError(std::string("la cantidad debe ser mayor que cero para ") + action);
    }
}

void DroneIbag151::requireDeliveryStage(DeliveryStage expected, const char* action) const {
    if (delivery_stage_ != expected) {
        throw DroneError(std::string("no se puede ") + action +
                         " en el estado actual de la entrega");
    }
}

FlightState DroneIbag151::flightState() const {
    return flight_state_;
}

DeliveryStage DroneIbag151::deliveryStage() const {
    return delivery_stage_;
}

int DroneIbag151::altitude() const {
    return altitude_;
}

int DroneIbag151::heading() const {
    return heading_;
}

int DroneIbag151::speed() const {
    return speed_;
}

bool DroneIbag151::hasPackage() const {
    return delivery_stage_ == DeliveryStage::WithPackage;
}

}  // namespace ibag151
