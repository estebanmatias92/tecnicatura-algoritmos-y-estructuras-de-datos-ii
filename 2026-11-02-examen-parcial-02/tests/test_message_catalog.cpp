#include "domain_error.hpp"
#include "message_catalog.hpp"

#include <gtest/gtest.h>

#include <map>
#include <string>

using partial02::DomainError;
using partial02::ErrorCode;
using partial02::Fields;
using partial02::MessageCatalog;

namespace {

std::string translate(MessageCatalog& cat, ErrorCode code, Fields fields = {}) {
    return cat.translate(DomainError(code, std::move(fields)));
}

}  // namespace

TEST(MessageCatalog, EmptyArticleCode) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::EmptyArticleCode),
              "El código de artículo no puede estar vacío.");
}

TEST(MessageCatalog, NonPositiveUnitPrice) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::NonPositiveUnitPrice),
              "El precio unitario debe ser mayor que cero.");
}

TEST(MessageCatalog, NegativeMoney) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::NegativeMoney),
              "El importe no puede ser negativo.");
}

TEST(MessageCatalog, EmptyBusinessName) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::EmptyBusinessName),
              "La razón social no puede estar vacía.");
}

TEST(MessageCatalog, CuitFormat) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::CuitFormat),
              "El CUIT debe tener exactamente 11 dígitos numéricos.");
}

TEST(MessageCatalog, NonPositiveQuantity) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::NonPositiveQuantity),
              "La cantidad debe ser mayor que cero.");
}

TEST(MessageCatalog, DateFormat) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::DateFormat),
              "Fecha inválida. Usá el formato AAAA-MM-DD.");
}

TEST(MessageCatalog, InvalidCalendarDate) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::InvalidCalendarDate,
                        {{"date", "2026-02-30"}}),
              "La fecha 2026-02-30 no existe en el calendario.");
}

TEST(MessageCatalog, DeliveryBeforeCreation) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::DeliveryBeforeCreation,
                        {{"createdAt", "2026-11-02"}}),
              "La fecha de entrega no puede ser anterior a la fecha de creación (2026-11-02).");
}

TEST(MessageCatalog, EmptyOrder) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::EmptyOrder),
              "El pedido debe tener al menos un artículo.");
}

TEST(MessageCatalog, UnknownArticle) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::UnknownArticle, {{"code", "NO-EXISTE"}}),
              "No existe un artículo con el código NO-EXISTE.");
}

TEST(MessageCatalog, UnknownSupplier) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::UnknownSupplier, {{"cuit", "99999999999"}}),
              "No existe un proveedor con el CUIT 99999999999.");
}

TEST(MessageCatalog, DuplicateArticleCode) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::DuplicateArticleCode, {{"code", "CAU-001"}}),
              "Ya existe un artículo con el código CAU-001.");
}

TEST(MessageCatalog, DuplicateCuit) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::DuplicateCuit, {{"cuit", "20123456789"}}),
              "Ya existe un proveedor con el CUIT 20123456789.");
}

TEST(MessageCatalog, DuplicateArticleInOrder) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::DuplicateArticleInOrder, {{"code", "CAU-001"}}),
              "El artículo CAU-001 ya está en el pedido. Modificá la cantidad del ítem existente.");
}

TEST(MessageCatalog, SupplierHasOrders) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, ErrorCode::SupplierHasOrders,
                        {{"cuit", "20123456789"}, {"count", "2"}}),
              "No se puede eliminar el proveedor 20123456789: tiene 2 pedido(s) asociado(s).");
}

TEST(MessageCatalog, UnknownCodeDevuelveMensajeGenerico) {
    MessageCatalog cat;
    EXPECT_EQ(translate(cat, static_cast<ErrorCode>(99)), "Error desconocido.");
}
