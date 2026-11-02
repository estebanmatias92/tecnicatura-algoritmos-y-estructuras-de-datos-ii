#include "maria_db_article_repository.hpp"

#include <mysql.h>
#include <stdexcept>
#include <string>
#include <cstring>

namespace partial02 {

MariaDbArticleRepository::MariaDbArticleRepository(MariaDbConnection& conn)
    : conn_(conn) {}

void MariaDbArticleRepository::loadAll() const {
    if (!cache_.empty()) {
        return;
    }
    MYSQL_RES* res = conn_.query(
        "SELECT code, description, unit_price_cents FROM articles");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr) {
        std::string code(row[0] ? row[0] : "");
        std::string desc(row[1] ? row[1] : "");
        std::int64_t cents = row[2] ? std::stoll(row[2]) : 0;
        cache_.push_back(
            std::make_unique<Article>(code, desc, partial02::Money(cents)));
    }
    mysql_free_result(res);
}

const Article* MariaDbArticleRepository::findInCache(
    const std::string& key) const {
    for (const auto& ptr : cache_) {
        if (ptr->code() == key) {
            return ptr.get();
        }
    }
    return nullptr;
}

const Article* MariaDbArticleRepository::find(const std::string& key) const {
    loadAll();
    if (const Article* found = findInCache(key)) {
        return found;
    }
    MYSQL_STMT* stmt = conn_.prepare(
        "SELECT code, description, unit_price_cents FROM articles WHERE code = ?");
    const char* codeStr = key.c_str();
    unsigned long codeLen = key.size();
    MYSQL_BIND bind{};
    bind.buffer_type = MYSQL_TYPE_STRING;
    bind.buffer = const_cast<char*>(codeStr);
    bind.length = &codeLen;
    mysql_stmt_bind_param(stmt, &bind);
    mysql_stmt_execute(stmt);
    MYSQL_RES* res = mysql_stmt_result_metadata(stmt);
    MYSQL_ROW row;
    const Article* result = nullptr;
    if (res != nullptr && (row = mysql_fetch_row(res)) != nullptr) {
        std::string code(row[0] ? row[0] : "");
        std::string desc(row[1] ? row[1] : "");
        std::int64_t cents = row[2] ? std::stoll(row[2]) : 0;
        cache_.push_back(
            std::make_unique<Article>(code, desc, partial02::Money(cents)));
        result = cache_.back().get();
    }
    mysql_free_result(res);
    mysql_stmt_close(stmt);
    return result;
}

std::vector<const Article*> MariaDbArticleRepository::all() const {
    loadAll();
    std::vector<const Article*> result;
    result.reserve(cache_.size());
    for (const auto& ptr : cache_) {
        result.push_back(ptr.get());
    }
    return result;
}

void MariaDbArticleRepository::add(const Article& entity) {
    MYSQL_STMT* stmt = conn_.prepare(
        "INSERT INTO articles (code, description, unit_price_cents) VALUES (?, ?, ?)");
    const char* codeStr = entity.code().c_str();
    unsigned long codeLen = entity.code().size();
    const char* descStr = entity.description().c_str();
    unsigned long descLen = entity.description().size();
    std::int64_t cents = entity.unitPrice().cents();

    MYSQL_BIND bind[3]{};
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = const_cast<char*>(codeStr);
    bind[0].length = &codeLen;
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = const_cast<char*>(descStr);
    bind[1].length = &descLen;
    bind[2].buffer_type = MYSQL_TYPE_INT64;
    bind[2].buffer = &cents;

    mysql_stmt_bind_param(stmt, bind);
    if (mysql_stmt_execute(stmt) != 0) {
        mysql_stmt_close(stmt);
        throw std::runtime_error("Error al insertar artículo: " +
                                 std::string(mysql_stmt_error(stmt)));
    }
    mysql_stmt_close(stmt);

    cache_.push_back(std::make_unique<Article>(entity));
}

}  // namespace partial02
