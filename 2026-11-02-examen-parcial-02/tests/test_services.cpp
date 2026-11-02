#include "article.hpp"
#include "article_catalog.hpp"
#include "clock.hpp"
#include "cuit.hpp"
#include "date.hpp"
#include "domain_error.hpp"
#include "in_memory_order_number_sequence.hpp"
#include "inmemory_repository.hpp"
#include "money.hpp"
#include "order_number_sequence.hpp"
#include "ordernumber.hpp"
#include "purchase_order_service.hpp"
#include "supplier.hpp"
#include "supplier_service.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using partial02::Article;
using partial02::ArticleCatalog;
using partial02::Clock;
using partial02::ConflictError;
using partial02::Cuit;
using partial02::Date;
using partial02::DomainError;
using partial02::ErrorCode;
using partial02::InMemoryOrderNumberSequence;
using partial02::InMemoryRepository;
using partial02::Money;
using partial02::NotFoundError;
using partial02::OrderNumber;
using partial02::PurchaseOrder;
using partial02::PurchaseOrderService;
using partial02::Supplier;
using partial02::SupplierService;
using partial02::ValidationError;

namespace {

// Reloj fijo: las pruebas de fecha no dependen del día en que corren (ADR-0005).
class FixedClock : public Clock {
public:
    explicit FixedClock(const Date& today) : today_(today) {}
    Date now() override { return today_; }

private:
    Date today_;
};

// Harness: servicios cableados con repositorios en memoria y un artículo
// `CAU-001` en el catálogo. Reloj fijado en 2026-11-02.
struct Fixture {
    InMemoryRepository<Supplier, Cuit> supplierRepo{
        [](const Supplier& s) { return s.cuit(); }};
    InMemoryRepository<partial02::PurchaseOrder, OrderNumber> orderRepo{
        [](const partial02::PurchaseOrder& o) { return o.number(); }};
    ArticleCatalog catalog;
    InMemoryOrderNumberSequence sequence;
    FixedClock clock{Date(2026, 11, 2)};

    SupplierService supplierService{supplierRepo};
    PurchaseOrderService orderService{supplierRepo, catalog, orderRepo,
                                      sequence, clock};

    Fixture() {
        catalog.add(Article("CAU-001", "Caucho natural", Money(150000)));
        supplierRepo.add(Supplier(Cuit("20123456789"), "Cauchos del Sur S.A."));
    }
};

}  // namespace

// ---------- SupplierService ----------

TEST(SupplierService, AddValidSupplier) {
    Fixture f;
    EXPECT_NO_THROW(f.supplierService.add(Cuit("20234567891"),
                                          "Insumos Andinos S.R.L."));
    auto list = f.supplierService.list();
    ASSERT_EQ(list.size(), 2u);
    EXPECT_EQ(list[1]->businessName(), "Insumos Andinos S.R.L.");
}

TEST(SupplierService, AddDuplicateCuitRejected) {
    Fixture f;
    try {
        f.supplierService.add(Cuit("20123456789"), "Otro nombre");
        FAIL() << "debería haber lanzado ConflictError";
    } catch (const ConflictError& e) {
        EXPECT_EQ(e.code(), ErrorCode::DuplicateCuit);
    }
}

TEST(SupplierService, AddEmptyBusinessNameRejected) {
    Fixture f;
    try {
        f.supplierService.add(Cuit("20234567891"), "");
        FAIL() << "debería haber lanzado ValidationError";
    } catch (const ValidationError& e) {
        EXPECT_EQ(e.code(), ErrorCode::EmptyBusinessName);
    }
}

TEST(SupplierService, UpdateNotFoundRejected) {
    Fixture f;
    try {
        f.supplierService.update(Cuit("99999999999"), "Nuevo nombre");
        FAIL() << "debería haber lanzado NotFoundError";
    } catch (const NotFoundError& e) {
        EXPECT_EQ(e.code(), ErrorCode::UnknownSupplier);
    }
}

TEST(SupplierService, UpdateValid) {
    Fixture f;
    EXPECT_NO_THROW(f.supplierService.update(Cuit("20123456789"),
                                             "Nuevo nombre S.A."));
    const Supplier* s = f.supplierRepo.find(Cuit("20123456789"));
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->businessName(), "Nuevo nombre S.A.");
}

TEST(SupplierService, RemoveNotFoundRejected) {
    Fixture f;
    try {
        f.supplierService.remove(Cuit("99999999999"));
        FAIL() << "debería haber lanzado NotFoundError";
    } catch (const NotFoundError& e) {
        EXPECT_EQ(e.code(), ErrorCode::UnknownSupplier);
    }
}

