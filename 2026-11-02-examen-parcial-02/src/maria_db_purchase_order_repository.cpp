#include "maria_db_purchase_order_repository.hpp"
#include "maria_db_article_repository.hpp"
#include "maria_db_supplier_repository.hpp"

#include <mysql.h>
#include <stdexcept>
#include <string>
#include <cstring>

namespace partial02 {

namespace {

/// Parsea una fecha en formato "YYYY-MM-DD" tal como la devuelve MariaDB para
/// una columna DATE.
Date parseDate(const std::string& text) {
    if (text.size() != 10 || text[4] != '-' || text[7] != '-') {
        throw std::runtime_error("Fecha inválida en la base de datos: " + text);
    }
    int year = std::stoi(text.substr(0, 4));
    int month = std::stoi(text.substr(5, 2));
    int day = std::stoi(text.substr(8, 2));
    return Date(year, month, day);
}

}  // namespace

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

std::vector<PurchaseOrder::Item> MariaDbPurchaseOrderRepository::loadItems(
    const OrderNumber& number) const {
    // order_number proviene de la propia aplicación, no de entrada del usuario.
    MYSQL_RES* res = conn_.query(
        "SELECT article_code, quantity, position FROM purchase_order_items "
        "WHERE order_number = " + std::to_string(number.value()) +
        " ORDER BY position");
    MYSQL_ROW row;
    std::vector<PurchaseOrder::Item> items;
    while ((row = mysql_fetch_row(res)) != nullptr) {
        const Article* article =
            articleRepo_.find(row[0] ? row[0] : "");
        if (article == nullptr) {
            mysql_free_result(res);
            throw std::runtime_error("Artículo " +
                                     std::string(row[0] ? row[0] : "") +
                                     " no encontrado al cargar el pedido " +
                                     std::to_string(number.value()));
        }
        unsigned int quantity =
            row[1] ? static_cast<unsigned int>(std::stoul(row[1])) : 0u;
        items.push_back({article, Quantity(quantity)});
    }
    mysql_free_result(res);
    return items;
}

const PurchaseOrder* MariaDbPurchaseOrderRepository::find(const OrderNumber& key) const {
    loadAll();
    for (const auto& ptr : cache_) {
        if (ptr->number() == key) {
            return ptr.get();
        }
    }
    return nullptr;
}

std::vector<const PurchaseOrder*> MariaDbPurchaseOrderRepository::all() const {
    loadAll();
    std::vector<const PurchaseOrder*> result;
    result.reserve(cache_.size());
    for (const auto& ptr : cache_) {
        result.push_back(ptr.get());
    }
    return result;
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
        OrderNumber number(static_cast<unsigned int>(std::stoul(row[0] ? row[0] : "0")));
        Cuit cuit(row[1] ? row[1] : "");
        Date createdAt = parseDate(row[2] ? row[2] : "");
        Date expectedDelivery = parseDate(row[3] ? row[3] : "");

        const Supplier* supplier = supplierRepo_.find(cuit);
        if (supplier == nullptr) {
            mysql_free_result(res);
            throw std::runtime_error("Proveedor " + cuit.value() +
                                     " no encontrado al cargar el pedido " +
                                     std::to_string(number.value()));
        }

        std::vector<PurchaseOrder::Item> items = loadItems(number);
        cache_.push_back(std::make_unique<PurchaseOrder>(number, supplier, createdAt,
                                                         expectedDelivery, std::move(items)));
    }
    mysql_free_result(res);
}

void MariaDbPurchaseOrderRepository::add(const PurchaseOrder& entity) {
    MYSQL_STMT* stmt = conn_.prepare(
        "INSERT INTO purchase_orders (number, supplier_cuit, created_at, expected_delivery) "
        "VALUES (?, ?, ?, ?)");
    unsigned int numberValue = entity.number().value();
    std::string createdAtStr = entity.createdAt().to_string();
    std::string expectedDeliveryStr = entity.expectedDelivery().to_string();
    const char* cuitStr = entity.supplier()->cuit().value().c_str();
    unsigned long cuitLen = entity.supplier()->cuit().value().size();
    unsigned long createdAtLen = createdAtStr.size();
    unsigned long expectedDeliveryLen = expectedDeliveryStr.size();

    unsigned long numberLen = sizeof(numberValue);
    MYSQL_BIND bind[4]{};
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &numberValue;
    bind[0].length = &numberLen;
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = const_cast<char*>(cuitStr);
    bind[1].length = &cuitLen;
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = const_cast<char*>(createdAtStr.c_str());
    bind[2].length = &createdAtLen;
    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = const_cast<char*>(expectedDeliveryStr.c_str());
    bind[3].length = &expectedDeliveryLen;

    mysql_stmt_bind_param(stmt, bind);
    if (mysql_stmt_execute(stmt) != 0) {
        mysql_stmt_close(stmt);
        throw std::runtime_error("Error al insertar pedido: " +
                                 std::string(mysql_stmt_error(stmt)));
    }
    mysql_stmt_close(stmt);

    // Ítems: la clave compuesta (order_number, article_code) hace cumplir
    // BR-008 en la base; la columna position conserva el orden de carga.
    MYSQL_STMT* istmt = conn_.prepare(
        "INSERT INTO purchase_order_items (order_number, article_code, quantity, position) "
        "VALUES (?, ?, ?, ?)");
    int position = 1;
    for (const auto& item : entity.items()) {
        const std::string& code = item.first->code();
        unsigned long codeLen = code.size();
        unsigned int quantity = item.second.value();
        unsigned long quantityLen = sizeof(quantity);
        unsigned long positionLen = sizeof(position);
        MYSQL_BIND ibind[4]{};
        ibind[0].buffer_type = MYSQL_TYPE_LONG;
        ibind[0].buffer = &numberValue;
        ibind[0].length = &numberLen;
        ibind[1].buffer_type = MYSQL_TYPE_STRING;
        ibind[1].buffer = const_cast<char*>(code.c_str());
        ibind[1].length = &codeLen;
        ibind[2].buffer_type = MYSQL_TYPE_LONG;
        ibind[2].buffer = &quantity;
        ibind[2].length = &quantityLen;
        ibind[3].buffer_type = MYSQL_TYPE_LONG;
        ibind[3].buffer = &position;
        ibind[3].length = &positionLen;

        mysql_stmt_bind_param(istmt, ibind);
        if (mysql_stmt_execute(istmt) != 0) {
            mysql_stmt_close(istmt);
            throw std::runtime_error("Error al insertar ítem del pedido: " +
                                     std::string(mysql_stmt_error(istmt)));
        }
        ++position;
    }
    mysql_stmt_close(istmt);

    // Caché coherente con la base (punteros estables para find()/all()).
    cache_.push_back(std::make_unique<PurchaseOrder>(entity));
}

}  // namespace partial02
