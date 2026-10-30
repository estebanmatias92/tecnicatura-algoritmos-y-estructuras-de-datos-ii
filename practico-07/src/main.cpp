#include <iostream>
#include "Navigator.hpp"
#include "Peaton.hpp"
#include "Coche.hpp"
#include "TransportePublico.hpp"

int main() {
    Navigator navigator;

    Peaton peaton;
    Coche coche;
    TransportePublico tp;

    std::cout << "=== Patrón Strategy: Navegación por medio de transporte ===" << std::endl;

    navigator.setStrategy(&peaton);
    navigator.executeAlgorithm();

    navigator.setStrategy(&coche);
    navigator.executeAlgorithm();

    navigator.setStrategy(&tp);
    navigator.executeAlgorithm();

    return 0;
}
