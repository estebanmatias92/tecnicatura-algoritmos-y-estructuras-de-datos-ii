#ifndef GIMNASIO_HPP
#define GIMNASIO_HPP

#include "AlojamientoDecorator.hpp"
#include <string>

class Gimnasio : public AlojamientoDecorator {
public:
    Gimnasio(Alojamiento* alojamiento);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
