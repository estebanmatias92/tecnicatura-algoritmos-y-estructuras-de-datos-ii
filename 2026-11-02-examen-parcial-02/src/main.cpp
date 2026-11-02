#include "app.hpp"

#include "article_catalog.hpp"
#include "clock.hpp"
#include "console.hpp"
#include "in_memory_order_number_sequence.hpp"
#include "inmemory_repository.hpp"
#include "message_catalog.hpp"
#include "purchase_order_service.hpp"
#include "supplier_service.hpp"

#include <iostream>
#include <memory>

using namespace partial02;

int main() {
    // Catálogo de artículos (dueño de los objetos Article)
    ArticleCatalog catalog;

    // Repositorios en memoria
    InMemoryRepository<Supplier, Cuit> supplierRepo(
        [](const Supplier& s) { return s.cuit(); });
    InMemoryRepository<PurchaseOrder, OrderNumber> orderRepo(
        [](const PurchaseOrder& o) { return o.number(); });

    // Secuencia de números de pedido
    InMemoryOrderNumberSequence sequence;

    // Reloj del sistema
    SystemClock clock;

    // Servicios
    SupplierService supplierService(supplierRepo);
    PurchaseOrderService purchaseOrderService(supplierRepo, catalog, orderRepo,
                                              sequence, clock);

    // Catálogo de mensajes
    MessageCatalog messageCatalog;

    // Consola
    Console console(std::cin, std::cout, catalog, supplierService,
                    purchaseOrderService, messageCatalog);

    return console.run();
}
