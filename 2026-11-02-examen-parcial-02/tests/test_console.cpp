#include "article_catalog.hpp"
#include "clock.hpp"
#include "console.hpp"
#include "in_memory_order_number_sequence.hpp"
#include "inmemory_repository.hpp"
#include "message_catalog.hpp"
#include "purchase_order_service.hpp"
#include "supplier_service.hpp"

#include <gtest/gtest.h>

#include <istream>
#include <ostream>
#include <sstream>
#include <string>

using partial02::ArticleCatalog;
using partial02::Console;
using partial02::Cuit;
using partial02::Date;
using partial02::InMemoryOrderNumberSequence;
using partial02::InMemoryRepository;
using partial02::MessageCatalog;
using partial02::PurchaseOrderService;
using partial02::SupplierService;
using partial02::SystemClock;

namespace {

// Harness: construye el cableado completo y ejecuta una operación directa,
// devolviendo la salida capturada.
std::string opWithInput(const std::string& input,
                        void (Console::*op)()) {
    std::istringstream in(input);
    std::ostringstream out;

    ArticleCatalog catalog;
    InMemoryRepository<partial02::Supplier, Cuit> supplierRepo(
        [](const partial02::Supplier& s) { return s.cuit(); });
    InMemoryRepository<partial02::PurchaseOrder, partial02::OrderNumber>
        orderRepo([](const partial02::PurchaseOrder& o) {
            return o.number();
        });
    InMemoryOrderNumberSequence sequence;
    SystemClock clock;

    SupplierService supplierService(supplierRepo);
    PurchaseOrderService orderService(supplierRepo, catalog, orderRepo,
                                      sequence, clock);
    MessageCatalog messages;
    Console console(in, out, catalog, supplierService, orderService, messages);

    (console.*op)();
    return out.str();
}

// Ejecuta el bucle completo del menú con una secuencia de teclas.
std::string runWithInput(const std::string& input) {
    std::istringstream in(input);
    std::ostringstream out;

    ArticleCatalog catalog;
    InMemoryRepository<partial02::Supplier, Cuit> supplierRepo(
        [](const partial02::Supplier& s) { return s.cuit(); });
    InMemoryRepository<partial02::PurchaseOrder, partial02::OrderNumber>
        orderRepo([](const partial02::PurchaseOrder& o) {
            return o.number();
        });
    InMemoryOrderNumberSequence sequence;
    SystemClock clock;

    SupplierService supplierService(supplierRepo);
    PurchaseOrderService orderService(supplierRepo, catalog, orderRepo,
                                      sequence, clock);
    MessageCatalog messages;
    Console console(in, out, catalog, supplierService, orderService, messages);

    console.run();
    return out.str();
}

}  // namespace

// ---------- Menú y salida ----------

TEST(Console, ExitOption0) {
    std::string out = runWithInput("0\n");
    EXPECT_TRUE(out.find("Hasta luego.") != std::string::npos);
}

TEST(Console, ExitViaEOF) {
    std::istringstream in("");
    std::ostringstream out;
    ArticleCatalog catalog;
    InMemoryRepository<partial02::Supplier, Cuit> supplierRepo(
        [](const partial02::Supplier& s) { return s.cuit(); });
    InMemoryRepository<partial02::PurchaseOrder, partial02::OrderNumber>
        orderRepo([](const partial02::PurchaseOrder& o) {
            return o.number();
        });
    InMemoryOrderNumberSequence sequence;
    SystemClock clock;
    SupplierService supplierService(supplierRepo);
    PurchaseOrderService orderService(supplierRepo, catalog, orderRepo,
                                      sequence, clock);
    MessageCatalog messages;
    Console console(in, out, catalog, supplierService, orderService, messages);
    EXPECT_EQ(console.run(), 0);
    EXPECT_TRUE(out.str().find("Hasta luego.") != std::string::npos);
}

TEST(Console, InvalidOption) {
    std::string out = runWithInput("9\n0\n");
    EXPECT_TRUE(out.find("Opción inválida") != std::string::npos);
    EXPECT_TRUE(out.find("Hasta luego.") != std::string::npos);
}

// ---------- OP-01 Cargar artículo ----------

TEST(Console, CreateArticleValid) {
    std::string out = opWithInput("CAU-001\nCaucho natural\n1500,00\n",
                                  &Console::createArticle);
    EXPECT_TRUE(out.find("Artículo CAU-001 cargado.") != std::string::npos);
}

TEST(Console, CreateArticleEmptyCode) {
    std::string out = opWithInput("\n", &Console::createArticle);
    EXPECT_TRUE(out.find("El código de artículo no puede estar vacío.")
                    != std::string::npos);
}

