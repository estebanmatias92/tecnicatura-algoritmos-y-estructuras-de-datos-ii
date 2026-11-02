#include "date.hpp"

#include <array>
#include <ctime>
#include <stdexcept>
#include <string>

namespace partial02 {

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Date: invalid month");
    }
    int max_day = days_in_month(year, month);
    if (day < 1 || day > max_day) {
        throw std::invalid_argument("Date: invalid day");
    }
}

Date Date::today() {
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    return Date(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
}

bool Date::is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::days_in_month(int year, int month) {
    static const std::array<int, 13> days{
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap(year)) {
        return 29;
    }
    return days[month];
}

bool Date::operator==(const Date& other) const noexcept {
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool Date::operator<(const Date& other) const noexcept {
    if (year_ != other.year_) {
        return year_ < other.year_;
    }
    if (month_ != other.month_) {
        return month_ < other.month_;
    }
    return day_ < other.day_;
}

std::string Date::to_string() const {
    char buf[11];
    std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", year_, month_, day_);
    return std::string(buf);
}

}  // namespace partial02
