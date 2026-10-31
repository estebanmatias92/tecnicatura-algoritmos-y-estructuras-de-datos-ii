#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include <string>
#include "Calculadora.hpp"

/**
 * @brief Controlador (patron GRASP Controller).
 *
 * Recibe y coordina una operacion que proviene de la interfaz de usuario,
 * actuando como intermediario entre la consola y la logica de negocio
 * (Calculadora). La consola no conoce directamente a la calculadora.
 */
class Controlador {
public:
    Controlador() = default;

    /**
     * @brief Ejecuta una operacion aritmetica y devuelve el resultado como texto
     * listo para mostrar por consola.
     * @param operador Uno de '+', '-', '*', '/'.
     * @param a Primer operando.
     * @param b Segundo operando.
     * @return Cadena con el resultado o un mensaje de error.
     */
    std::string ejecutar(char operador, double a, double b);

private:
    Calculadora calculadora_;
};

#endif // CONTROLADOR_HPP
