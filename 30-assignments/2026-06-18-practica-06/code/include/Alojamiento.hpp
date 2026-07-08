#ifndef ALOJAMIENTO_HPP
#define ALOJAMIENTO_HPP

#include <string>

class Alojamiento {
public:
    virtual std::string getDescripcion() const = 0;
    virtual double calcularPrecio() const = 0;
    virtual ~Alojamiento() = default;
};

#endif
