#pragma once
#include "Strategy.hpp"

class Coche : public Strategy {
public:
    void executeAlgorithm() const override;
};
