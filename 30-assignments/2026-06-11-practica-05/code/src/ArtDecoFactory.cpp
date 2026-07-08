#include "ArtDecoFactory.hpp"

Chair* ArtDecoFactory::createChair() const {
    return new ArtDecoChair();
}

Sofa* ArtDecoFactory::createSofa() const {
    return new ArtDecoSofa();
}

CoffeeTable* ArtDecoFactory::createCoffeeTable() const {
    return new ArtDecoCoffeeTable();
}
