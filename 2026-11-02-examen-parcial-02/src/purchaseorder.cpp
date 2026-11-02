#include "purchaseorder.hpp"

#include "format.hpp"

#include <stdexcept>

namespace partial02 {

PurchaseOrder::PurchaseOrder(OrderNumber number, const Supplier* supplier,
                             Date createdAt, Date expectedDelivery,
                             std::vector<Item> items)
    : number_(std::move(number)),
      supplier_(supplier),
      createdAt_(std::move(createdAt)),
      expectedDelivery_(std::move(expectedDelivery)),
      items_(std::move(items)) {
    if (supplier_ == nullptr) {
        throw std::invalid_argument("PurchaseOrder requires a supplier");
    }
    if (items_.empty()) {
        throw std::invalid_argument("PurchaseOrder must have at least one item");
    }
    if (expectedDelivery_ < createdAt_) {
        throw std::invalid_argument("Expected delivery cannot be before creation date");
    }
}

Money PurchaseOrder::total() const {
    std::int64_t sum = 0;
    for (const auto& item : items_) {
        sum += item.first->unitPrice().cents() * static_cast<std::int64_t>(item.second.value());
    }
    return Money(sum);
}

std::ostream& operator<<(std::ostream& os, const PurchaseOrder& po) {
    os << "Pedido " << po.number().value() << " - creado " << po.createdAt().to_string()
       << " - entrega " << po.expectedDelivery().to_string() << "\n";
    for (const auto& item : po.items()) {
        std::int64_t subtotalCents =
            item.first->unitPrice().cents() *
            static_cast<std::int64_t>(item.second.value());
        os << "    " << item.first->code() << " " << item.first->description() << ": "
           << item.second.value() << " x "
           << formatMoney(item.first->unitPrice().cents()) << " = "
           << formatMoney(subtotalCents) << "\n";
    }
    os << "  Total del pedido: " << formatMoney(po.total().cents()) << "\n";
    return os;
}

}  // namespace partial02
