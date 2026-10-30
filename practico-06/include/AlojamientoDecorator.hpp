#ifndef ALOJAMIENTO_DECORATOR_HPP
#define ALOJAMIENTO_DECORATOR_HPP

#include "Alojamiento.hpp"
#include <string>

class AlojamientoDecorator : public Alojamiento {
protected:
    Alojamiento* alojamiento;
public:
    AlojamientoDecorator(Alojamiento* alojamiento);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
    virtual ~AlojamientoDecorator() = default;
};

#endif
