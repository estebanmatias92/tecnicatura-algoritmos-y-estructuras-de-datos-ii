#pragma once
#include "Strategy.hpp"

class TransportePublico : public Strategy {
public:
    void executeAlgorithm() const override;
};
