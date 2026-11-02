#ifndef PARTIAL02_MARIA_DB_PURCHASE_ORDER_REPOSITORY_HPP
#define PARTIAL02_MARIA_DB_PURCHASE_ORDER_REPOSITORY_HPP

#include <mysql.h>

#include "maria_db_connection.hpp"
#include "ordernumber.hpp"
#include "purchaseorder.hpp"
#include "repository.hpp"

#include <memory>
#include <vector>

namespace partial02 {

class MariaDbArticleRepository;
class MariaDbSupplierRepository;

/// Adaptador MariaDB para PurchaseOrder. Implementa Repository<PurchaseOrder,
/// OrderNumber> (alta y lectura, append-only) y OrderNumberSequence
/// (número = MAX(number)+1 dentro de la transacción).
class MariaDbPurchaseOrderRepository : public Repository<PurchaseOrder, OrderNumber>,
                                       public OrderNumberSequence {
public:
    MariaDbPurchaseOrderRepository(MariaDbConnection& conn,
                                   MariaDbArticleRepository& articleRepo,
                                   MariaDbSupplierRepository& supplierRepo);

    const PurchaseOrder* find(const OrderNumber& key) const override;
    std::vector<const PurchaseOrder*> all() const override;
    void add(const PurchaseOrder& entity) override;

    OrderNumber nextNumber() override;

private:
    MariaDbConnection& conn_;
    MariaDbArticleRepository& articleRepo_;
    MariaDbSupplierRepository& supplierRepo_;
    mutable std::vector<std::unique_ptr<PurchaseOrder>> cache_;

    void loadAll() const;
};

}  // namespace partial02

#endif  // PARTIAL02_MARIA_DB_PURCHASE_ORDER_REPOSITORY_HPP
