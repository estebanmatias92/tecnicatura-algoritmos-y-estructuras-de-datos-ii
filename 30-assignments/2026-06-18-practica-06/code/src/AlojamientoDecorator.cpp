#include "AlojamientoDecorator.hpp"

AlojamientoDecorator::AlojamientoDecorator(Alojamiento* alojamiento)
    : alojamiento(alojamiento) {}

std::string AlojamientoDecorator::getDescripcion() const {
    return alojamiento->getDescripcion();
}

double AlojamientoDecorator::calcularPrecio() const {
    return alojamiento->calcularPrecio();
}
