#ifndef PARTIAL02_DOMAIN_ERROR_HPP
#define PARTIAL02_DOMAIN_ERROR_HPP

#include <map>
#include <stdexcept>
#include <string>

namespace partial02 {

/// Código de error estable en inglés. El texto en español vive solo en
/// MessageCatalog (la consola); el dominio nunca arma oraciones.
enum class ErrorCode {
    // Invariante del valor o de la operación
    EmptyArticleCode,
    NonPositiveUnitPrice,
    NegativeMoney,
    EmptyBusinessName,
    CuitFormat,
    NonPositiveQuantity,
    DateFormat,
    InvalidCalendarDate,
    DeliveryBeforeCreation,
    EmptyOrder,
    // Clave inexistente
    UnknownArticle,
    UnknownSupplier,
    // Depende del conjunto, no del valor solo
    DuplicateArticleCode,
    DuplicateCuit,
    DuplicateArticleInOrder,
    SupplierHasOrders,
};

using Fields = std::map<std::string, std::string>;

class DomainError : public std::runtime_error {
public:
    DomainError(ErrorCode code, Fields fields = {});

    ErrorCode code() const noexcept;
    const Fields& fields() const noexcept;

private:
    ErrorCode code_;
    Fields fields_;
};

class ValidationError : public DomainError {
public:
    using DomainError::DomainError;
};

class NotFoundError : public DomainError {
public:
    using DomainError::DomainError;
};

class ConflictError : public DomainError {
public:
    using DomainError::DomainError;
};

}  // namespace partial02

#endif  // PARTIAL02_DOMAIN_ERROR_HPP
