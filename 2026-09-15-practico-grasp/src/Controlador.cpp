#include "Controlador.hpp"
#include <sstream>
#include <iomanip>

std::string Controlador::ejecutar(char operador, double a, double b) {
    try {
        double resultado = calculadora_.operar(operador, a, b);
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << a << " " << operador << " " << b << " = " << resultado;
        return oss.str();
    } catch (const std::exception& e) {
        return std::string("Error: ") + e.what();
    }
}