TEST(SupplierService, RemoveValid) {
    Fixture f;
    EXPECT_NO_THROW(f.supplierService.remove(Cuit("20123456789")));
    EXPECT_EQ(f.supplierRepo.find(Cuit("20123456789")), nullptr);
    EXPECT_TRUE(f.supplierService.list().empty());
}

// ---------- PurchaseOrderService ----------

TEST(PurchaseOrderService, UnknownSupplierRejected) {
    Fixture f;
    try {
        f.orderService.create(Cuit("99999999999"), Date(2026, 11, 10),
                              {{"CAU-001", 5}});
        FAIL() << "debería haber lanzado NotFoundError";
    } catch (const NotFoundError& e) {
        EXPECT_EQ(e.code(), ErrorCode::UnknownSupplier);
    }
}

TEST(PurchaseOrderService, DeliveryBeforeCreationRejected) {
    Fixture f;
    // createdAt = 2026-11-02 (reloj fijo), entrega 2026-11-01 es anterior.
    try {
        f.orderService.create(Cuit("20123456789"), Date(2026, 11, 1),
                              {{"CAU-001", 5}});
        FAIL() << "debería haber lanzado ValidationError";
    } catch (const ValidationError& e) {
        EXPECT_EQ(e.code(), ErrorCode::DeliveryBeforeCreation);
    }
}

TEST(PurchaseOrderService, EmptyOrderRejected) {
    Fixture f;
    try {
        f.orderService.create(Cuit("20123456789"), Date(2026, 11, 10), {});
        FAIL() << "debería haber lanzado ValidationError";
    } catch (const ValidationError& e) {
        EXPECT_EQ(e.code(), ErrorCode::EmptyOrder);
    }
}

TEST(PurchaseOrderService, NonPositiveQuantityRejected) {
    Fixture f;
    try {
        f.orderService.create(Cuit("20123456789"), Date(2026, 11, 10),
                              {{"CAU-001", 0}});
        FAIL() << "debería haber lanzado ValidationError";
    } catch (const ValidationError& e) {
        EXPECT_EQ(e.code(), ErrorCode::NonPositiveQuantity);
    }
}

TEST(PurchaseOrderService, UnknownArticleRejected) {
    Fixture f;
    try {
        f.orderService.create(Cuit("20123456789"), Date(2026, 11, 10),
                              {{"NO-EXISTE", 5}});
        FAIL() << "debería haber lanzado NotFoundError";
    } catch (const NotFoundError& e) {
        EXPECT_EQ(e.code(), ErrorCode::UnknownArticle);
    }
}

TEST(PurchaseOrderService, DuplicateArticleInOrderRejected) {
    Fixture f;
    try {
        f.orderService.create(Cuit("20123456789"), Date(2026, 11, 10),
                              {{"CAU-001", 5}, {"CAU-001", 3}});
        FAIL() << "debería haber lanzado ConflictError";
    } catch (const ConflictError& e) {
        EXPECT_EQ(e.code(), ErrorCode::DuplicateArticleInOrder);
    }
}

TEST(PurchaseOrderService, CreateHappyPath) {
    Fixture f;
    PurchaseOrder order = f.orderService.create(
        Cuit("20123456789"), Date(2026, 11, 10), {{"CAU-001", 500}});
    EXPECT_EQ(order.number().value(), 1u);
    EXPECT_NE(order.supplier(), nullptr);
    EXPECT_EQ(order.supplier()->cuit().value(), "20123456789");
    EXPECT_EQ(order.createdAt(), Date(2026, 11, 2));
    EXPECT_EQ(order.expectedDelivery(), Date(2026, 11, 10));
    ASSERT_EQ(order.items().size(), 1u);
    EXPECT_EQ(order.items()[0].first->code(), "CAU-001");
    EXPECT_EQ(order.items()[0].second.value(), 500u);
}

TEST(PurchaseOrderService, OrdersBySupplier) {
    Fixture f;
    f.orderService.create(Cuit("20123456789"), Date(2026, 11, 10),
                          {{"CAU-001", 1}});
    auto groups = f.orderService.ordersBySupplier();
    ASSERT_EQ(groups.size(), 1u);
    EXPECT_EQ(groups[0].supplier->cuit().value(), "20123456789");
    ASSERT_EQ(groups[0].orders.size(), 1u);
}

TEST(PurchaseOrderService, HasOrdersFor) {
    Fixture f;
    EXPECT_FALSE(f.orderService.hasOrdersFor(Cuit("20123456789")));
    f.orderService.create(Cuit("20123456789"), Date(2026, 11, 10),
                          {{"CAU-001", 1}});
    EXPECT_TRUE(f.orderService.hasOrdersFor(Cuit("20123456789")));
    EXPECT_FALSE(f.orderService.hasOrdersFor(Cuit("20234567891")));
}
