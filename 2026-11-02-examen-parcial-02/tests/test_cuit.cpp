#include "cuit.hpp"

#include <gtest/gtest.h>

using partial02::Cuit;

TEST(Cuit, ValidElevenDigits) {
    Cuit c("20123456789");
    EXPECT_EQ(c.value(), "20123456789");
}

TEST(Cuit, TenDigitsRejected) {
    EXPECT_THROW(Cuit("2012345678"), std::invalid_argument);
}

TEST(Cuit, TwelveDigitsRejected) {
    EXPECT_THROW(Cuit("201234567890"), std::invalid_argument);
}

TEST(Cuit, WithLettersRejected) {
    EXPECT_THROW(Cuit("20-12345678-3"), std::invalid_argument);
    EXPECT_THROW(Cuit("abcdefghijk"), std::invalid_argument);
}

TEST(Cuit, EmptyRejected) {
    EXPECT_THROW(Cuit(""), std::invalid_argument);
}

TEST(Cuit, ComparisonOperators) {
    Cuit a("20123456789");
    Cuit b("20123456789");
    Cuit c("27334455669");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a < c);
    EXPECT_FALSE(c < a);
}
