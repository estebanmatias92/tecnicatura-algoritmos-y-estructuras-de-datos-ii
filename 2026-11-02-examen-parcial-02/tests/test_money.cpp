#include "money.hpp"

#include <gtest/gtest.h>

using partial02::Money;

TEST(Money, StoresCents) {
    Money m(150000);  // 1500,00
    EXPECT_EQ(m.cents(), 150000);
}

TEST(Money, NegativeIsRejected) {
    EXPECT_THROW(Money(-1), std::invalid_argument);
}

TEST(Money, ZeroIsAllowed) {
    // Money(0) es técnicamente válido; Article rechaza precios de 0
    Money m(0);
    EXPECT_EQ(m.cents(), 0);
}

TEST(Money, ExplicitConstructor) {
    static_assert(!std::is_convertible_v<std::int64_t, Money>,
                  "Money constructor must be explicit");
}
