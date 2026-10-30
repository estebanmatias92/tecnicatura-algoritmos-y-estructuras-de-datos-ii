#include "Navigator.hpp"
#include <iostream>

Navigator::Navigator() : strategy_(nullptr) {}
Navigator::~Navigator() {}

void Navigator::setStrategy(Strategy* s) {
    strategy_ = s;
}

Strategy* Navigator::getStrategy() const {
    return strategy_;
}

void Navigator::executeAlgorithm() const {
    if (strategy_) {
        strategy_->executeAlgorithm();
    } else {
        std::cout << "No hay estrategia configurada." << std::endl;
    }
}
