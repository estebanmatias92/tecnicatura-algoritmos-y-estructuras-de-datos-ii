#include "Calculadora.hpp"

double Calculadora::sumar(double a, double b) const {
    return a + b;
}

double Calculadora::restar(double a, double b) const {
    return a - b;
}

double Calculadora::multiplicar(double a, double b) const {
    return a * b;
}

double Calculadora::dividir(double dividendo, double divisor) const {
    if (divisor == 0.0) {
        throw std::domain_error("Division por cero no permitida");
    }
    return dividendo / divisor;
}

double Calculadora::operar(char operador, double a, double b) const {
    switch (operador) {
        case '+': return sumar(a, b);
        case '-': return restar(a, b);
        case '*': return multiplicar(a, b);
        case '/': return dividir(a, b);
        default:
            throw std::invalid_argument("Operador no valido: use '+', '-', '*' o '/'");
    }
}
