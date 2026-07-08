#include "Apartamento.hpp"

Apartamento::Apartamento(const std::string& nombre, double precioBase)
    : nombre(nombre), precioBase(precioBase) {}

std::string Apartamento::getDescripcion() const {
    return "Apartamento " + nombre;
}

double Apartamento::calcularPrecio() const {
    return precioBase;
}
