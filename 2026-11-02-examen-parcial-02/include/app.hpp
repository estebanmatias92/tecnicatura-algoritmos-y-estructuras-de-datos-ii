#ifndef PARTIAL02_APP_HPP
#define PARTIAL02_APP_HPP

#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "article.hpp"
#include "cuit.hpp"
#include "date.hpp"
#include "money.hpp"
#include "ordernumber.hpp"
#include "purchaseorder.hpp"
#include "quantity.hpp"
#include "supplier.hpp"

namespace partial02 {

/// Versión "antes" del examen: una sola clase que concentra menú,
/// almacenamiento, validación y formateo (defectos plantados a propósito).
///
/// Recibe sus streams por constructor: ese es el borde de comportamiento
/// estable que permite escribir la suite de pruebas sin tocar stdin.
class App {
public:
    App(std::istream& in, std::ostream& out);

    /// Bucle del menú. Devuelve el código de salida del programa.
    int run();

    /// Una operación por opción del menú: públicas para que las pruebas
    /// las llamen sin recorrer el bucle.
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

    // Almacenamiento en memoria (RAII: unique_ptr, delete automático)
    std::vector<std::unique_ptr<Article>> articles_;
    std::vector<std::unique_ptr<Supplier>> suppliers_;
    std::vector<std::unique_ptr<PurchaseOrder>> orders_;
    unsigned nextOrderNumber_ = 1;

    // Búsqueda (tres bloques copiados a mano: defecto #4 embrionario)
    Supplier* findSupplier(const Cuit& cuit);
    Article* findArticle(const std::string& code);

    // Lectura
    std::string readLine();
    bool readUnsigned(unsigned& out);
    bool readMoney(std::int64_t& outCents);
    bool readDate(Date& out);
    bool readCuit(Cuit& out);

    // Menú
    void showMenu();

    // Operaciones (implementación privada; los métodos públicos delegan)
    void doCreateArticle();
    void doCreateSupplier();
    void doListSuppliers();
    void doUpdateSupplier();
    void doRemoveSupplier();
    void doCreateOrder();
    void doShowOrders();

    // Mensajes (hardcodeados en el "antes"; se extraen a MessageCatalog en SRP)
    void msg(const std::string& text);
};

}  // namespace partial02

#endif  // PARTIAL02_APP_HPP
