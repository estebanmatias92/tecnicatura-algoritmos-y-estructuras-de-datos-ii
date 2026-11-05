#ifndef IBAG151_DRONE_STATE_HPP
#define IBAG151_DRONE_STATE_HPP

#include <stdexcept>
#include <string>

namespace ibag151 {

/// Whether the drone is on the ground or flying.
enum class FlightState {
    Landed,
    Flying,
};

/// Progress of the delivery workflow.
///
/// The order is strict: the package is unloaded, then the reception photo is
/// taken, and only then the delivery can be notified.
enum class DeliveryStage {
    WithPackage,
    PackageUnloaded,
    ReceptionPhotographed,
    DeliveryNotified,
};

/// Raised when an operation is not valid for the current drone state.
class DroneError : public std::runtime_error {
public:
    explicit DroneError(const std::string& message) : std::runtime_error(message) {}
};

}  // namespace ibag151

#endif  // IBAG151_DRONE_STATE_HPP
