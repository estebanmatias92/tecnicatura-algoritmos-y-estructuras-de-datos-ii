#include "message_catalog.hpp"

#include <sstream>

namespace partial02 {

std::string MessageCatalog::translate(const DomainError& err) {
    using partial02::ErrorCode;
    std::ostringstream os;

    switch (err.code()) {
    case ErrorCode::EmptyArticleCode:
        return "El código de artículo no puede estar vacío.";
    case ErrorCode::NonPositiveUnitPrice:
        return "El precio unitario debe ser mayor que cero.";
    case ErrorCode::NegativeMoney:
        return "El importe no puede ser negativo.";
    case ErrorCode::EmptyBusinessName:
        return "La razón social no puede estar vacía.";
    case ErrorCode::CuitFormat:
        return "El CUIT debe tener exactamente 11 dígitos numéricos.";
    case ErrorCode::NonPositiveQuantity:
        return "La cantidad debe ser mayor que cero.";
    case ErrorCode::DateFormat:
        return "Fecha inválida. Usá el formato AAAA-MM-DD.";
    case ErrorCode::InvalidCalendarDate:
        return "La fecha " + err.fields().at("date") +
               " no existe en el calendario.";
    case ErrorCode::DeliveryBeforeCreation:
        return "La fecha de entrega no puede ser anterior a la fecha de creación (" +
               err.fields().at("createdAt") + ").";
    case ErrorCode::EmptyOrder:
        return "El pedido debe tener al menos un artículo.";
    case ErrorCode::UnknownArticle:
        return "No existe un artículo con el código " +
               err.fields().at("code") + ".";
    case ErrorCode::UnknownSupplier:
        return "No existe un proveedor con el CUIT " +
               err.fields().at("cuit") + ".";
    case ErrorCode::DuplicateArticleCode:
        return "Ya existe un artículo con el código " +
               err.fields().at("code") + ".";
    case ErrorCode::DuplicateCuit:
        return "Ya existe un proveedor con el CUIT " +
               err.fields().at("cuit") + ".";
    case ErrorCode::DuplicateArticleInOrder:
        return "El artículo " + err.fields().at("code") +
               " ya está en el pedido. Modificá la cantidad del ítem existente.";
    case ErrorCode::SupplierHasOrders:
        return "No se puede eliminar el proveedor " +
               err.fields().at("cuit") + ": tiene " +
               err.fields().at("count") + " pedido(s) asociado(s).";
    }
    return "Error desconocido.";
}

}  // namespace partial02
