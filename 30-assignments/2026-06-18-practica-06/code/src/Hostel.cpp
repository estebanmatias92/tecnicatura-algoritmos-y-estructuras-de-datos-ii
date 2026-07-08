#include "Hostel.hpp"

Hostel::Hostel(const std::string& nombre, double precioBase)
    : nombre(nombre), precioBase(precioBase) {}

std::string Hostel::getDescripcion() const {
    return "Hostel " + nombre;
}

double Hostel::calcularPrecio() const {
    return precioBase;
}
