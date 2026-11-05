#include <iostream>

#include "ibag151/drone_ibag151.hpp"

int main() {
    ibag151::DroneIbag151 drone;

    std::cout << "Drone IBag151\n";
    std::cout << "Estado: "
              << (drone.flightState() == ibag151::FlightState::Landed ? "en tierra" : "en vuelo")
              << "\n";
    std::cout << "Altitud: " << drone.altitude() << " m\n";
    std::cout << "Velocidad: " << drone.speed() << " u\n";
    std::cout << "Rumbo: " << drone.heading() << " grados\n";
    std::cout << "Paquete a bordo: " << (drone.hasPackage() ? "si" : "no") << "\n";

    return 0;
}
