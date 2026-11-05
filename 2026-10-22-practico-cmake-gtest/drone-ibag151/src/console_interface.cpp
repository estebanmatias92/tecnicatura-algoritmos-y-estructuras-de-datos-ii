#include "ibag151/console_interface.hpp"

namespace ibag151 {

ConsoleInterface::ConsoleInterface(std::istream& in, std::ostream& out, Drone& drone)
    : in_(in), out_(out), drone_(drone) {}

int ConsoleInterface::run() {
    // Implementation added in the green step of the TDD cycle.
    return 0;
}

bool ConsoleInterface::execute(const std::string&) {
    // Implementation added in the green step of the TDD cycle.
    return true;
}

}  // namespace ibag151
