#ifndef PARTIAL02_MARIA_DB_SUPPLIER_REPOSITORY_HPP
#define PARTIAL02_MARIA_DB_SUPPLIER_REPOSITORY_HPP

#include "maria_db_connection.hpp"
#include "repository.hpp"
#include "supplier.hpp"

#include <memory>
#include <vector>

namespace partial02 {

/// Adaptador MariaDB para Supplier. Implementa MutableRepository<Supplier, Cuit>.
/// Los objetos Supplier se almacenan en un caché interno con unique_ptr para
/// que los punteros devueltos por find()/all() sean estables.
class MariaDbSupplierRepository : public MutableRepository<Supplier, Cuit> {
public:
    explicit MariaDbSupplierRepository(MariaDbConnection& conn);

    const Supplier* find(const Cuit& key) const override;
    std::vector<const Supplier*> all() const override;
    void add(const Supplier& entity) override;
    void update(const Supplier& entity) override;
    void remove(const Cuit& key) override;

private:
    MariaDbConnection& conn_;
    mutable std::vector<std::unique_ptr<Supplier>> cache_;

    void loadAll() const;
    const Supplier* findInCache(const Cuit& key) const;
};

}  // namespace partial02

#endif  // PARTIAL02_MARIA_DB_SUPPLIER_REPOSITORY_HPP
