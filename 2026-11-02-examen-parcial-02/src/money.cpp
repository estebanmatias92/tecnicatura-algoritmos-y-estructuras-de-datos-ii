#include "money.hpp"

namespace partial02 {

Money::Money(std::int64_t cents) : cents_(cents) {
    if (cents < 0) {
        throw std::invalid_argument("Money cannot be negative");
    }
}

std::int64_t Money::cents() const noexcept {
    return cents_;
}

}  // namespace partial02
