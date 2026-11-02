#include "app.hpp"

#include "domain_error.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace partial02 {

namespace {

std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string formatMoney(std::int64_t cents) {
    std::ostringstream os;
    bool negative = cents < 0;
    std::int64_t absCents = negative ? -cents : cents;
    std::int64_t pesos = absCents / 100;
    std::int64_t centavos = absCents % 100;
    if (negative) {
        os << "-";
    }
    os << pesos << "," << std::setw(2) << std::setfill('0') << centavos;
    return os.str();
}

}  // namespace

App::App(std::istream& in, std::ostream& out) : in_(in), out_(out) {}

int App::run() {
    while (true) {
        showMenu();
        std::string opcion = trim(readLine());
        if (opcion.empty() || opcion == "0") {
            msg("Hasta luego.");
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
            msg("Opción inválida. Ingresá un número entre 0 y 7.");
        }
    }
}

void App::showMenu() {
    out_ << "\n";
    msg("=== Productos de Goma — Compras de materia prima ===");
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

std::string App::readLine() {
    std::string line;
    if (!std::getline(in_, line)) {
        return "";  // EOF: se trata como salida
    }
    return line;
}

bool App::readUnsigned(unsigned& out) {
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

bool App::readMoney(std::int64_t& outCents) {
    std::string line = trim(readLine());
    if (line.empty()) {
        return false;
    }
    // Acepta coma decimal, hasta 2 decimales. Opcional signo negativo.
    bool negative = false;
    std::size_t pos = 0;
    if (!line.empty() && line[0] == '-') {
        negative = true;
        pos = 1;
    }
    std::string entero;
    std::string decimales;
    bool puntoComaEncontrado = false;
    for (std::size_t i = pos; i < line.size(); ++i) {
        char c = line[i];
        if (c == ',' || c == '.') {
            if (puntoComaEncontrado) {
                return false;  // dos separadores
            }
            puntoComaEncontrado = true;
            continue;
        }
        if (c < '0' || c > '9') {
            return false;
        }
        if (puntoComaEncontrado) {
            decimales.push_back(c);
        } else {
            entero.push_back(c);
        }
    }
    if (entero.empty()) {
        return false;
    }
    // Redondear/truncar decimales a 2 dígitos
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

bool App::readDate(Date& out) {
    std::string line = trim(readLine());
    if (line.size() != 10) {
        return false;
    }
    if (line[4] != '-' || line[7] != '-') {
        return false;
    }
    int year = 0, month = 0, day = 0;
    for (int i = 0; i < 4; ++i) {
        if (line[i] < '0' || line[i] > '9') {
            return false;
        }
        year = year * 10 + (line[i] - '0');
    }
    for (int i = 5; i < 7; ++i) {
        if (line[i] < '0' || line[i] > '9') {
            return false;
        }
        month = month * 10 + (line[i] - '0');
    }
    for (int i = 8; i < 10; ++i) {
        if (line[i] < '0' || line[i] > '9') {
            return false;
        }
        day = day * 10 + (line[i] - '0');
    }
    try {
        out = Date(year, month, day);
    } catch (...) {
        return false;
    }
    return true;
}

bool App::readCuit(Cuit& out) {
    std::string line = trim(readLine());
    try {
        out = Cuit(line);
        return true;
    } catch (...) {
        return false;
    }
}

Supplier* App::findSupplier(const Cuit& cuit) {
    for (auto& s : suppliers_) {
        if (s->cuit() == cuit) {
            return s.get();
        }
    }
    return nullptr;
}

Article* App::findArticle(const std::string& code) {
    for (auto& a : articles_) {
        if (a->code() == code) {
            return a.get();
        }
    }
    return nullptr;
}

void App::msg(const std::string& text) {
    out_ << text << "\n";
}

void App::createArticle() {
    msg("Código de artículo: ");
    std::string code = trim(readLine());
    if (code.empty()) {
        msg("El código de artículo no puede estar vacío.");
        return;
    }
    if (findArticle(code) != nullptr) {
        msg("Ya existe un artículo con el código " + code + ".");
        return;
    }

    msg("Descripción: ");
    std::string description = trim(readLine());

    msg("Precio unitario (por ejemplo 1500,00): ");
    std::int64_t cents = 0;
    if (!readMoney(cents)) {
        msg("Importe inválido. Usá el formato 1500,00 (coma decimal, hasta dos decimales).");
        return;
    }
    if (cents < 0) {
        msg("El importe no puede ser negativo.");
        return;
    }
    Money unitPrice(cents);
    if (unitPrice.cents() <= 0) {
        msg("El precio unitario debe ser mayor que cero.");
        return;
    }

    articles_.push_back(std::make_unique<Article>(code, description, unitPrice));
    msg("Artículo " + code + " cargado.");
}

void App::createSupplier() {
    msg("CUIT del proveedor (11 dígitos): ");
    Cuit cuit("00000000000");  // placeholder, se reemplaza si readCuit tiene éxito
    if (!readCuit(cuit)) {
        msg("El CUIT debe tener exactamente 11 dígitos numéricos.");
        return;
    }
    if (findSupplier(cuit) != nullptr) {
        msg("Ya existe un proveedor con el CUIT " + cuit.value() + ".");
        return;
    }

    msg("Razón social: ");
    std::string businessName = trim(readLine());
    if (businessName.empty()) {
        msg("La razón social no puede estar vacía.");
        return;
    }

    suppliers_.push_back(std::make_unique<Supplier>(cuit, businessName));
    msg("Proveedor " + cuit.value() + " - " + businessName + " cargado.");
}

void App::listSuppliers() {
    // Ordenar por CUIT ascendente
    std::vector<Supplier*> sorted;
    for (auto& s : suppliers_) {
        sorted.push_back(s.get());
    }
    std::sort(sorted.begin(), sorted.end(),
              [](const Supplier* a, const Supplier* b) {
                  return a->cuit() < b->cuit();
              });

    msg("Proveedores registrados:");
    if (sorted.empty()) {
        msg("No hay proveedores registrados.");
        return;
    }
    for (auto* s : sorted) {
        out_ << s->cuit().value() << " - " << s->businessName() << "\n";
    }
}

void App::updateSupplier() {
    msg("CUIT del proveedor a modificar: ");
    Cuit cuit("00000000000");
    if (!readCuit(cuit)) {
        msg("El CUIT debe tener exactamente 11 dígitos numéricos.");
        return;
    }
    Supplier* s = findSupplier(cuit);
    if (s == nullptr) {
        msg("No existe un proveedor con el CUIT " + cuit.value() + ".");
        return;
    }

    msg("Razón social actual: " + s->businessName() +
        ". Nueva razón social (Enter para conservarla): ");
    std::string newName = trim(readLine());
    if (!newName.empty()) {
        s->businessName(newName);
    }
    msg("Proveedor " + cuit.value() + " - " + s->businessName() + " modificado.");
}

void App::removeSupplier() {
    msg("CUIT del proveedor a eliminar: ");
    Cuit cuit("00000000000");
    if (!readCuit(cuit)) {
        msg("El CUIT debe tener exactamente 11 dígitos numéricos.");
        return;
    }
    Supplier* s = findSupplier(cuit);
    if (s == nullptr) {
        msg("No existe un proveedor con el CUIT " + cuit.value() + ".");
        return;
    }

    // Contar pedidos asociados
    unsigned count = 0;
    for (auto& o : orders_) {
        if (o->supplier() == s) {
            ++count;
        }
    }
    if (count > 0) {
        msg("No se puede eliminar el proveedor " + cuit.value() +
            ": tiene " + std::to_string(count) + " pedido(s) asociado(s).");
        return;
    }

    suppliers_.erase(
        std::remove_if(suppliers_.begin(), suppliers_.end(),
                       [&](const std::unique_ptr<Supplier>& p) {
                           return p->cuit() == cuit;
                       }),
        suppliers_.end());
    msg("Proveedor " + cuit.value() + " - " + s->businessName() + " eliminado.");
}

void App::createOrder() {
    // 1. CUIT del proveedor
    msg("CUIT del proveedor del pedido: ");
    Cuit cuit("00000000000");
    if (!readCuit(cuit)) {
        msg("El CUIT debe tener exactamente 11 dígitos numéricos.");
        return;
    }
    Supplier* supplier = findSupplier(cuit);
    if (supplier == nullptr) {
        msg("No existe un proveedor con el CUIT " + cuit.value() + ".");
        return;
    }

    // 2. Fecha de entrega esperada
    msg("Fecha de entrega esperada (AAAA-MM-DD): ");
    Date delivery(1, 1, 1);  // placeholder; se sobrescribe si readDate tiene éxito
    if (!readDate(delivery)) {
        msg("Fecha inválida. Usá el formato AAAA-MM-DD.");
        return;
    }
    Date created = Date::today();
    if (delivery < created) {
        msg("La fecha de entrega no puede ser anterior a la fecha de creación (" +
            created.to_string() + ").");
        return;
    }

    // 3. Ítems
    std::vector<PurchaseOrder::Item> items;
    while (true) {
        msg("Código de artículo (Enter para terminar): ");
        std::string code = trim(readLine());
        if (code.empty()) {
            break;
        }
        Article* article = findArticle(code);
        if (article == nullptr) {
            msg("No existe un artículo con el código " + code + ".");
            continue;
        }
        // Verificar duplicado (BR-008)
        bool duplicado = false;
        for (const auto& item : items) {
            if (item.first == article) {
                duplicado = true;
                break;
            }
        }
        if (duplicado) {
            msg("El artículo " + code +
                " ya está en el pedido. Modificá la cantidad del ítem existente.");
            continue;
        }

        msg("Cantidad: ");
        unsigned qty = 0;
        if (!readUnsigned(qty)) {
            msg("Cantidad inválida. Ingresá un número entero mayor que cero, sin decimales.");
            continue;
        }
        if (qty == 0) {
            msg("La cantidad debe ser mayor que cero.");
            continue;
        }

        items.push_back({article, Quantity(qty)});
        msg("Ítem agregado: " + code + " - " + std::to_string(qty));
    }

    if (items.empty()) {
        msg("El pedido debe tener al menos un artículo.");
        return;
    }

    OrderNumber number(nextOrderNumber_++);
    orders_.push_back(std::make_unique<PurchaseOrder>(
        number, supplier, created, delivery, std::move(items)));
    msg("Pedido " + std::to_string(number.value()) +
        " creado para " + cuit.value() + " - " + supplier->businessName() + ".");
}

void App::doShowOrders() {
    // Agrupar por proveedor
    struct SupplierGroup {
        const Supplier* supplier;
        std::vector<PurchaseOrder*> orders;
    };
    std::vector<SupplierGroup> groups;
    for (auto& o : orders_) {
        bool found = false;
        for (auto& g : groups) {
            if (g.supplier == o->supplier()) {
                g.orders.push_back(o.get());
                found = true;
                break;
            }
        }
        if (!found) {
            groups.push_back(SupplierGroup{o->supplier(), {o.get()}});
        }
    }

    // Ordenar grupos por CUIT
    std::sort(groups.begin(), groups.end(),
              [](const SupplierGroup& a, const SupplierGroup& b) {
                  return a.supplier->cuit() < b.supplier->cuit();
              });

    // Ordenar pedidos dentro de cada grupo por número
    for (auto& g : groups) {
        std::sort(g.orders.begin(), g.orders.end(),
                  [](const PurchaseOrder* a, const PurchaseOrder* b) {
                      return a->number() < b->number();
                  });
    }

    bool hayPedidos = false;
    for (const auto& g : groups) {
        if (g.orders.empty()) {
            continue;
        }
        hayPedidos = true;
        out_ << "\n";
        msg("Proveedor: " + g.supplier->cuit().value() + " - " +
            g.supplier->businessName());
        for (const auto* po : g.orders) {
            out_ << "  Pedido " << po->number().value() << " - creado " <<
                    po->createdAt().to_string() << " - entrega " <<
                    po->expectedDelivery().to_string() << "\n";
            for (const auto& item : po->items()) {
                std::int64_t subtotalCents =
                    item.first->unitPrice().cents() *
                    static_cast<std::int64_t>(item.second.value());
                out_ << "    " << item.first->code() << " " <<
                        item.first->description() << ": " <<
                        item.second.value() << " x " <<
                        formatMoney(item.first->unitPrice().cents()) << " = " <<
                        formatMoney(subtotalCents) << "\n";
            }
            out_ << "  Total del pedido: " << formatMoney(po->total().cents()) << "\n";
        }
    }

    if (!hayPedidos) {
        msg("No hay pedidos registrados.");
    }
}

void App::showOrders() {
    doShowOrders();
}

}  // namespace partial02
