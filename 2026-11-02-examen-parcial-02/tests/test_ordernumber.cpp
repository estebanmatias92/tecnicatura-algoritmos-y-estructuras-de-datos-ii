#include "ordernumber.hpp"

#include <gtest/gtest.h>

using partial02::OrderNumber;

TEST(OrderNumber, WrapsUnsigned) {
    OrderNumber n(42);
    EXPECT_EQ(n.value(), 42u);
}

TEST(OrderNumber, ZeroIsValid) {
    // OrderNumber(0) es válido; la asignación real empieza desde 1
    OrderNumber n(0);
    EXPECT_EQ(n.value(), 0u);
}

TEST(OrderNumber, ComparisonOperators) {
    OrderNumber a(1);
    OrderNumber b(2);
    OrderNumber c(1);

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a == b);
}
