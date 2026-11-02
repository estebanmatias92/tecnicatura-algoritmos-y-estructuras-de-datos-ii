#include "supplier.hpp"

#include <gtest/gtest.h>

using partial02::Cuit;
using partial02::Supplier;

TEST(Supplier, ValidSupplier) {
    Supplier s(Cuit("20123456789"), "Cauchos del Sur S.A.");
    EXPECT_EQ(s.cuit().value(), "20123456789");
    EXPECT_EQ(s.businessName(), "Cauchos del Sur S.A.");
}

TEST(Supplier, InvalidCuitRejected) {
    EXPECT_THROW(Supplier(Cuit("2012345678"), "X"), std::invalid_argument);
}

TEST(Supplier, EmptyBusinessNameRejected) {
    EXPECT_THROW(Supplier(Cuit("20123456789"), ""), std::invalid_argument);
}

TEST(Supplier, CanModifyBusinessName) {
    Supplier s(Cuit("20123456789"), "Nombre viejo");
    s.businessName("Nombre nuevo");
    EXPECT_EQ(s.businessName(), "Nombre nuevo");
    // El CUIT no cambia (es la identidad)
    EXPECT_EQ(s.cuit().value(), "20123456789");
}

TEST(Supplier, ComparisonByCuit) {
    Supplier a(Cuit("20123456789"), "A");
    Supplier b(Cuit("27334455669"), "B");

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}
