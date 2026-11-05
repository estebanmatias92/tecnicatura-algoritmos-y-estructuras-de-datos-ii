#include "ibag151/drone_ibag151.hpp"

namespace ibag151 {

void DroneIbag151::takeOff() {
    if (flight_state_ == FlightState::Flying) {
        throw DroneError("el drone ya esta en vuelo");
    }

    flight_state_ = FlightState::Flying;
}

void DroneIbag151::land() {
    // Implementation added in the green step of the TDD cycle.
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
