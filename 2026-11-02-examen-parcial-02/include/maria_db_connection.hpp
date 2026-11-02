#ifndef PARTIAL02_MARIA_DB_CONNECTION_HPP
#define PARTIAL02_MARIA_DB_CONNECTION_HPP

#include <mysql.h>

#include <cstdint>
#include <string>

namespace partial02 {

/// Conexión MariaDB con RAII: se cierra en el destructor. No hay
/// mysql_close suelto (ADR-0004).
class MariaDbConnection {
public:
    MariaDbConnection(const std::string& host, std::uint16_t port,
                      const std::string& user, const std::string& password,
                      const std::string& database);
    ~MariaDbConnection();

    MariaDbConnection(const MariaDbConnection&) = delete;
    MariaDbConnection& operator=(const MariaDbConnection&) = delete;

    MYSQL* get() const noexcept { return conn_; }

    /// Ejecuta una consulta SQL y devuelve el resultado (llamar a mysql_free_result).
    MYSQL_RES* query(const std::string& sql);

    /// Prepara una sentencia para uso con bind_param/bind_result.
    MYSQL_STMT* prepare(const std::string& sql);

private:
    MYSQL* conn_;
};

}  // namespace partial02

#endif  // PARTIAL02_MARIA_DB_CONNECTION_HPP
