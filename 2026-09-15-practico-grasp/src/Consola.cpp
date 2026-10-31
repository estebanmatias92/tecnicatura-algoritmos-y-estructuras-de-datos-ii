#include "Consola.hpp"
#include <iostream>
#include <iomanip>

void Consola::mostrar(const std::string& mensaje) const {
    std::cout << mensaje << std::endl;
}

std::string Consola::leer() const {
    std::string linea;
    std::getline(std::cin, linea);
    return linea;
}

void Consola::mostrarResultado(double resultado) const {
    std::cout << std::fixed << std::setprecision(2) << "Resultado: " << resultado << std::endl;
}

void Consola::mostrarError(const std::string& mensaje) const {
    std::cerr << "Error: " << mensaje << std::endl;
}
