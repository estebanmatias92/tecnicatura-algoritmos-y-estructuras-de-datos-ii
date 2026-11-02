#include "purchase_order_service.hpp"

#include "domain_error.hpp"

#include <algorithm>

namespace partial02 {

PurchaseOrderService::PurchaseOrderService(
    MutableRepository<Supplier, Cuit>& supplierRepo,
    ArticleCatalog& catalog,
    Repository<PurchaseOrder, OrderNumber>& orderRepo,
    OrderNumberSequence& sequence,
    Clock& clock)
    : supplierRepo_(supplierRepo),
      catalog_(catalog),
      orderRepo_(orderRepo),
      sequence_(sequence),
      clock_(clock) {}

PurchaseOrder PurchaseOrderService::create(
    const Cuit& cuit, const Date& expectedDelivery,
    const std::vector<std::pair<std::string, unsigned>>& items) {
    // BR-006: el proveedor debe existir
    const Supplier* supplier = supplierRepo_.find(cuit);
    if (supplier == nullptr) {
        throw NotFoundError(ErrorCode::UnknownSupplier,
                            {{"cuit", cuit.value()}});
    }

    // RN-013: fecha de creación es hoy (no editable)
    Date createdAt = clock_.now();

    // BR-011: entrega no anterior a creación
    if (expectedDelivery < createdAt) {
        throw ValidationError(ErrorCode::DeliveryBeforeCreation,
                              {{"createdAt", createdAt.to_string()}});
    }

    // BR-007: al menos un artículo
    if (items.empty()) {
        throw ValidationError(ErrorCode::EmptyOrder);
    }

    // Resolver artículos, validar existencia (BR-007), cantidad (BR-001),
    // y no duplicado (BR-008)
    std::vector<PurchaseOrder::Item> resolvedItems;
    for (const auto& [code, qty] : items) {
        if (qty == 0) {
            throw ValidationError(ErrorCode::NonPositiveQuantity);
        }
        const Article* article = catalog_.find(code);
        if (article == nullptr) {
            throw NotFoundError(ErrorCode::UnknownArticle,
                                {{"code", code}});
        }
        for (const auto& existing : resolvedItems) {
            if (existing.first == article) {
                throw ConflictError(ErrorCode::DuplicateArticleInOrder,
                                    {{"code", code}});
            }
        }
        resolvedItems.push_back({article, Quantity(qty)});
    }

    // BR-010: número autogenerado antes de persistir
    OrderNumber number = sequence_.nextNumber();

    PurchaseOrder order(number, supplier, createdAt, expectedDelivery,
                        std::move(resolvedItems));
    orderRepo_.add(order);
    return order;
}

std::vector<SupplierOrders> PurchaseOrderService::ordersBySupplier() const {
    const std::vector<const Supplier*> allSuppliers = supplierRepo_.all();
    const std::vector<const PurchaseOrder*> allOrders = orderRepo_.all();

    // Crear un grupo por cada proveedor (orden de allSuppliers)
    std::vector<SupplierOrders> groups;
    groups.reserve(allSuppliers.size());
    for (const Supplier* supplier : allSuppliers) {
        groups.push_back({supplier, {}});
    }

    // Asignar cada pedido al grupo de su proveedor
    for (const PurchaseOrder* order : allOrders) {
        for (auto& group : groups) {
            if (group.supplier == order->supplier()) {
                group.orders.push_back(order);
                break;
            }
        }
    }

    // Filtrar grupos sin pedidos y ordenar
    std::vector<SupplierOrders> result;
    for (auto& group : groups) {
        if (!group.orders.empty()) {
            // Ordenar pedidos dentro del grupo por número ascendente
            std::sort(group.orders.begin(), group.orders.end(),
                      [](const PurchaseOrder* a, const PurchaseOrder* b) {
                          return a->number() < b->number();
                      });
            result.push_back(std::move(group));
        }
    }

    // Los grupos ya están en orden de allSuppliers, que viene del repositorio.
    // Para garantizar orden ascendente de CUIT, ordenamos los grupos.
    std::sort(result.begin(), result.end(),
              [](const SupplierOrders& a, const SupplierOrders& b) {
                  return a.supplier->cuit() < b.supplier->cuit();
              });

    return result;
}

bool PurchaseOrderService::hasOrdersFor(const Cuit& cuit) const {
    const std::vector<const PurchaseOrder*> allOrders = orderRepo_.all();
    for (const PurchaseOrder* order : allOrders) {
        if (order->supplier()->cuit() == cuit) {
            return true;
        }
    }
    return false;
}

}  // namespace partial02
