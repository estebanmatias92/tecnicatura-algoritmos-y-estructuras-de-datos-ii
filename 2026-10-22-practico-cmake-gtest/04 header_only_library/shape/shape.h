#pragma once
#include <string>
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string GetName() = 0;
};

inline void PrintShape(Shape& shape) {
    std::cout << shape.GetName() << std::endl;
}

void PrintShape(Shape& shape);