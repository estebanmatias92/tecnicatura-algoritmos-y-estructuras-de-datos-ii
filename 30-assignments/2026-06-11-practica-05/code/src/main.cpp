#include <iostream>
#include <memory>
#include <vector>

#include "MuebleriaFactory.hpp"
#include "ModernFactory.hpp"
#include "VictorianFactory.hpp"
#include "ArtDecoFactory.hpp"

static void showFamily(const MuebleriaFactory& factory) {
    std::cout << "\n=== Familia " << factory.factoryStyle() << " ===\n";

    std::unique_ptr<Chair>       chair(factory.createChair());
    std::unique_ptr<Sofa>        sofa(factory.createSofa());
    std::unique_ptr<CoffeeTable> table(factory.createCoffeeTable());

    chair->sitOn();
    sofa->lieOn();
    table->placeOn();

    std::cout << "  (Patas silla: " << (chair->hasLegs() ? "si" : "no")
              << " | Almohadones sofa: " << (sofa->hasCushions() ? "si" : "no")
              << " | Superficie mesa: " << (table->hasSurface() ? "si" : "no") << ")\n";
}

int main() {
    std::vector<std::unique_ptr<MuebleriaFactory>> factories;
    factories.push_back(std::make_unique<ModernFactory>());
    factories.push_back(std::make_unique<VictorianFactory>());
    factories.push_back(std::make_unique<ArtDecoFactory>());

    for (const auto& f : factories) {
        showFamily(*f);
    }

    std::cout << "\n--- Todos los muebles pertenecen a su familia correspondiente ---\n";
    return 0;
}
