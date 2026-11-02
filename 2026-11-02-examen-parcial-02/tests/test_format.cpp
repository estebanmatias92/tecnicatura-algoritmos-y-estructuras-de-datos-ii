#include "format.hpp"

#include <gtest/gtest.h>

#include <string>

using partial02::formatMoney;

TEST(Format, PositiveAmountTwoDecimals) {
    EXPECT_EQ(formatMoney(150000), "1500,00");
    EXPECT_EQ(formatMoney(750000), "7500,00");
    EXPECT_EQ(formatMoney(110000), "1100,00");
}

TEST(Format, ZeroAndSubPeso) {
    EXPECT_EQ(formatMoney(0), "0,00");
    EXPECT_EQ(formatMoney(5), "0,05");
    EXPECT_EQ(formatMoney(105), "1,05");
    EXPECT_EQ(formatMoney(150005), "1500,05");
}

TEST(Format, NegativeAmount) {
    EXPECT_EQ(formatMoney(-150000), "-1500,00");
    EXPECT_EQ(formatMoney(-5), "-0,05");
}
