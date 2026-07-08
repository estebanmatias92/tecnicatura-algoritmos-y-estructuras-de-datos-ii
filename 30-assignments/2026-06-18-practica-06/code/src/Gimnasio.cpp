#include "Gimnasio.hpp"

Gimnasio::Gimnasio(Alojamiento* alojamiento)
    : AlojamientoDecorator(alojamiento) {}

std::string Gimnasio::getDescripcion() const {
    return alojamiento->getDescripcion() + " + Gimnasio";
}

double Gimnasio::calcularPrecio() const {
    return alojamiento->calcularPrecio() + 20.0;
}
