#pragma once

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void executeAlgorithm() const = 0;
};
