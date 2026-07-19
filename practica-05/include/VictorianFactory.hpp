#ifndef VICTORIAN_FACTORY_HPP
#define VICTORIAN_FACTORY_HPP

#include "MuebleriaFactory.hpp"

class VictorianFactory : public MuebleriaFactory {
public:
    Chair* createChair() const override;
    Sofa* createSofa() const override;
    CoffeeTable* createCoffeeTable() const override;
    std::string factoryStyle() const override { return "Victorian"; }
};

#endif
