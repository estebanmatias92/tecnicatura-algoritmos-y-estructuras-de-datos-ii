#include "clock.hpp"
#include "console.hpp"
#include "in_memory_order_number_sequence.hpp"
#include "maria_db_article_repository.hpp"
#include "maria_db_connection.hpp"
#include "maria_db_purchase_order_repository.hpp"
#include "maria_db_supplier_repository.hpp"
#include "message_catalog.hpp"
#include "purchase_order_service.hpp"
#include "supplier_service.hpp"

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

using namespace partial02;

namespace {

/// Lee una variable de entorno; si no está definida, devuelve el default
/// de desarrollo (nunca credenciales reales: RNF-013).
std::string envOrDefault(const std::string& name, const std::string& defaultValue) {
    const char* value = std::getenv(name.c_str());
    return value != nullptr ? std::string(value) : defaultValue;
}

}  // namespace

int main() {
    // Credenciales de la base por variables de entorno con defaults de desarrollo.
    const std::string host = envOrDefault("MARIADB_HOST", "127.0.0.1");
    const std::uint16_t port = static_cast<std::uint16_t>(
        std::stoi(envOrDefault("MARIADB_PORT", "3306")));
    const std::string database = envOrDefault("MARIADB_DATABASE", "parcial02");
    const std::string user = envOrDefault("MARIADB_USER", "parcial02");
    const std::string password = envOrDefault("MARIADB_PASSWORD", "parcial02-pass");

    // RN-017 / AC-017: si la base no responde, informar por consola y terminar
    // con código distinto de cero sin mostrar el menú.
    std::unique_ptr<MariaDbConnection> connection;
    try {
        connection = std::make_unique<MariaDbConnection>(host, port, user, password,
                                                         database);
    } catch (const std::exception& error) {
        std::cerr << "No se pudo conectar con la base de datos: " << error.what()
                  << "\n";
        std::cerr << "Iniciá el contenedor con: docker compose up -d\n";
        return 1;
    }

    // Repositorios MariaDB sobre la misma conexión (DIP: los servicios programan
    // contra Repository<T, K>, no contra una implementación concreta).
    MariaDbSupplierRepository supplierRepo(*connection);
    MariaDbArticleRepository articleRepo(*connection);
    MariaDbPurchaseOrderRepository orderRepo(*connection, articleRepo, supplierRepo);

    // El repositorio de pedidos MariaDB es a su vez la secuencia de números
    // de pedido (MAX(number) + 1 antes del insert, BR-010).
    SystemClock clock;
    SupplierService supplierService(supplierRepo);
    PurchaseOrderService purchaseOrderService(supplierRepo, articleRepo, orderRepo,
                                              orderRepo, clock);
    MessageCatalog messageCatalog;

    // Consola: recibe el catálogo de artículos por el puerto Repository.
    Console console(std::cin, std::cout, articleRepo, supplierService,
                    purchaseOrderService, messageCatalog);

    return console.run();
}
