#ifndef HOSTEL_HPP
#define HOSTEL_HPP

#include "Alojamiento.hpp"
#include <string>

class Hostel : public Alojamiento {
private:
    std::string nombre;
    double precioBase;
public:
    Hostel(const std::string& nombre, double precioBase);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
