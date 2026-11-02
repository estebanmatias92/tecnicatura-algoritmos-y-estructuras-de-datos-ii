#include "date.hpp"

#include <gtest/gtest.h>

using partial02::Date;

TEST(Date, ValidDate) {
    Date d(2026, 11, 2);
    EXPECT_EQ(d.year(), 2026);
    EXPECT_EQ(d.month(), 11);
    EXPECT_EQ(d.day(), 2);
    EXPECT_EQ(d.to_string(), "2026-11-02");
}

TEST(Date, InvalidMonth) {
    EXPECT_THROW(Date(2026, 0, 1), std::invalid_argument);
    EXPECT_THROW(Date(2026, 13, 1), std::invalid_argument);
}

TEST(Date, InvalidDay) {
    EXPECT_THROW(Date(2026, 1, 0), std::invalid_argument);
    EXPECT_THROW(Date(2026, 1, 32), std::invalid_argument);
}

TEST(Date, February2026Has28Days) {
    EXPECT_NO_THROW(Date(2026, 2, 28));
    EXPECT_THROW(Date(2026, 2, 29), std::invalid_argument);
}

TEST(Date, LeapYearFebruary29) {
    EXPECT_NO_THROW(Date(2024, 2, 29));
    EXPECT_NO_THROW(Date(2000, 2, 29));
    EXPECT_THROW(Date(2023, 2, 29), std::invalid_argument);
    EXPECT_THROW(Date(1900, 2, 29), std::invalid_argument);
}

TEST(Date, AprilHas30Days) {
    EXPECT_NO_THROW(Date(2026, 4, 30));
    EXPECT_THROW(Date(2026, 4, 31), std::invalid_argument);
}

TEST(Date, ComparisonOperators) {
    Date a(2026, 1, 1);
    Date b(2026, 1, 2);
    Date c(2026, 1, 1);

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(a >= c);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a == b);
}

TEST(Date, TodayIsReasonable) {
    Date today = Date::today();
    EXPECT_GE(today.year(), 2026);
    EXPECT_GE(today.month(), 1);
    EXPECT_LE(today.month(), 12);
    EXPECT_GE(today.day(), 1);
    EXPECT_LE(today.day(), 31);
}
