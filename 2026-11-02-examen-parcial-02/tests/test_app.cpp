#include "app.hpp"

#include <gtest/gtest.h>

#include <istream>
#include <ostream>
#include <sstream>
#include <string>

using partial02::App;

namespace {

// Ejecuta una secuencia de teclas y devuelve la salida capturada.
std::string runWithInput(const std::string& input) {
    std::istringstream in(input);
    std::ostringstream out;
    App app(in, out);
    app.run();
    return out.str();
}

// Llama a una operación directa y devuelve la salida capturada.
std::string opWithInput(const std::string& input, void (App::*op)()) {
    std::istringstream in(input);
    std::ostringstream out;
    App app(in, out);
    (app.*op)();
    return out.str();
}

}  // namespace

// ---------- Menú y salida ----------

TEST(App, ExitOption0) {
    std::string out = runWithInput("0\n");
    EXPECT_TRUE(out.find("Hasta luego") != std::string::npos);
}

TEST(App, ExitViaEOF) {
    std::istringstream in("");
    std::ostringstream out;
    App app(in, out);
    EXPECT_EQ(app.run(), 0);
    EXPECT_TRUE(out.str().find("Hasta luego") != std::string::npos);
}

TEST(App, InvalidOption) {
    std::string out = runWithInput("9\n0\n");
    EXPECT_TRUE(out.find("Opción inválida") != std::string::npos);
    EXPECT_TRUE(out.find("Hasta luego") != std::string::npos);
}

// ---------- OP-01 Cargar artículo ----------

TEST(App, CreateArticleValid) {
    std::string out = opWithInput("CAU-001\nCaucho natural\n1500,00\n", &App::createArticle);
    EXPECT_TRUE(out.find("Artículo CAU-001 cargado") != std::string::npos);
}

TEST(App, CreateArticleEmptyCode) {
    std::string out = opWithInput("\n", &App::createArticle);
    EXPECT_TRUE(out.find("El código de artículo no puede estar vacío") != std::string::npos);
}

TEST(App, CreateArticleDuplicateCode) {
    std::istringstream in("CAU-001\nDesc\n1500,00\nCAU-001\nDesc2\n2000,00\n");
    std::ostringstream out;
    App app(in, out);
    app.createArticle();
    app.createArticle();
    EXPECT_TRUE(out.str().find("Ya existe un artículo con el código CAU-001") != std::string::npos);
}

TEST(App, CreateArticleZeroPrice) {
    std::string out = opWithInput("CAU-001\nDesc\n0\n", &App::createArticle);
    EXPECT_TRUE(out.find("El precio unitario debe ser mayor que cero") != std::string::npos);
}

TEST(App, CreateArticleNegativePrice) {
    std::string out = opWithInput("CAU-001\nDesc\n-100\n", &App::createArticle);
    EXPECT_TRUE(out.find("El importe no puede ser negativo") != std::string::npos);
}

TEST(App, CreateArticleInvalidFormat) {
    std::string out = opWithInput("CAU-001\nDesc\nabc\n", &App::createArticle);
    EXPECT_TRUE(out.find("Importe inválido") != std::string::npos);
}

TEST(App, CreateArticleDescriptionCanBeEmpty) {
    std::string out = opWithInput("CAU-001\n\n1500,00\n", &App::createArticle);
    EXPECT_TRUE(out.find("Artículo CAU-001 cargado") != std::string::npos);
}

// ---------- OP-02 Cargar proveedor ----------

TEST(App, CreateSupplierValid) {
    std::string out = opWithInput("20123456789\nCauchos del Sur S.A.\n", &App::createSupplier);
    EXPECT_TRUE(out.find("Proveedor 20123456789 - Cauchos del Sur S.A. cargado") != std::string::npos);
}

TEST(App, CreateSupplierInvalidCuit) {
    std::string out = opWithInput("2012345678\nX\n", &App::createSupplier);
    EXPECT_TRUE(out.find("El CUIT debe tener exactamente 11 dígitos") != std::string::npos);
}

