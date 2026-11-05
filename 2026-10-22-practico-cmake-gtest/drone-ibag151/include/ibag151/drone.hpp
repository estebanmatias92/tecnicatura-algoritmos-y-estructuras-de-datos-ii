#ifndef IBAG151_DRONE_HPP
#define IBAG151_DRONE_HPP

#include "drone_state.hpp"

namespace ibag151 {

/// Port that models the activities required by the assignment.
///
/// Callers depend on this abstraction (DIP), so the console adapter can be
/// tested with a fake drone and the concrete drone can evolve independently.
/// The interface grows one activity at a time, driven by its failing test.
class Drone {
public:
    virtual ~Drone() = default;

    /// Leaves the ground. Requires the drone to be landed.
    virtual void takeOff() = 0;

    /// Returns to the ground, resetting altitude and speed. Requires flight.
    virtual void land() = 0;

    /// Gains altitude. Requires flight and a positive amount.
    virtual void ascend(int meters) = 0;

    /// Loses altitude without reaching below ground. Requires flight.
    virtual void descend(int meters) = 0;

    /// Rotates 90 degrees clockwise. Requires flight.
    virtual void turnRight() = 0;

    /// Rotates 90 degrees counter-clockwise. Requires flight.
    virtual void turnLeft() = 0;

    /// Increases speed. Requires flight and a positive amount.
    virtual void accelerate(int amount) = 0;

    /// Reduces speed without going below zero. Requires flight.
    virtual void brake(int amount) = 0;

    /// Unloads the package. Requires landing with the package still on board.
    virtual void unloadPackage() = 0;

    virtual FlightState flightState() const = 0;
    virtual DeliveryStage deliveryStage() const = 0;
    virtual int altitude() const = 0;
    virtual int heading() const = 0;
    virtual int speed() const = 0;
    virtual bool hasPackage() const = 0;
};

}  // namespace ibag151

#endif  // IBAG151_DRONE_HPP
