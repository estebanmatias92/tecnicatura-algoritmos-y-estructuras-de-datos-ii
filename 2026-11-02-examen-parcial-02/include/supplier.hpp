#ifndef PARTIAL02_SUPPLIER_HPP
#define PARTIAL02_SUPPLIER_HPP

#include "cuit.hpp"

#include <string>

namespace partial02 {

/// Proveedor: la única entidad con CRUD completo en esta versión.
class Supplier {
public:
    Supplier(Cuit cuit, std::string businessName);

    const Cuit& cuit() const noexcept { return cuit_; }
    const std::string& businessName() const noexcept { return businessName_; }

    void businessName(std::string name) { businessName_ = std::move(name); }

    bool operator==(const Supplier& other) const noexcept { return cuit_ == other.cuit_; }
    bool operator!=(const Supplier& other) const noexcept { return !(*this == other); }
    bool operator<(const Supplier& other) const noexcept { return cuit_ < other.cuit_; }

private:
    Cuit cuit_;
    std::string businessName_;
};

}  // namespace partial02

#endif  // PARTIAL02_SUPPLIER_HPP
