#ifndef CALCULADORA_HPP
#define CALCULADORA_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Calculadora que implementa las cuatro operaciones básicas.
 *
 * Aplica el patron GRASP Information Expert: es la clase que conoce los
 * operandos y, por tanto, la candidata natural para recibir la responsabilidad
 * de calcular el resultado de una operacion aritmetica.
 *
 * No depende de ninguna interfaz de usuario: solo expone operaciones puras.
 */
class Calculadora {
public:
    Calculadora() = default;

    /**
     * @brief Suma dos operandos.
     */
    double sumar(double a, double b) const;

    /**
     * @brief Resta dos operandos.
     */
    double restar(double a, double b) const;

    /**
     * @brief Multiplica dos operandos.
     */
    double multiplicar(double a, double b) const;

    /**
     * @brief Divide dos operandos. Lanza std::domain_error si el divisor es cero.
     */
    double dividir(double dividendo, double divisor) const;

    /**
     * @brief Ejecuta la operacion indicada por el operador sobre dos operandos.
     * @param operador Uno de '+', '-', '*', '/'.
     * @throws std::invalid_argument si el operador no es valido.
     */
    double operar(char operador, double a, double b) const;
};

#endif // CALCULADORA_HPP
