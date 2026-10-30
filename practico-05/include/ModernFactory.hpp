#ifndef MODERN_FACTORY_HPP
#define MODERN_FACTORY_HPP

#include "MuebleriaFactory.hpp"

class ModernFactory : public MuebleriaFactory {
public:
    Chair* createChair() const override;
    Sofa* createSofa() const override;
    CoffeeTable* createCoffeeTable() const override;
    std::string factoryStyle() const override { return "Modern"; }
};

#endif
