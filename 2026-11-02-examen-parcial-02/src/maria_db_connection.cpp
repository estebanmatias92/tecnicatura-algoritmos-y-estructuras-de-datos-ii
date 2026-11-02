#include "maria_db_connection.hpp"

#include <mysql.h>
#include <stdexcept>
#include <string>

namespace partial02 {

MariaDbConnection::MariaDbConnection(const std::string& host,
                                     std::uint16_t port,
                                     const std::string& user,
                                     const std::string& password,
                                     const std::string& database)
    : conn_(mysql_init(nullptr)) {
    if (conn_ == nullptr) {
        throw std::runtime_error("No se pudo inicializar la conexión MariaDB");
    }

    if (mysql_real_connect(conn_, host.c_str(), user.c_str(),
                           password.c_str(), database.c_str(),
                           port, nullptr, 0) == nullptr) {
        std::string err = mysql_error(conn_);
        mysql_close(conn_);
        conn_ = nullptr;
        throw std::runtime_error("No se pudo conectar a MariaDB: " + err);
    }
}

MariaDbConnection::~MariaDbConnection() {
    if (conn_ != nullptr) {
        mysql_close(conn_);
    }
}

MYSQL_RES* MariaDbConnection::query(const std::string& sql) {
    if (mysql_query(conn_, sql.c_str()) != 0) {
        throw std::runtime_error("Error en consulta SQL: " +
                                 std::string(mysql_error(conn_)));
    }
    return mysql_store_result(conn_);
}

MYSQL_STMT* MariaDbConnection::prepare(const std::string& sql) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn_);
    if (stmt == nullptr) {
        throw std::runtime_error("No se pudo inicializar sentencia: " +
                                 std::string(mysql_error(conn_)));
    }
    if (mysql_stmt_prepare(stmt, sql.c_str(), sql.size()) != 0) {
        mysql_stmt_close(stmt);
        throw std::runtime_error("Error al preparar sentencia: " +
                                 std::string(mysql_stmt_error(stmt)));
    }
    return stmt;
}

}  // namespace partial02
