#include "ibag151/console_interface.hpp"

#include <exception>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace ibag151 {

namespace {

std::string trim(const std::string& text) {
    const std::string whitespace = " \t\r\n";
    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }

    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

const char* flightStateName(FlightState state) {
    return state == FlightState::Flying ? "en vuelo" : "en tierra";
}

std::string deliveryStageName(DeliveryStage stage) {
    switch (stage) {
        case DeliveryStage::WithPackage:
            return "con paquete";
        case DeliveryStage::PackageUnloaded:
            return "paquete descargado";
        case DeliveryStage::ReceptionPhotographed:
            return "foto tomada";
        case DeliveryStage::DeliveryNotified:
            return "notificada";
    }

    return "desconocida";
}

/// Reads an optional integer argument; defaults to one when absent.
int optionalAmount(std::istringstream& tokens) {
    std::string token;
    if (!(tokens >> token)) {
        return 1;
    }

    std::size_t processed = 0;
    int amount = 0;
    try {
        amount = std::stoi(token, &processed);
    } catch (const std::exception&) {
        throw DroneError("cantidad invalida: " + token);
    }

    if (processed != token.size()) {
        throw DroneError("cantidad invalida: " + token);
    }

    return amount;
}

}  // namespace

ConsoleInterface::ConsoleInterface(std::istream& in, std::ostream& out, Drone& drone)
    : in_(in), out_(out), drone_(drone) {}

int ConsoleInterface::run() {
    std::string line;
    while (std::getline(in_, line)) {
        if (!execute(line)) {
            break;
        }
    }

    return 0;
}

bool ConsoleInterface::execute(const std::string& raw_line) {
    const std::string line = trim(raw_line);
    if (line.empty()) {
        return true;
    }

    out_ << "> " << line << '\n';

    std::istringstream tokens(line);
    std::string command;
    tokens >> command;

    try {
        if (command == "salir") {
            out_ << "Hasta luego.\n";
            return false;
        }

        if (command == "despegar") {
            drone_.takeOff();
        } else if (command == "aterrizar") {
            drone_.land();
        } else if (command == "elevar") {
            drone_.ascend(optionalAmount(tokens));
        } else if (command == "bajar") {
            drone_.descend(optionalAmount(tokens));
        } else if (command == "acelerar") {
            drone_.accelerate(optionalAmount(tokens));
        } else if (command == "frenar") {
            drone_.brake(optionalAmount(tokens));
        } else if (command == "girar") {
            std::string direction;
            tokens >> direction;
            if (direction == "derecha") {
                drone_.turnRight();
            } else if (direction == "izquierda") {
                drone_.turnLeft();
            } else {
                out_ << "ERROR: uso: girar derecha | girar izquierda\n";
                return true;
            }
        } else if (command == "descargar") {
            std::string target;
            tokens >> target;
            if (target != "paquete") {
                out_ << "ERROR: uso: descargar paquete\n";
                return true;
            }
            drone_.unloadPackage();
        } else if (command == "sacar") {
            std::string target;
            tokens >> target;
            if (target != "foto") {
                out_ << "ERROR: uso: sacar foto\n";
                return true;
            }
            drone_.takeReceptionPhoto();
        } else if (command == "notificar") {
            std::string target;
            tokens >> target;
            if (target != "entrega") {
                out_ << "ERROR: uso: notificar entrega\n";
                return true;
            }
            drone_.notifyDelivery();
        } else if (command == "estado") {
            printStatus();
            return true;
        } else if (command == "ayuda") {
            printHelp();
            return true;
        } else {
            out_ << "ERROR: comando desconocido: " << command << '\n';
            return true;
        }

        out_ << "OK: " << line << '\n';
    } catch (const DroneError& error) {
        out_ << "ERROR: " << error.what() << '\n';
    }

    return true;
}

void ConsoleInterface::printStatus() {
    out_ << "Estado: " << flightStateName(drone_.flightState()) << '\n';
    out_ << "Altitud: " << drone_.altitude() << " m\n";
    out_ << "Velocidad: " << drone_.speed() << " u\n";
    out_ << "Rumbo: " << drone_.heading() << " grados\n";
    out_ << "Paquete a bordo: " << (drone_.hasPackage() ? "si" : "no") << '\n';
    out_ << "Entrega: " << deliveryStageName(drone_.deliveryStage()) << '\n';
}

void ConsoleInterface::printHelp() {
    out_ << "Comandos:\n"
         << "  despegar\n"
         << "  aterrizar\n"
         << "  elevar [metros]\n"
         << "  bajar [metros]\n"
         << "  girar derecha | girar izquierda\n"
         << "  acelerar [unidades]\n"
         << "  frenar [unidades]\n"
         << "  descargar paquete\n"
         << "  sacar foto\n"
         << "  notificar entrega\n"
         << "  estado\n"
         << "  ayuda\n"
         << "  salir\n";
}

}  // namespace ibag151
