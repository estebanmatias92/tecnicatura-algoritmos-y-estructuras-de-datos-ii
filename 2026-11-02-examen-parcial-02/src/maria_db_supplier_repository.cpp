#include "maria_db_supplier_repository.hpp"

#include <mysql.h>
#include <stdexcept>
#include <string>
#include <cstring>

namespace partial02 {

MariaDbSupplierRepository::MariaDbSupplierRepository(MariaDbConnection& conn)
    : conn_(conn) {}

void MariaDbSupplierRepository::loadAll() const {
    if (!cache_.empty()) {
        return;  // Ya cargado
    }
    MYSQL_RES* res = conn_.query("SELECT cuit, business_name FROM suppliers");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr) {
        Cuit cuit(row[0] ? row[0] : "");
        std::string name(row[1] ? row[1] : "");
        cache_.push_back(std::make_unique<Supplier>(cuit, name));
    }
    mysql_free_result(res);
}

const Supplier* MariaDbSupplierRepository::findInCache(const Cuit& key) const {
    for (const auto& ptr : cache_) {
        if (ptr->cuit() == key) {
            return ptr.get();
        }
    }
    return nullptr;
}

const Supplier* MariaDbSupplierRepository::find(const Cuit& key) const {
    loadAll();
    if (const Supplier* found = findInCache(key)) {
        return found;
    }
    // No está en caché: consultar la base directamente
    MYSQL_STMT* stmt = conn_.prepare(
        "SELECT cuit, business_name FROM suppliers WHERE cuit = ?");
    const char* cuitStr = key.value().c_str();
    unsigned long cuitLen = key.value().size();
    MYSQL_BIND bind{};
    bind.buffer_type = MYSQL_TYPE_STRING;
    bind.buffer = const_cast<char*>(cuitStr);
    bind.length = &cuitLen;
    mysql_stmt_bind_param(stmt, &bind);
    mysql_stmt_execute(stmt);
    MYSQL_RES* res = mysql_stmt_result_metadata(stmt);
    MYSQL_ROW row;
    const Supplier* result = nullptr;
    if (res != nullptr && (row = mysql_fetch_row(res)) != nullptr) {
        Cuit cuit(row[0] ? row[0] : "");
        std::string name(row[1] ? row[1] : "");
        cache_.push_back(std::make_unique<Supplier>(cuit, name));
        result = cache_.back().get();
    }
    mysql_free_result(res);
    mysql_stmt_close(stmt);
    return result;
}

std::vector<const Supplier*> MariaDbSupplierRepository::all() const {
    loadAll();
    std::vector<const Supplier*> result;
    result.reserve(cache_.size());
    for (const auto& ptr : cache_) {
        result.push_back(ptr.get());
    }
    return result;
}

void MariaDbSupplierRepository::add(const Supplier& entity) {
    MYSQL_STMT* stmt = conn_.prepare(
        "INSERT INTO suppliers (cuit, business_name) VALUES (?, ?)");
    const char* cuitStr = entity.cuit().value().c_str();
    unsigned long cuitLen = entity.cuit().value().size();
    const char* nameStr = entity.businessName().c_str();
    unsigned long nameLen = entity.businessName().size();

    MYSQL_BIND bind[2]{};
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(cuitStr);
    bind[0].length = &cuitLen;
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = const_cast<char*>(nameStr);
    bind[1].length = &nameLen;

    mysql_stmt_bind_param(stmt, bind);
    if (mysql_stmt_execute(stmt) != 0) {
        mysql_stmt_close(stmt);
        throw std::runtime_error("Error al insertar proveedor: " +
                                 std::string(mysql_stmt_error(stmt)));
    }
    mysql_stmt_close(stmt);

    // Agregar al caché
    cache_.push_back(std::make_unique<Supplier>(entity));
}

void MariaDbSupplierRepository::update(const Supplier& entity) {
    MYSQL_STMT* stmt = conn_.prepare(
        "UPDATE suppliers SET business_name = ? WHERE cuit = ?");
    const char* nameStr = entity.businessName().c_str();
    unsigned long nameLen = entity.businessName().size();
    const char* cuitStr = entity.cuit().value().c_str();
    unsigned long cuitLen = entity.cuit().value().size();

    MYSQL_BIND bind[2]{};
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(nameStr);
    bind[0].length = &nameLen;
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = const_cast<char*>(cuitStr);
    bind[1].length = &cuitLen;

    mysql_stmt_bind_param(stmt, bind);
    if (mysql_stmt_execute(stmt) != 0) {
        mysql_stmt_close(stmt);
        throw std::runtime_error("Error al actualizar proveedor: " +
                                 std::string(mysql_stmt_error(stmt)));
    }
    mysql_stmt_close(stmt);

    // Actualizar en caché
    for (auto& ptr : cache_) {
        if (ptr->cuit() == entity.cuit()) {
            *ptr = entity;
            return;
        }
    }
}

void MariaDbSupplierRepository::remove(const Cuit& key) {
    MYSQL_STMT* stmt = conn_.prepare(
        "DELETE FROM suppliers WHERE cuit = ?");
    const char* cuitStr = key.value().c_str();
    unsigned long cuitLen = key.value().size();

    MYSQL_BIND bind[1]{};
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(cuitStr);
    bind[0].length = &cuitLen;

    mysql_stmt_bind_param(stmt, bind);
    if (mysql_stmt_execute(stmt) != 0) {
        mysql_stmt_close(stmt);
        throw std::runtime_error("Error al eliminar proveedor: " +
                                 std::string(mysql_stmt_error(stmt)));
    }
    mysql_stmt_close(stmt);

    // Eliminar del caché
    auto it = std::remove_if(cache_.begin(), cache_.end(),
                             [&](const std::unique_ptr<Supplier>& ptr) {
                                 return ptr->cuit() == key;
                             });
    if (it != cache_.end()) {
        cache_.erase(it, cache_.end());
    }
}

}  // namespace partial02
