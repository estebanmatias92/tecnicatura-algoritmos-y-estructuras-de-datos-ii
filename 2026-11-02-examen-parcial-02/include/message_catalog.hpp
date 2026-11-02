#ifndef PARTIAL02_MESSAGE_CATALOG_HPP
#define PARTIAL02_MESSAGE_CATALOG_HPP

#include "domain_error.hpp"

#include <string>

namespace partial02 {

/// Catálogo de mensajes en español. Traduce un DomainError (código en inglés +
/// campos) a la plantilla MSG-### que ve el operador.
/// Los textos en español viven SOLO aquí; el dominio nunca arma oraciones.
class MessageCatalog {
public:
    /// Traduce un error de dominio a su mensaje en español.
    static std::string translate(const DomainError& err);
};

}  // namespace partial02

#endif  // PARTIAL02_MESSAGE_CATALOG_HPP
