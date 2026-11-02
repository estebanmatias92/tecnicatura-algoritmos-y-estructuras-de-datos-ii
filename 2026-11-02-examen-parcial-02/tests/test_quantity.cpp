#include "quantity.hpp"

#include <gtest/gtest.h>

using partial02::Quantity;

TEST(Quantity, PositiveValueIsValid) {
    Quantity q(1);
    EXPECT_EQ(q.value(), 1u);

    Quantity q500(500);
    EXPECT_EQ(q500.value(), 500u);
}

TEST(Quantity, ZeroIsRejected) {
    EXPECT_THROW(Quantity(0), std::invalid_argument);
}

TEST(Quantity, ExplicitConstructor) {
    // No se puede construir implícitamente desde unsigned
    static_assert(!std::is_convertible_v<unsigned, Quantity>,
                  "Quantity constructor must be explicit");
}
