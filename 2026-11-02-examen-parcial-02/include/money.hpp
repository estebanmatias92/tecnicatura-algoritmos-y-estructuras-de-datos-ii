#ifndef PARTIAL02_MONEY_HPP
#define PARTIAL02_MONEY_HPP

#include <cstdint>
#include <stdexcept>

namespace partial02 {

/// Importe en centavos, entero de 64 bits. No admite punto flotante.
/// No conoce moneda: el sistema opera en ARS.
class Money {
public:
    explicit Money(std::int64_t cents);

    std::int64_t cents() const noexcept;

private:
    std::int64_t cents_;
};

}  // namespace partial02

#endif  // PARTIAL02_MONEY_HPP
