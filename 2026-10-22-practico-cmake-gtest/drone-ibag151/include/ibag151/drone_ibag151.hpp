#ifndef IBAG151_DRONE_IBAG151_HPP
#define IBAG151_DRONE_IBAG151_HPP

#include "drone.hpp"

namespace ibag151 {

/// Concrete drone "IBag151".
///
/// It owns its state (Information Expert): altitude, heading, speed, flight
/// state and delivery stage are private and only change through operations
/// that validate the current state.
class DroneIbag151 : public Drone {
public:
    DroneIbag151() = default;

    void takeOff() override;
    void land() override;
    void ascend(int meters) override;
    void descend(int meters) override;
    void turnRight() override;
    void turnLeft() override;
    void accelerate(int amount) override;
    void brake(int amount) override;
    void unloadPackage() override;

    FlightState flightState() const override;
    DeliveryStage deliveryStage() const override;
    int altitude() const override;
    int heading() const override;
    int speed() const override;
    bool hasPackage() const override;

private:
    void requireFlying(const char* action) const;
    void requireLanded(const char* action) const;
    void requirePositive(int amount, const char* action) const;
    void requireDeliveryStage(DeliveryStage expected, const char* action) const;

    FlightState flight_state_{FlightState::Landed};
    DeliveryStage delivery_stage_{DeliveryStage::WithPackage};
    int altitude_{0};
    int heading_{0};
    int speed_{0};
};

}  // namespace ibag151

#endif  // IBAG151_DRONE_IBAG151_HPP
