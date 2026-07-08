#ifndef WIFI_HPP
#define WIFI_HPP

#include "AlojamientoDecorator.hpp"
#include <string>

class Wifi : public AlojamientoDecorator {
public:
    Wifi(Alojamiento* alojamiento);
    std::string getDescripcion() const override;
    double calcularPrecio() const override;
};

#endif
