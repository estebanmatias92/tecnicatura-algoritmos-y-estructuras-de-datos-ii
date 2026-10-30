#ifndef PISCINA_HPP
#define PISCINA_HPP

#include "AlojamientoDecorator.hpp"
#include <string>

class Piscina : public AlojamientoDecorator {
public:
    Piscina(Alojamiento* alojamiento);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
