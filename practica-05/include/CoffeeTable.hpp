#ifndef COFFEETABLE_HPP
#define COFFEETABLE_HPP

#include <iostream>
#include <string>

class CoffeeTable {
public:
    virtual ~CoffeeTable() = default;
    virtual bool hasSurface() const = 0;
    virtual void placeOn() const = 0;
    virtual std::string style() const = 0;
};

class ModernCoffeeTable : public CoffeeTable {
public:
    bool hasSurface() const override { return true; }
    void placeOn() const override { std::cout << "  [ModernCoffeeTable] Apoyas el cafe en una mesa de vidrio moderno.\n"; }
    std::string style() const override { return "Modern"; }
};

class VictorianCoffeeTable : public CoffeeTable {
public:
    bool hasSurface() const override { return true; }
    void placeOn() const override { std::cout << "  [VictorianCoffeeTable] Apoyas el cafe en una mesa de madera victoriana.\n"; }
    std::string style() const override { return "Victorian"; }
};

class ArtDecoCoffeeTable : public CoffeeTable {
public:
    bool hasSurface() const override { return true; }
    void placeOn() const override { std::cout << "  [ArtDecoCoffeeTable] Apoyas el cafe en una mesa Art Deco con detalles dorados.\n"; }
    std::string style() const override { return "ArtDeco"; }
};

#endif
