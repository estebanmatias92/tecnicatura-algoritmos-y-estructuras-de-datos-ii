#include <iostream>
#include <string>
#include "templates.hpp"

int main() {
    std::cout << "=== TP 08 - Templates ===" << std::endl;

    // 5. Función con dos parámetros distintos (retorno / argumento)
    double d = convertir<double>(42);
    std::cout << "5. convertir<double>(42) = " << d << std::endl;

    // 6. Clase con parámetro como miembro
    Caja<int> caja(99);
    std::cout << "6. Caja<int> contenido = " << caja.obtener() << std::endl;

    // 7. Clase con dos parámetros: constructor (T), método sin args retorna R
    Convertidor<int, double> conv(7);
    std::cout << "7. Convertidor<int,double> resultado = " << conv.resultado() << std::endl;

    // 8. menor con argumentos del mismo tipo
    std::cout << "8. menor(2,3) = " << menor(2, 3) << std::endl;
    std::cout << "8. menor(6.0,4.0) = " << menor(6.0, 4.0) << std::endl;

    // 9. Comprobar int, double, float
    std::cout << "9. int menor = " << menor(10, 2) << std::endl;
    std::cout << "9. double menor = " << menor(8.5, 3.2) << std::endl;
    std::cout << "9. float menor = " << menor(2.5f, 9.1f) << std::endl;

    // 10. Argumentos de distintos tipos (dos posibilidades)
    // Con un solo parámetro de plantilla: requiere conversión implícita o deja ambigüedad
    // Probamos el caso con dos parámetros explícitos (función con T y U)
    std::cout << "10. menorDistintos(3, 4.5) = " << menorDistintos(3, 4.5) << std::endl;

    // También probamos con un parámetro de plantilla: compila si ambos pueden convertirse al mismo T
    std::cout << "10. menor(3.0, 4) = " << menor(3.0, 4.0) << std::endl;

    return 0;
}
