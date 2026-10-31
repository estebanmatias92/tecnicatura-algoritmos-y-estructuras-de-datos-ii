#ifndef CONSOLA_HPP
#define CONSOLA_HPP

#include <string>

/**
 * @brief Interfaz de usuario por consola.
 *
 * Se encarga unicamente de la entrada/salida de datos. No conoce la logica
 * de calculo ni depende directamente de Calculadora: se comunica a traves
 * del Controlador, manteniendo bajo acoplamiento.
 */
class Consola {
public:
    Consola() = default;

    /**
     * @brief Muestra un mensaje por salida estandar.
     */
    void mostrar(const std::string& mensaje) const;

    /**
     * @brief Lee una linea de entrada estandar.
     */
    std::string leer() const;

    /**
     * @brief Muestra el resultado de una operacion.
     */
    void mostrarResultado(double resultado) const;

    /**
     * @brief Muestra un mensaje de error en salida de error estandar.
     */
    void mostrarError(const std::string& mensaje) const;
};

#endif // CONSOLA_HPP
