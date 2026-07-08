#include "Desayuno.hpp"

Desayuno::Desayuno(Alojamiento* alojamiento)
    : AlojamientoDecorator(alojamiento) {}

std::string Desayuno::getDescripcion() const {
    return alojamiento->getDescripcion() + " + Desayuno";
}

double Desayuno::calcularPrecio() const {
    return alojamiento->calcularPrecio() + 15.0;
}
