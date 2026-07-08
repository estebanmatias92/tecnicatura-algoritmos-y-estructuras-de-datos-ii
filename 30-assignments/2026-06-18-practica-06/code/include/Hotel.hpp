#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "Alojamiento.hpp"
#include <string>

class Hotel : public Alojamiento {
private:
    std::string nombre;
    double precioBase;
public:
    Hotel(const std::string& nombre, double precioBase);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
