#include "Consola.hpp"
#include "Controlador.hpp"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    Consola consola;
    Controlador controlador;

    consola.mostrar("=== Calculadora GRASP (patron Controller) ===");
    consola.mostrar("Operaciones soportadas: +, -, *, /");
    consola.mostrar("Escribe 'salir' para terminar.");
    consola.mostrar("");

    while (true) {
        consola.mostrar("Ingresa operacion (ej: 5 + 3) o 'salir':");
        std::string linea = consola.leer();

        if (linea == "salir" || linea == "exit" || linea == "q") {
            consola.mostrar("Saliendo de la calculadora. ¡Hasta luego!");
            break;
        }

        // Parse simple: "a operador b"
        double a = 0.0, b = 0.0;
        char operador = 0;
        std::istringstream iss(linea);
        if (!(iss >> a >> operador >> b)) {
            consola.mostrarError("Formato invalido. Usa: numero operador numero (ej: 5 + 3)");
            continue;
        }

        std::string resultado = controlador.ejecutar(operador, a, b);
        consola.mostrar(resultado);
        consola.mostrar("");
    }

    return 0;
}
