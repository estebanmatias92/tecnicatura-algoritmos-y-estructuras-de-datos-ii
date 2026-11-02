#ifndef PARTIAL02_ORDERNUMBER_HPP
#define PARTIAL02_ORDERNUMBER_HPP

#include <cstddef>

namespace partial02 {

/// Número de pedido: identificador único y autogenerado.
class OrderNumber {
public:
    explicit OrderNumber(unsigned value);

    unsigned value() const noexcept { return value_; }

    bool operator==(const OrderNumber& other) const noexcept { return value_ == other.value_; }
    bool operator!=(const OrderNumber& other) const noexcept { return !(*this == other); }
    bool operator<(const OrderNumber& other) const noexcept { return value_ < other.value_; }

private:
    unsigned value_;
};

}  // namespace partial02

#endif  // PARTIAL02_ORDERNUMBER_HPP
