#ifndef APARTAMENTO_HPP
#define APARTAMENTO_HPP

#include "Alojamiento.hpp"
#include <string>

class Apartamento : public Alojamiento {
private:
    std::string nombre;
    double precioBase;
public:
    Apartamento(const std::string& nombre, double precioBase);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
