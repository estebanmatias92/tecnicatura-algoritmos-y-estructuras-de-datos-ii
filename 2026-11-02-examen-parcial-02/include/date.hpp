#ifndef PARTIAL02_DATE_HPP
#define PARTIAL02_DATE_HPP

#include <string>

namespace partial02 {

/// Fecha de calendario (día, mes, año). Parsea y valida AAAA-MM-DD,
/// rechazando fechas inexistentes como 2026-02-30.
class Date {
public:
    /// Construye desde componentes numéricos. Valida el calendario.
    Date(int year, int month, int day);

    /// Fecha del sistema en el momento de la llamada.
    static Date today();

    int year() const noexcept { return year_; }
    int month() const noexcept { return month_; }
    int day() const noexcept { return day_; }

    bool operator==(const Date& other) const noexcept;
    bool operator!=(const Date& other) const noexcept { return !(*this == other); }
    bool operator<(const Date& other) const noexcept;
    bool operator>=(const Date& other) const noexcept { return !(*this < other); }

    std::string to_string() const;

private:
    int year_;
    int month_;
    int day_;

    static bool is_leap(int year);
    static int days_in_month(int year, int month);
};

}  // namespace partial02

#endif  // PARTIAL02_DATE_HPP
