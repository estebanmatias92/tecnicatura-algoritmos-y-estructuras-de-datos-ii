#ifndef PARTIAL02_CUIT_HPP
#define PARTIAL02_CUIT_HPP

#include <string>

namespace partial02 {

/// CUIT de un proveedor: exactamente 11 dígitos numéricos.
/// Es la identidad del proveedor en el sistema (clave única).
class Cuit {
public:
    explicit Cuit(std::string digits);

    const std::string& value() const noexcept { return digits_; }

    bool operator==(const Cuit& other) const noexcept { return digits_ == other.digits_; }
    bool operator!=(const Cuit& other) const noexcept { return !(*this == other); }
    bool operator<(const Cuit& other) const noexcept { return digits_ < other.digits_; }

private:
    std::string digits_;
};

}  // namespace partial02

#endif  // PARTIAL02_CUIT_HPP
