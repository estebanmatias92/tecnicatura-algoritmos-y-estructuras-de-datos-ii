#ifndef PARTIAL02_CLOCK_HPP
#define PARTIAL02_CLOCK_HPP

#include "date.hpp"

namespace partial02 {

/// Puerto que entrega la fecha del sistema. Inyectable para que las pruebas
/// de fecha no dependan del día en que corren (AC-013, AC-014).
class Clock {
public:
    virtual ~Clock() = default;
    virtual Date now() = 0;
};

/// Implementación por defecto que usa Date::today().
class SystemClock : public Clock {
public:
    Date now() override { return Date::today(); }
};

}  // namespace partial02

#endif  // PARTIAL02_CLOCK_HPP
