#include "supplier.hpp"

#include <stdexcept>

namespace partial02 {

Supplier::Supplier(Cuit cuit, std::string businessName)
    : cuit_(std::move(cuit)), businessName_(std::move(businessName)) {
    if (businessName_.empty()) {
        throw std::invalid_argument("Business name cannot be empty");
    }
}

}  // namespace partial02