TEST(App, CreateSupplierDuplicateCuit) {
    std::istringstream in("20123456789\nProveedor A\n20123456789\nProveedor B\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.createSupplier();
    EXPECT_TRUE(out.str().find("Ya existe un proveedor con el CUIT 20123456789") != std::string::npos);
}

TEST(App, CreateSupplierEmptyBusinessName) {
    std::string out = opWithInput("20123456789\n\n", &App::createSupplier);
    EXPECT_TRUE(out.find("La razón social no puede estar vacía") != std::string::npos);
}

// ---------- OP-03 Listar proveedores ----------

TEST(App, ListSuppliersEmpty) {
    std::string out = opWithInput("", &App::listSuppliers);
    EXPECT_TRUE(out.find("Proveedores registrados:") != std::string::npos);
    EXPECT_TRUE(out.find("No hay proveedores registrados") != std::string::npos);
}

TEST(App, ListSuppliersOrderedByCuit) {
    std::istringstream in("27334455669\nQuímica\n20123456789\nCauchos\n30712345678\nAceite\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.createSupplier();
    app.createSupplier();
    app.listSuppliers();
    std::string s = out.str();
    EXPECT_TRUE(s.find("Proveedores registrados:") != std::string::npos);
    EXPECT_TRUE(s.find("20123456789") != std::string::npos);
    EXPECT_TRUE(s.find("27334455669") != std::string::npos);
    EXPECT_TRUE(s.find("30712345678") != std::string::npos);
}

// ---------- OP-04 Modificar proveedor ----------

TEST(App, UpdateSupplierNonexistent) {
    std::string out = opWithInput("99999999999\n", &App::updateSupplier);
    EXPECT_TRUE(out.find("No existe un proveedor con el CUIT 99999999999") != std::string::npos);
}

TEST(App, UpdateSupplierValid) {
    std::istringstream in("20123456789\nNombre viejo\n20123456789\nNombre nuevo\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.updateSupplier();
    EXPECT_TRUE(out.str().find("Nombre nuevo") != std::string::npos);
    EXPECT_TRUE(out.str().find("modificado") != std::string::npos);
}

TEST(App, UpdateSupplierKeepNameWithEnter) {
    std::istringstream in("20123456789\nNombre viejo\n20123456789\n\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.updateSupplier();
    EXPECT_TRUE(out.str().find("Nombre viejo") != std::string::npos);
}

// ---------- OP-05 Eliminar proveedor ----------

TEST(App, RemoveSupplierNonexistent) {
    std::string out = opWithInput("99999999999\n", &App::removeSupplier);
    EXPECT_TRUE(out.find("No existe un proveedor con el CUIT 99999999999") != std::string::npos);
}

TEST(App, RemoveSupplierWithoutOrders) {
    std::istringstream in("20123456789\nProveedor\n20123456789\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.removeSupplier();
    EXPECT_TRUE(out.str().find("eliminado") != std::string::npos);
}

// ---------- OP-06 Cargar pedido ----------

TEST(App, CreateOrderNonexistentSupplier) {
    std::string out = opWithInput("99999999999\n", &App::createOrder);
    EXPECT_TRUE(out.find("No existe un proveedor con el CUIT 99999999999") != std::string::npos);
}

TEST(App, CreateOrderInvalidDate) {
    // Primero crear proveedor válido, luego orden con fecha inválida
    std::istringstream in("20123456789\nProv\n20123456789\n2026-02-30\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("Fecha inválida") != std::string::npos);
}

TEST(App, CreateOrderDeliveryBeforeCreation) {
    std::istringstream in("20123456789\nProv\n20123456789\n2020-01-01\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("no puede ser anterior a la fecha de creación") != std::string::npos);
}

TEST(App, CreateOrderNoItems) {
    std::istringstream in("20123456789\nProv\n20123456789\n2026-11-10\n\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("El pedido debe tener al menos un artículo") != std::string::npos);
}

TEST(App, CreateOrderUnknownArticle) {
    std::istringstream in("20123456789\nProv\n20123456789\n2026-11-10\nINEXISTENTE\n1\n\n");
    std::ostringstream out;
    App app(in, out);
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("No existe un artículo con el código INEXISTENTE") != std::string::npos);
}

TEST(App, CreateOrderDuplicateArticle) {
    // Necesita artículo CAU-001 ya cargado
    std::istringstream in(
        "CAU-001\nCaucho\n1500,00\n"
        "20123456789\nProv\n"
        "20123456789\n2026-11-10\nCAU-001\n1\nCAU-001\n1\n\n"
    );
    std::ostringstream out;
    App app(in, out);
    app.createArticle();
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("ya está en el pedido") != std::string::npos);
}

TEST(App, CreateOrderInvalidQuantity) {
    std::istringstream in(
        "CAU-001\nCaucho\n1500,00\n"
        "20123456789\nProv\n"
        "20123456789\n2026-11-10\nCAU-001\n0\n\n"
    );
    std::ostringstream out;
    App app(in, out);
    app.createArticle();
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("mayor que cero") != std::string::npos);
}

TEST(App, CreateOrderValid) {
    std::istringstream in(
        "CAU-001\nCaucho natural\n1500,00\n"
        "20123456789\nProv Test\n"
        "20123456789\n2026-11-10\nCAU-001\n500\n\n"
    );
    std::ostringstream out;
    App app(in, out);
    app.createArticle();
    app.createSupplier();
    app.createOrder();
    EXPECT_TRUE(out.str().find("Pedido 1 creado") != std::string::npos);
    EXPECT_TRUE(out.str().find("Ítem agregado: CAU-001 - 500") != std::string::npos);
}

// ---------- OP-07 Mostrar pedidos ----------

TEST(App, ShowOrdersEmpty) {
    std::string out = opWithInput("", &App::showOrders);
    EXPECT_TRUE(out.find("No hay pedidos registrados") != std::string::npos);
}

TEST(App, ShowOrdersGroupsBySupplier) {
    std::istringstream in(
        "CAU-001\nCaucho natural\n1500,00\n"
        "20123456789\nCauchos del Sur\n"
        "27334455669\nQuímica del Plata\n"
        "20123456789\n2026-11-05\nCAU-001\n100\n\n"
        "27334455669\n2026-11-10\nCAU-001\n50\n\n"
    );
    std::ostringstream out;
    App app(in, out);
    app.createArticle();
    app.createSupplier();
    app.createSupplier();
    app.createOrder();
    app.createOrder();
    app.showOrders();
    std::string s = out.str();
    EXPECT_TRUE(s.find("Proveedor: 20123456789 - Cauchos del Sur") != std::string::npos);
    EXPECT_TRUE(s.find("Proveedor: 27334455669 - Química del Plata") != std::string::npos);
    EXPECT_TRUE(s.find("Cauchos del Sur") < s.find("Química del Plata"));
}

TEST(App, ShowOrdersShowsTotal) {
    std::istringstream in(
        "CAU-001\nCaucho natural\n1500,00\n"
        "20123456789\nProv\n"
        "20123456789\n2026-11-05\nCAU-001\n2\n\n"
    );
    std::ostringstream out;
    App app(in, out);
    app.createArticle();
    app.createSupplier();
    app.createOrder();
    app.showOrders();
    EXPECT_TRUE(out.str().find("Total del pedido: 3000,00") != std::string::npos);
}
