#ifndef PARTIAL02_CONSOLE_HPP
#define PARTIAL02_CONSOLE_HPP

#include "article_catalog.hpp"
#include "message_catalog.hpp"
#include "purchase_order_service.hpp"
#include "supplier_service.hpp"

#include <istream>
#include <ostream>

namespace partial02 {

/// Adaptador de consola: lee opciones y escribe resultados. No conoce reglas
/// de negocio ni almacenamiento. Recibe todas sus dependencias por
/// constructor (DIP/IoC).
class Console {
public:
    Console(std::istream& in, std::ostream& out,
            ArticleCatalog& catalog,
            SupplierService& suppliers,
            PurchaseOrderService& orders,
            MessageCatalog& messages);

    /// Bucle del menú. Devuelve el código de salida del programa.
    int run();

    /// Una operación por opción del menú: públicas para pruebas.
    void createArticle();
    void createSupplier();
    void listSuppliers();
    void updateSupplier();
    void removeSupplier();
    void createOrder();
    void showOrders();

private:
    std::istream& in_;
    std::ostream& out_;
    ArticleCatalog& catalog_;
    SupplierService& suppliers_;
    PurchaseOrderService& orders_;
    MessageCatalog& messages_;

    // Lectura de entrada
    std::string readLine();
    std::string trim(const std::string& s);
    bool readUnsigned(unsigned& out);
    bool readMoney(std::int64_t& outCents);
    bool readDate(Date& out);
    bool readCuit(Cuit& out);

    // Menú
    void showMenu();

    // Wrapper: captura DomainError y traduce al catálogo de mensajes
    template <class Fn>
    void guard(Fn&& fn) {
        try {
            fn();
        } catch (const DomainError& err) {
            out_ << MessageCatalog::translate(err) << "\n";
        }
    }

    // Operaciones
    void doCreateArticle();
    void doCreateSupplier();
    void doListSuppliers();
    void doUpdateSupplier();
    void doRemoveSupplier();
    void doCreateOrder();
    void doShowOrders();
};

}  // namespace partial02

#endif  // PARTIAL02_CONSOLE_HPP
