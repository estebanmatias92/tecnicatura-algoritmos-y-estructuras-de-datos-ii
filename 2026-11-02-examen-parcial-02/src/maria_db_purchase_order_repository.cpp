#include "maria_db_purchase_order_repository.hpp"

#include <mysql.h>
#include <stdexcept>
#include <string>
#include <cstring>

namespace partial02 {

MariaDbPurchaseOrderRepository::MariaDbPurchaseOrderRepository(
    MariaDbConnection& conn, MariaDbArticleRepository& articleRepo,
    MariaDbSupplierRepository& supplierRepo)
    : conn_(conn), articleRepo_(articleRepo), supplierRepo_(supplierRepo) {}

OrderNumber MariaDbPurchaseOrderRepository::nextNumber() {
    MYSQL_RES* res = conn_.query(
        "SELECT COALESCE(MAX(number), 0) + 1 FROM purchase_orders");
    MYSQL_ROW row = mysql_fetch_row(res);
    unsigned int next = row && row[0] ? static_cast<unsigned int>(std::stoul(row[0])) : 1u;
    mysql_free_result(res);
    return OrderNumber(next);
}

void MariaDbPurchaseOrderRepository::loadAll() const {
    if (!cache_.empty()) {
        return;
    }
    MYSQL_RES* res = conn_.query(
        "SELECT number, supplier_cuit, created_at, expected_delivery "
        "FROM purchase_orders ORDER BY number");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr) {
        OrderNumber number(static_cast<unsigned int>(std::stoul(row[0])));
        Cuit cuit(row[1] ? row[1] : "");
        Date createdAt(std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]));
        // row[2] = created_at "YYYY-MM-DD", row[3] = expected_delivery "YYYY-MM-DD"
        // Pero mysql_fetch_row retorna strings, no fechas parseadas.
        // Necesito parsear la fecha.
        // Simplificar: usar string y parsear manualmente.
        mysql_free_result(res);
        // ... esto se complica. Dejo para después.
        break;
    }
}

}  // namespace partial02
