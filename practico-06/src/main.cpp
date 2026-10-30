// Consigna Marco Práctico 1 - Aplicación C++ con patrón Decorator
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>

#include "Hotel.hpp"
#include "Hostel.hpp"
#include "Apartamento.hpp"
#include "Piscina.hpp"
#include "Desayuno.hpp"
#include "Gimnasio.hpp"
#include "Wifi.hpp"

static void mostrarPresupuesto(const Alojamiento& a) {
    std::cout << "  " << a.getDescripcion() << " | $"
              << std::fixed << std::setprecision(2) << a.calcularPrecio()
              << " /noche" << std::endl;
}

int main() {
    std::cout << "=== SISTEMA DE PRESUPUESTO DE ALOJAMIENTOS ===" << std::endl;
    std::cout << "       (Patron Decorator en C++17)" << std::endl;
    std::cout << std::endl;

    // Demostracion con Hotel (componente concreto)
    std::cout << "--- Presupuestos con Hotel ---" << std::endl;
    Hotel hotelBase("Sheraton", 120.0);
    mostrarPresupuesto(hotelBase);

    Piscina hotelConPiscina(&hotelBase);
    mostrarPresupuesto(hotelConPiscina);

    Desayuno hotelConDesayuno(&hotelBase);
    mostrarPresupuesto(hotelConDesayuno);

    // Decorator apilado: Hotel + Piscina + Gimnasio
    Piscina conPiscina(&hotelBase);
    Gimnasio conPiscinaYGimnasio(&conPiscina);
    Wifi conTodo(&conPiscinaYGimnasio);
    mostrarPresupuesto(conTodo);

    std::cout << std::endl;

    // Extensibilidad: nuevos tipos de alojamiento sin modificar nada existente
    std::cout << "--- Extensibilidad: Hostel y Apartamento ---" << std::endl;
    Hostel hostelBase("Downtown Hostel", 45.0);
    mostrarPresupuesto(hostelBase);

    Desayuno hostelConDesayuno(&hostelBase);
    Wifi hostelConDesayunoYWifi(&hostelConDesayuno);
    mostrarPresupuesto(hostelConDesayunoYWifi);

    std::cout << std::endl;

    Apartamento aptoBase("Palermo Loft", 90.0);
    mostrarPresupuesto(aptoBase);

    Gimnasio aptoConGimnasio(&aptoBase);
    Piscina aptoConGimnasioYPiscina(&aptoConGimnasio);
    mostrarPresupuesto(aptoConGimnasioYPiscina);

    std::cout << std::endl;
    std::cout << "=== FIN DEL PRESUPUESTO ===" << std::endl;

    return 0;
}
