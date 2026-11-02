#include "quantity.hpp"

namespace partial02 {

Quantity::Quantity(unsigned value) : value_(value) {
    if (value == 0) {
        throw std::invalid_argument("Quantity must be greater than zero");
    }
}

unsigned Quantity::value() const noexcept {
    return value_;
}

}  // namespace partial02
