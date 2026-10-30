#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>

// 5. Función plantilla: dos parámetros distintos, uno retorno y otro argumento.
template <typename R, typename A>
R convertir(A valor) {
    return static_cast<R>(valor);
}

// 6. Clase plantilla: parámetro como variable miembro.
template <typename T>
class Caja {
    T contenido;
public:
    Caja(T val) : contenido(val) {}
    T obtener() const { return contenido; }
    void establecer(T val) { contenido = val; }
};

// 7. Clase plantilla: dos parámetros, uno al constructor, otro como retorno de método sin argumentos.
template <typename T, typename R>
class Convertidor {
    T valor;
public:
    Convertidor(T v) : valor(v) {}
    R resultado() const { return static_cast<R>(valor); }
};

// 8. Función menor genérica.
template <typename T>
T menor(T a, T b) {
    return (a < b) ? a : b;
}

// 10. Variantes para argumentos de distintos tipos.
template <typename T, typename U>
T menorDistintos(T a, U b) {
    return (a < b) ? a : static_cast<T>(b);
}

#endif
