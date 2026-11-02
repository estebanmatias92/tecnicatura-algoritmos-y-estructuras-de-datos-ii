#include <string>

class Shape {
public:
	virtual std::string GetName() = 0;
};

void PrintShape(Shape& shape);