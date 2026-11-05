#include <iostream>

#include "ibag151/console_interface.hpp"
#include "ibag151/drone_ibag151.hpp"

int main() {
    ibag151::DroneIbag151 drone;
    ibag151::ConsoleInterface console(std::cin, std::cout, drone);

    return console.run();
}
