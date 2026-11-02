#ifndef PARTIAL02_IN_MEMORY_ORDER_NUMBER_SEQUENCE_HPP
#define PARTIAL02_IN_MEMORY_ORDER_NUMBER_SEQUENCE_HPP

#include "order_number_sequence.hpp"

namespace partial02 {

/// Doble en memoria de OrderNumberSequence para pruebas.
class InMemoryOrderNumberSequence : public OrderNumberSequence {
public:
    explicit InMemoryOrderNumberSequence(unsigned start = 1)
        : next_(start) {}

    OrderNumber nextNumber() override {
        return OrderNumber(next_++);
    }

private:
    unsigned next_;
};

}  // namespace partial02

#endif  // PARTIAL02_IN_MEMORY_ORDER_NUMBER_SEQUENCE_HPP
