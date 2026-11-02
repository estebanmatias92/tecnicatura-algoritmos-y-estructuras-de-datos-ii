#include "console.hpp"
#include "format.hpp"

#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <string>

namespace partial02 {

Console::Console(std::istream& in, std::ostream& out,
                 ArticleCatalog& catalog, SupplierService& suppliers,
                 PurchaseOrderService& orders, MessageCatalog& messages)
    : in_(in), out_(out), catalog_(catalog), suppliers_(suppliers),
      orders_(orders), messages_(messages) {}

int Console::run() {
    while (true) {
        showMenu();
        std::string opcion = trim(readLine());
        if (opcion.empty() || opcion == "0") {
            out_ << "Hasta luego.\n";
            return 0;
        }
        if (opcion == "1") {
            createArticle();
        } else if (opcion == "2") {
            createSupplier();
        } else if (opcion == "3") {
            listSuppliers();
        } else if (opcion == "4") {
            updateSupplier();
        } else if (opcion == "5") {
            removeSupplier();
        } else if (opcion == "6") {
            createOrder();
        } else if (opcion == "7") {
            showOrders();
        } else {
            out_ << "Opción inválida. Ingresá un número entre 0 y 7.\n";
        }
    }
}

void Console::showMenu() {
    out_ << "\n";
    out_ << "=== Productos de Goma — Compras de materia prima ===\n";
    out_ << "\n";
    out_ << "1. Cargar artículo\n";
    out_ << "2. Cargar proveedor\n";
    out_ << "3. Listar proveedores\n";
    out_ << "4. Modificar proveedor\n";
    out_ << "5. Eliminar proveedor\n";
    out_ << "6. Cargar pedido\n";
    out_ << "7. Mostrar pedidos\n";
    out_ << "0. Salir\n";
    out_ << "\n";
    out_ << "Opción: ";
}

std::string Console::readLine() {
    std::string line;
    if (!std::getline(in_, line)) {
        return "";
    }
    return line;
}

std::string Console::trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

bool Console::readUnsigned(unsigned& out) {
    std::string line = trim(readLine());
    if (line.empty()) {
        return false;
    }
    for (char c : line) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    out = static_cast<unsigned>(std::stoul(line));
    return true;
}

bool Console::readMoney(std::int64_t& outCents) {
    std::string line = trim(readLine());
    if (line.empty()) {
        return false;
    }
    bool negative = false;
    std::size_t pos = 0;
    if (!line.empty() && line[0] == '-') {
        negative = true;
        pos = 1;
    }
    std::string entero;
    std::string decimales;
    bool separadorEncontrado = false;
    for (std::size_t i = pos; i < line.size(); ++i) {
        char c = line[i];
        if (c == ',' || c == '.') {
            if (separadorEncontrado) {
                return false;
            }
            separadorEncontrado = true;
            continue;
        }
        if (c < '0' || c > '9') {
            return false;
        }
        if (separadorEncontrado) {
            decimales.push_back(c);
        } else {
            entero.push_back(c);
        }
    }
    if (entero.empty()) {
        return false;
    }
    while (decimales.size() > 2) {
        decimales.pop_back();
    }
    while (decimales.size() < 2) {
        decimales.push_back('0');
    }
    std::int64_t cents = 0;
    try {
        cents = std::stoll(entero) * 100 + std::stoll(decimales);
    } catch (...) {
        return false;
    }
    if (negative) {
        cents = -cents;
    }
    outCents = cents;
    return true;
}

bool Console::readDate(Date& out) {
    std::string line = trim(readLine());
    if (line.size() != 10 || line[4] != '-' || line[7] != '-') {
        return false;
    }
    int year = 0, month = 0, day = 0;
    for (int i = 0; i < 4; ++i) {
        if (line[i] < '0' || line[i] > '9') return false;
        year = year * 10 + (line[i] - '0');
    }
    for (int i = 5; i < 7; ++i) {
        if (line[i] < '0' || line[i] > '9') return false;
        month = month * 10 + (line[i] - '0');
    }
    for (int i = 8; i < 10; ++i) {
        if (line[i] < '0' || line[i] > '9') return false;
        day = day * 10 + (line[i] - '0');
    }
    try {
        out = Date(year, month, day);
    } catch (...) {
        return false;
    }
    return true;
}

bool Console::readCuit(Cuit& out) {
    std::string line = trim(readLine());
    try {
        out = Cuit(line);
        return true;
    } catch (...) {
        return false;
    }
}

void Console::createArticle() {
    guard([this]() {
        out_ << "Código de artículo: ";
        std::string code = trim(readLine());
        if (code.empty()) {
            throw ValidationError(ErrorCode::EmptyArticleCode);
        }
        if (catalog_.find(code) != nullptr) {
            throw ConflictError(ErrorCode::DuplicateArticleCode,
                                {{"code", code}});
        }

        out_ << "Descripción: ";
        std::string description = trim(readLine());

        out_ << "Precio unitario (por ejemplo 1500,00): ";
        std::int64_t cents = 0;
        if (!readMoney(cents)) {
            throw ValidationError(ErrorCode::NegativeMoney);
        }
        if (cents <= 0) {
            throw ValidationError(ErrorCode::NonPositiveUnitPrice);
        }

        catalog_.add(std::make_unique<Article>(code, description, Money(cents)));
        out_ << "Artículo " << code << " cargado.\n";
    });
}

void Console::createSupplier() {
    guard([this]() {
        out_ << "CUIT del proveedor (11 dígitos): ";
        Cuit cuit("00000000000");
        if (!readCuit(cuit)) {
            throw ValidationError(ErrorCode::CuitFormat);
        }
        out_ << "Razón social: ";
        std::string businessName = trim(readLine());
        suppliers_.add(cuit, businessName);
        out_ << "Proveedor " << cuit.value() << " - " << businessName
             << " cargado.\n";
    });
}

void Console::listSuppliers() {
    guard([this]() {
        auto suppliers = suppliers_.list();
        // Orden ascendente de CUIT (determinista para pruebas)
        std::sort(suppliers.begin(), suppliers.end(),
                  [](const Supplier* a, const Supplier* b) {
                      return a->cuit() < b->cuit();
                  });
        out_ << "Proveedores registrados:\n";
        if (suppliers.empty()) {
            out_ << "No hay proveedores registrados.\n";
            return;
        }
        for (const Supplier* s : suppliers) {
            out_ << s->cuit().value() << " - " << s->businessName() << "\n";
        }
    });
}

void Console::updateSupplier() {
    guard([this]() {
        out_ << "CUIT del proveedor a modificar: ";
        Cuit cuit("00000000000");
        if (!readCuit(cuit)) {
            throw ValidationError(ErrorCode::CuitFormat);
        }
        out_ << "Nueva razón social (Enter para conservar la actual): ";
        std::string newName = trim(readLine());
        if (!newName.empty()) {
            suppliers_.update(cuit, newName);
        }
        // Mostrar nombre actualizado
        const Supplier* updated = nullptr;
        for (const Supplier* s : suppliers_.list()) {
            if (s->cuit() == cuit) {
                updated = s;
                break;
            }
        }
        if (updated != nullptr) {
            out_ << "Proveedor " << cuit.value() << " - "
                 << updated->businessName() << " modificado.\n";
        }
    });
}

void Console::removeSupplier() {
    guard([this]() {
        out_ << "CUIT del proveedor a eliminar: ";
        Cuit cuit("00000000000");
        if (!readCuit(cuit)) {
            throw ValidationError(ErrorCode::CuitFormat);
        }
        // BR-009: no eliminar proveedor con pedidos asociados
        if (orders_.hasOrdersFor(cuit)) {
            // Contar cuántos pedidos para el mensaje
            auto groups = orders_.ordersBySupplier();
            unsigned count = 0;
            for (const auto& g : groups) {
                if (g.supplier->cuit() == cuit) {
                    count = g.orders.size();
                    break;
                }
            }
            throw ConflictError(ErrorCode::SupplierHasOrders,
                                {{"cuit", cuit.value()},
                                 {"count", std::to_string(count)}});
        }
        suppliers_.remove(cuit);
        out_ << "Proveedor " << cuit.value() << " eliminado.\n";
    });
}

void Console::createOrder() {
    guard([this]() {
        out_ << "CUIT del proveedor del pedido: ";
        Cuit cuit("00000000000");
        if (!readCuit(cuit)) {
            throw ValidationError(ErrorCode::CuitFormat);
        }
        // BR-006: validar que el proveedor existe ANTES de pedir la fecha
        const Supplier* supplier = nullptr;
        for (const Supplier* s : suppliers_.list()) {
            if (s->cuit() == cuit) {
                supplier = s;
                break;
            }
        }
        if (supplier == nullptr) {
            throw NotFoundError(ErrorCode::UnknownSupplier,
                                {{"cuit", cuit.value()}});
        }

        out_ << "Fecha de entrega esperada (AAAA-MM-DD): ";
        Date delivery(1, 1, 1);
        if (!readDate(delivery)) {
            throw ValidationError(ErrorCode::DateFormat);
        }

        std::vector<std::pair<std::string, unsigned>> items;
        while (true) {
            out_ << "Código de artículo (Enter para terminar): ";
            std::string code = trim(readLine());
            if (code.empty()) {
                break;
            }
            out_ << "Cantidad: ";
            unsigned qty = 0;
            if (!readUnsigned(qty)) {
                out_ << "Cantidad inválida. Ingresá un número entero mayor que cero, sin decimales.\n";
                continue;
            }
            items.push_back({code, qty});
        }

        if (items.empty()) {
            throw ValidationError(ErrorCode::EmptyOrder);
        }

        orders_.create(cuit, delivery, items);
        out_ << "Pedido creado.\n";
    });
}

void Console::showOrders() {
    guard([this]() {
        auto groups = orders_.ordersBySupplier();
        bool hayPedidos = false;
        for (const auto& g : groups) {
            if (g.orders.empty()) continue;
            hayPedidos = true;
            out_ << "\n";
            out_ << "Proveedor: " << g.supplier->cuit().value() << " - "
                 << g.supplier->businessName() << "\n";
            for (const auto* po : g.orders) {
                out_ << "  " << *po;
            }
        }
        if (!hayPedidos) {
            out_ << "No hay pedidos registrados.\n";
        }
    });
}

}  // namespace partial02
