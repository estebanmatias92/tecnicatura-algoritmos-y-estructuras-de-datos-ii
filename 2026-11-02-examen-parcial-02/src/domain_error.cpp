#include "domain_error.hpp"

namespace partial02 {

DomainError::DomainError(ErrorCode code, Fields fields)
    : std::runtime_error("domain error"), code_(code), fields_(std::move(fields)) {}

ErrorCode DomainError::code() const noexcept {
    return code_;
}

const Fields& DomainError::fields() const noexcept {
    return fields_;
}

}  // namespace partial02
