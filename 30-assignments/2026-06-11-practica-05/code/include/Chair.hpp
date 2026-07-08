#ifndef CHAIR_HPP
#define CHAIR_HPP

#include <iostream>
#include <string>

class Chair {
public:
    virtual ~Chair() = default;
    virtual bool hasLegs() const = 0;
    virtual void sitOn() const = 0;
    virtual std::string style() const = 0;
};

class ModernChair : public Chair {
public:
    bool hasLegs() const override { return false; }
    void sitOn() const override { std::cout << "  [ModernChair] Te sentas en una silla moderna minimalista.\n"; }
    std::string style() const override { return "Modern"; }
};

class VictorianChair : public Chair {
public:
    bool hasLegs() const override { return true; }
    void sitOn() const override { std::cout << "  [VictorianChair] Te sentas en una silla victoriana con patas talladas.\n"; }
    std::string style() const override { return "Victorian"; }
};

class ArtDecoChair : public Chair {
public:
    bool hasLegs() const override { return true; }
    void sitOn() const override { std::cout << "  [ArtDecoChair] Te sentas en una silla Art Deco elegante.\n"; }
    std::string style() const override { return "ArtDeco"; }
};

#endif
