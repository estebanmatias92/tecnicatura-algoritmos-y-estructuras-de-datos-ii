#include "cuit.hpp"

#include <stdexcept>

namespace partial02 {

Cuit::Cuit(std::string digits) : digits_(std::move(digits)) {
    if (digits_.size() != 11) {
        throw std::invalid_argument("Cuit must have exactly 11 digits");
    }
    for (char c : digits_) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("Cuit must contain only digits");
        }
    }
}

}  // namespace partial02
