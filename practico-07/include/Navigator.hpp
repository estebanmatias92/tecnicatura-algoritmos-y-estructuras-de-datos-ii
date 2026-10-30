#pragma once
#include "Strategy.hpp"

class Navigator {
private:
    Strategy* strategy_;
public:
    Navigator();
    ~Navigator();
    void setStrategy(Strategy* s);
    Strategy* getStrategy() const;
    void executeAlgorithm() const;
};
