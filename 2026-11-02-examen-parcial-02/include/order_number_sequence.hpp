#ifndef PARTIAL02_ORDER_NUMBER_SEQUENCE_HPP
#define PARTIAL02_ORDER_NUMBER_SEQUENCE_HPP

#include "ordernumber.hpp"

namespace partial02 {

/// Puerto que entrega el siguiente OrderNumber antes de persistir el pedido.
/// Implementado por el repositorio MariaDB (antes del insert) y por un doble
/// en memoria para pruebas.
class OrderNumberSequence {
public:
    virtual ~OrderNumberSequence() = default;
    virtual OrderNumber nextNumber() = 0;
};

}  // namespace partial02

#endif  // PARTIAL02_ORDER_NUMBER_SEQUENCE_HPP
