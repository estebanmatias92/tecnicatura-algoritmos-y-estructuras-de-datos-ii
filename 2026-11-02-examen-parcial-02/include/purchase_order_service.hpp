#ifndef PARTIAL02_PURCHASE_ORDER_SERVICE_HPP
#define PARTIAL02_PURCHASE_ORDER_SERVICE_HPP

#include "clock.hpp"
#include "order_number_sequence.hpp"
#include "purchaseorder.hpp"
#include "repository.hpp"
#include "supplier.hpp"

#include <utility>
#include <vector>

namespace partial02 {

/// Vista de lectura: agrupa los pedidos de un proveedor para mostrarlos.
/// No es una entidad del dominio: se arma en cada consulta.
struct SupplierOrders {
    const Supplier* supplier;
    std::vector<const PurchaseOrder*> orders;
};

/// Servicio de pedidos: aplica BR-001, BR-006, BR-007, BR-008, BR-010,
/// BR-011, BR-012.
class PurchaseOrderService {
public:
    PurchaseOrderService(
        MutableRepository<Supplier, Cuit>& supplierRepo,
        Repository<Article, std::string>& catalog,
        Repository<PurchaseOrder, OrderNumber>& orderRepo,
        OrderNumberSequence& sequence,
        Clock& clock);

    /// Crea un pedido. items: pares (código de artículo, cantidad) en orden
    /// de carga. Lanza DomainError si alguna regla de negocio se viola.
    PurchaseOrder create(const Cuit& cuit, const Date& expectedDelivery,
                         const std::vector<std::pair<std::string, unsigned>>& items);

    /// Retorna pedidos agrupados por proveedor (CUIT ascendente, número
    /// ascendente dentro de cada grupo).
    std::vector<SupplierOrders> ordersBySupplier() const;

    /// Indica si el proveedor tiene al menos un pedido asociado (BR-009).
    bool hasOrdersFor(const Cuit& cuit) const;

private:
    MutableRepository<Supplier, Cuit>& supplierRepo_;
    Repository<Article, std::string>& catalog_;
    Repository<PurchaseOrder, OrderNumber>& orderRepo_;
    OrderNumberSequence& sequence_;
    Clock& clock_;
};

}  // namespace partial02

#endif  // PARTIAL02_PURCHASE_ORDER_SERVICE_HPP
