#include "format.hpp"

#include <sstream>

namespace partial02 {

std::string formatMoney(std::int64_t cents) {
    std::ostringstream os;
    bool negative = cents < 0;
    std::int64_t absCents = negative ? -cents : cents;
    std::int64_t pesos = absCents / 100;
    std::int64_t centavos = absCents % 100;
    if (negative) {
        os << "-";
    }
    os << pesos << "," << std::setw(2) << std::setfill('0') << centavos;
    return os.str();
}

}  // namespace partial02
