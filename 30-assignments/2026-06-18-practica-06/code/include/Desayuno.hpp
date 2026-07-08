#ifndef DESAYUNO_HPP
#define DESAYUNO_HPP

#include "AlojamientoDecorator.hpp"
#include <string>

class Desayuno : public AlojamientoDecorator {
public:
    Desayuno(Alojamiento* alojamiento);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
