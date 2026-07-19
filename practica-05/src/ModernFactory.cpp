#include "ModernFactory.hpp"

Chair* ModernFactory::createChair() const {
    return new ModernChair();
}

Sofa* ModernFactory::createSofa() const {
    return new ModernSofa();
}

CoffeeTable* ModernFactory::createCoffeeTable() const {
    return new ModernCoffeeTable();
}
