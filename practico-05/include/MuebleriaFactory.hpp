#ifndef MUEBLERIA_FACTORY_HPP
#define MUEBLERIA_FACTORY_HPP

#include "Chair.hpp"
#include "Sofa.hpp"
#include "CoffeeTable.hpp"

class MuebleriaFactory {
public:
    virtual ~MuebleriaFactory() = default;
    virtual Chair* createChair() const = 0;
    virtual Sofa* createSofa() const = 0;
    virtual CoffeeTable* createCoffeeTable() const = 0;
    virtual std::string factoryStyle() const = 0;
};

#endif
