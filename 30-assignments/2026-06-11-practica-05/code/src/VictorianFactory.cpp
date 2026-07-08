#include "VictorianFactory.hpp"

Chair* VictorianFactory::createChair() const {
    return new VictorianChair();
}

Sofa* VictorianFactory::createSofa() const {
    return new VictorianSofa();
}

CoffeeTable* VictorianFactory::createCoffeeTable() const {
    return new VictorianCoffeeTable();
}
