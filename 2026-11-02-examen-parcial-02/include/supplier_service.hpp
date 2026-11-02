#ifndef PARTIAL02_SUPPLIER_SERVICE_HPP
#define PARTIAL02_SUPPLIER_SERVICE_HPP

#include "cuit.hpp"
#include "domain_error.hpp"
#include "repository.hpp"
#include "supplier.hpp"

#include <vector>

namespace partial02 {

/// Servicio de proveedores: aplica BR-004, BR-005, BR-009.
/// Recibe el repositorio mutable por constructor (DIP/IoC).
class SupplierService {
public:
    SupplierService(MutableRepository<Supplier, Cuit>& repo);

    void add(const Cuit& cuit, const std::string& businessName);
    void update(const Cuit& cuit, const std::string& businessName);
    void remove(const Cuit& cuit);
    std::vector<const Supplier*> list() const;

private:
    MutableRepository<Supplier, Cuit>& repo_;
};

}  // namespace partial02

#endif  // PARTIAL02_SUPPLIER_SERVICE_HPP
