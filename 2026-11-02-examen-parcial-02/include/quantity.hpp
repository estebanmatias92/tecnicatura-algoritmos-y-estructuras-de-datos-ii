#ifndef PARTIAL02_QUANTITY_HPP
#define PARTIAL02_QUANTITY_HPP

#include <cstddef>
#include <stdexcept>

namespace partial02 {

/// Cantidad de unidades de un Article dentro de un PurchaseOrder.
/// Value type inmutable: garantiza en el constructor que el valor sea > 0.
class Quantity {
public:
    explicit Quantity(unsigned value);

    unsigned value() const noexcept;

private:
    unsigned value_;
};

}  // namespace partial02

#endif  // PARTIAL02_QUANTITY_HPP
