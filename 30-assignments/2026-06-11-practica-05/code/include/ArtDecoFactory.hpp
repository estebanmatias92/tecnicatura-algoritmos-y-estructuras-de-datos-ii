#ifndef ART_DECO_FACTORY_HPP
#define ART_DECO_FACTORY_HPP

#include "MuebleriaFactory.hpp"

class ArtDecoFactory : public MuebleriaFactory {
public:
    Chair* createChair() const override;
    Sofa* createSofa() const override;
    CoffeeTable* createCoffeeTable() const override;
    std::string factoryStyle() const override { return "ArtDeco"; }
};

#endif