TEST(Console, CreateArticleDuplicateCode) {
    std::istringstream in("CAU-001\nDesc\n1500,00\nCAU-001\nDesc2\n2000,00\n");
    std::ostringstream out;
    ArticleCatalog catalog;
    InMemoryRepository<partial02::Supplier, Cuit> supplierRepo(
        [](const partial02::Supplier& s) { return s.cuit(); });
    InMemoryRepository<partial02::PurchaseOrder, partial02::OrderNumber>
        orderRepo([](const partial02::PurchaseOrder& o) {
            return o.number();
        });
    InMemoryOrderNumberSequence sequence;
    SystemClock clock;
    SupplierService supplierService(supplierRepo);
    PurchaseOrderService orderService(supplierRepo, catalog, orderRepo,
                                      sequence, clock);
    MessageCatalog messages;
    Console console(in, out, catalog, supplierService, orderService, messages);
    console.createArticle();
    console.createArticle();
    EXPECT_TRUE(out.str().find("Ya existe un artículo con el código CAU-001") !=
                std::string::npos);
}

TEST(Console, CreateArticleZeroPrice) {
    std::string out = opWithInput("CAU-001\nDesc\n0\n", &Console::createArticle);
    EXPECT_TRUE(out.find("El precio unitario debe ser mayor que cero.")
                    != std::string::npos);
}

// ---------- OP-02 Cargar proveedor ----------

TEST(Console, CreateSupplierValid) {
    std::string out =
        opWithInput("20123456789\nCauchos del Sur S.A.\n", &Console::createSupplier);
    EXPECT_TRUE(out.find("Proveedor 20123456789 - Cauchos del Sur S.A. cargado.")
                    != std::string::npos);
}

TEST(Console, CreateSupplierInvalidCuit) {
    std::string out = opWithInput("2012345678\nX\n", &Console::createSupplier);
    EXPECT_TRUE(out.find("El CUIT debe tener exactamente 11 dígitos")
                    != std::string::npos);
}

TEST(Console, CreateSupplierEmptyBusinessName) {
    std::string out = opWithInput("20123456789\n\n", &Console::createSupplier);
    EXPECT_TRUE(out.find("La razón social no puede estar vacía.")
                    != std::string::npos);
}

// ---------- OP-03 Listar proveedores ----------

TEST(Console, ListSuppliersEmpty) {
    std::string out = opWithInput("", &Console::listSuppliers);
    EXPECT_TRUE(out.find("Proveedores registrados:") != std::string::npos);
    EXPECT_TRUE(out.find("No hay proveedores registrados.") != std::string::npos);
}

// ---------- OP-06 Cargar pedido ----------

TEST(Console, CreateOrderNonexistentSupplier) {
    std::string out = opWithInput("99999999999\n", &Console::createOrder);
    EXPECT_TRUE(out.find("No existe un proveedor con el CUIT 99999999999.")
                    != std::string::npos);
}

TEST(Console, CreateOrderInvalidDate) {
    std::istringstream in("20123456789\nProv\n20123456789\n2026-02-30\n");
    std::ostringstream out;
    ArticleCatalog catalog;
    InMemoryRepository<partial02::Supplier, Cuit> supplierRepo(
        [](const partial02::Supplier& s) { return s.cuit(); });
    InMemoryRepository<partial02::PurchaseOrder, partial02::OrderNumber>
        orderRepo([](const partial02::PurchaseOrder& o) {
            return o.number();
        });
    InMemoryOrderNumberSequence sequence;
    SystemClock clock;
    SupplierService supplierService(supplierRepo);
    PurchaseOrderService orderService(supplierRepo, catalog, orderRepo,
                                      sequence, clock);
    MessageCatalog messages;
    Console console(in, out, catalog, supplierService, orderService, messages);
    console.createSupplier();
    console.createOrder();
    EXPECT_TRUE(out.str().find("Fecha inválida") != std::string::npos);
}

// ---------- OP-07 Mostrar pedidos ----------

TEST(Console, ShowOrdersEmpty) {
    std::string out = opWithInput("", &Console::showOrders);
    EXPECT_TRUE(out.find("No hay pedidos registrados.") != std::string::npos);
}

// Muestra pedidos con ítems: ejercita PurchaseOrder::operator<< y formatMoney.
TEST(Console, ShowOrdersConPedidos) {
    std::istringstream in("CAU-001\nCaucho natural\n1500,00\n"
                          "20123456789\nCauchos del Sur S.A.\n"
                          "20123456789\n2026-12-01\nCAU-001\n5\n\n");
    std::ostringstream out;
    ArticleCatalog catalog;
    InMemoryRepository<partial02::Supplier, Cuit> supplierRepo(
        [](const partial02::Supplier& s) { return s.cuit(); });
    InMemoryRepository<partial02::PurchaseOrder, partial02::OrderNumber>
        orderRepo([](const partial02::PurchaseOrder& o) {
            return o.number();
        });
    InMemoryOrderNumberSequence sequence;
    SystemClock clock;
    SupplierService supplierService(supplierRepo);
    PurchaseOrderService orderService(supplierRepo, catalog, orderRepo,
                                      sequence, clock);
    MessageCatalog messages;
    Console console(in, out, catalog, supplierService, orderService, messages);
    console.createArticle();
    console.createSupplier();
    console.createOrder();
    console.showOrders();
    EXPECT_TRUE(out.str().find("Pedido 1 - creado") != std::string::npos);
    EXPECT_TRUE(out.str().find("1500,00") != std::string::npos);
    EXPECT_TRUE(out.str().find("7500,00") != std::string::npos);
}
