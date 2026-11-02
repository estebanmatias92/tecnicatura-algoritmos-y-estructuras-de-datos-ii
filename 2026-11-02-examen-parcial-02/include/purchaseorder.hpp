#ifndef PARTIAL02_PURCHASEORDER_HPP
#define PARTIAL02_PURCHASEORDER_HPP

#include "article.hpp"
#include "date.hpp"
#include "money.hpp"
#include "ordernumber.hpp"
#include "quantity.hpp"
#include "supplier.hpp"

#include <utility>
#include <vector>

namespace partial02 {

/// Pedido de compra: uno o más artículos asignados a un único proveedor.
/// El puntero a Article es no propietario: el catálogo es dueño.
class PurchaseOrder {
public:
    using Item = std::pair<const Article*, Quantity>;

    PurchaseOrder(OrderNumber number, const Supplier* supplier, Date createdAt,
                  Date expectedDelivery, std::vector<Item> items);

    const OrderNumber& number() const noexcept { return number_; }
    const Supplier* supplier() const noexcept { return supplier_; }
    const Date& createdAt() const noexcept { return createdAt_; }
    const Date& expectedDelivery() const noexcept { return expectedDelivery_; }
    const std::vector<Item>& items() const noexcept { return items_; }

    /// Total del pedido: suma de unitPrice × quantity. Se calcula, no se almacena (BR-012).
    Money total() const;

    bool operator==(const PurchaseOrder& other) const noexcept { return number_ == other.number_; }
    bool operator!=(const PurchaseOrder& other) const noexcept { return !(*this == other); }
    bool operator<(const PurchaseOrder& other) const noexcept { return number_ < other.number_; }

private:
    OrderNumber number_;
    const Supplier* supplier_;
    Date createdAt_;
    Date expectedDelivery_;
    std::vector<Item> items_;
};

}  // namespace partial02

#endif  // PARTIAL02_PURCHASEORDER_HPP
