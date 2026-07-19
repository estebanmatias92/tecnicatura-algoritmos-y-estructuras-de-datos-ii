#ifndef SOFA_HPP
#define SOFA_HPP

#include <iostream>
#include <string>

class Sofa {
public:
    virtual ~Sofa() = default;
    virtual bool hasCushions() const = 0;
    virtual void lieOn() const = 0;
    virtual std::string style() const = 0;
};

class ModernSofa : public Sofa {
public:
    bool hasCushions() const override { return true; }
    void lieOn() const override { std::cout << "  [ModernSofa] Te recostas en un sofa moderno de cuero.\n"; }
    std::string style() const override { return "Modern"; }
};

class VictorianSofa : public Sofa {
public:
    bool hasCushions() const override { return true; }
    void lieOn() const override { std::cout << "  [VictorianSofa] Te recostas en un sofa victoriano con tapizado clasico.\n"; }
    std::string style() const override { return "Victorian"; }
};

class ArtDecoSofa : public Sofa {
public:
    bool hasCushions() const override { return true; }
    void lieOn() const override { std::cout << "  [ArtDecoSofa] Te recostas en un sofa Art Deco de terciopelo.\n"; }
    std::string style() const override { return "ArtDeco"; }
};

#endif
