#include <iostream>
#include "shape.h"

int main() {
    Shape s;
    s.GetName(); // o el método que tengas declarado en shape.h
    std::cout << "Shape name: " << s.GetName() << std::endl;

    return 0;
}
