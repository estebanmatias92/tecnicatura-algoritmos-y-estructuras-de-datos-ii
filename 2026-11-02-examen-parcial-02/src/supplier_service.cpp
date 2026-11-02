#include "supplier_service.hpp"

namespace partial02 {

SupplierService::SupplierService(MutableRepository<Supplier, Cuit>& repo)
    : repo_(repo) {}

void SupplierService::add(const Cuit& cuit, const std::string& businessName) {
    if (repo_.find(cuit) != nullptr) {
        throw ConflictError(ErrorCode::DuplicateCuit, {{"cuit", cuit.value()}});
    }
    try {
        repo_.add(Supplier(cuit, businessName));  // valida BR-005 en el constructor
    } catch (const std::invalid_argument& e) {
        throw ValidationError(ErrorCode::EmptyBusinessName);
    }
}

void SupplierService::update(const Cuit& cuit, const std::string& businessName) {
    const Supplier* existing = repo_.find(cuit);
    if (existing == nullptr) {
        throw NotFoundError(ErrorCode::UnknownSupplier,
                            {{"cuit", cuit.value()}});
    }
    Supplier updated(cuit, businessName);  // valida BR-005
    repo_.update(updated);
}

void SupplierService::remove(const Cuit& cuit) {
    if (repo_.find(cuit) == nullptr) {
        throw NotFoundError(ErrorCode::UnknownSupplier,
                            {{"cuit", cuit.value()}});
    }
    repo_.remove(cuit);
}

std::vector<const Supplier*> SupplierService::list() const {
    return repo_.all();
}

}  // namespace partial02
