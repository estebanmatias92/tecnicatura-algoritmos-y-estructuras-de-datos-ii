#include "purchaseorder.hpp"

#include "article.hpp"
#include "date.hpp"
#include "money.hpp"
#include "quantity.hpp"
#include "supplier.hpp"

#include <gtest/gtest.h>

using partial02::Article;
using partial02::Cuit;
using partial02::Date;
using partial02::Money;
using partial02::OrderNumber;
using partial02::PurchaseOrder;
using partial02::Quantity;
using partial02::Supplier;

namespace {

Supplier make_supplier() {
    return Supplier(Cuit("20123456789"), "Cauchos del Sur S.A.");
}

Article make_article(const std::string& code, std::int64_t cents) {
    return Article(code, "Desc", Money(cents));
}

}  // namespace

TEST(PurchaseOrder, ValidOrder) {
    Supplier s = make_supplier();
    Article a = make_article("CAU-001", 150000);

    PurchaseOrder po(OrderNumber(1), &s, Date(2026, 10, 20), Date(2026, 11, 5),
                     {{&a, Quantity(500)}});

    EXPECT_EQ(po.number().value(), 1u);
    EXPECT_EQ(po.supplier()->cuit().value(), "20123456789");
    EXPECT_EQ(po.items().size(), 1u);
    EXPECT_EQ(po.total().cents(), 75000000);  // 150000 * 500 = 75,000,000 centavos
}

TEST(PurchaseOrder, NoItemsRejected) {
    Supplier s = make_supplier();
    EXPECT_THROW(PurchaseOrder(OrderNumber(1), &s, Date(2026, 10, 20), Date(2026, 11, 5),
                               {}),
                 std::invalid_argument);
}

TEST(PurchaseOrder, DeliveryBeforeCreationRejected) {
    Supplier s = make_supplier();
    Article a = make_article("CAU-001", 150000);
    EXPECT_THROW(PurchaseOrder(OrderNumber(1), &s, Date(2026, 11, 5), Date(2026, 10, 20),
                               {{&a, Quantity(1)}}),
                 std::invalid_argument);
}

TEST(PurchaseOrder, NullSupplierRejected) {
    Article a = make_article("CAU-001", 150000);
    EXPECT_THROW(PurchaseOrder(OrderNumber(1), nullptr, Date(2026, 10, 20), Date(2026, 11, 5),
                               {{&a, Quantity(1)}}),
                 std::invalid_argument);
}

TEST(PurchaseOrder, TotalSumsSubtotals) {
    Supplier s = make_supplier();
    Article a = make_article("CAU-001", 150000);  // 1500,00
    Article b = make_article("AZU-002", 80000);    // 800,00

    PurchaseOrder po(OrderNumber(1), &s, Date(2026, 10, 20), Date(2026, 11, 5),
                     {{&a, Quantity(2)}, {&b, Quantity(3)}});

    // 2*150000 + 3*80000 = 300000 + 240000 = 540000 centavos
    EXPECT_EQ(po.total().cents(), 540000);
}

TEST(PurchaseOrder, ComparisonByNumber) {
    Supplier s = make_supplier();
    Article a = make_article("CAU-001", 150000);

    PurchaseOrder a1(OrderNumber(1), &s, Date(2026, 10, 20), Date(2026, 11, 5),
                     {{&a, Quantity(1)}});
    PurchaseOrder a2(OrderNumber(2), &s, Date(2026, 10, 20), Date(2026, 11, 5),
                     {{&a, Quantity(1)}});

    EXPECT_TRUE(a1 < a2);
    EXPECT_FALSE(a2 < a1);
}

TEST(PurchaseOrder, SameDeliveryAsCreationIsValid) {
    Supplier s = make_supplier();
    Article a = make_article("CAU-001", 150000);
    EXPECT_NO_THROW(PurchaseOrder(OrderNumber(1), &s, Date(2026, 10, 20), Date(2026, 10, 20),
                                  {{&a, Quantity(1)}}));
}
