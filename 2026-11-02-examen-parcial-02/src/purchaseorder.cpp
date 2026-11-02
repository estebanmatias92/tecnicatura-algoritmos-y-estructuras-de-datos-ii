#include "purchaseorder.hpp"

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

}  // namespace partial02
