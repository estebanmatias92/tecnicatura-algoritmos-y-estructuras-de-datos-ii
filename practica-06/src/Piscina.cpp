#include "Piscina.hpp"

Piscina::Piscina(Alojamiento* alojamiento)
    : AlojamientoDecorator(alojamiento) {}

std::string Piscina::getDescripcion() const {
    return alojamiento->getDescripcion() + " + Piscina";
}

double Piscina::calcularPrecio() const {
    return alojamiento->calcularPrecio() + 35.0;
}
