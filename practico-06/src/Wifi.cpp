#include "Wifi.hpp"

Wifi::Wifi(Alojamiento* alojamiento)
    : AlojamientoDecorator(alojamiento) {}

std::string Wifi::getDescripcion() const {
    return alojamiento->getDescripcion() + " + Wifi";
}

double Wifi::calcularPrecio() const {
    return alojamiento->calcularPrecio() + 10.0;
}
