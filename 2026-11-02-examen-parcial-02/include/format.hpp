#ifndef PARTIAL02_FORMAT_HPP
#define PARTIAL02_FORMAT_HPP

#include <cstdint>
#include <iomanip>
#include <iosfwd>
#include <string>

namespace partial02 {

/// Formatea un importe en centavos como "1500,00" (sin separador de miles,
/// coma decimal, dos cifras).
std::string formatMoney(std::int64_t cents);

}  // namespace partial02

#endif  // PARTIAL02_FORMAT_HPP
