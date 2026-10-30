#include "Hotel.hpp"

Hotel::Hotel(const std::string& nombre, double precioBase)
    : nombre(nombre), precioBase(precioBase) {}

std::string Hotel::getDescripcion() const {
    return "Hotel " + nombre;
}

double Hotel::calcularPrecio() const {
    return precioBase;
}
