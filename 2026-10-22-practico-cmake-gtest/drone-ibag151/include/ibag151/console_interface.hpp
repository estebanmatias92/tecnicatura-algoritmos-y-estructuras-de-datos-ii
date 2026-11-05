#ifndef IBAG151_CONSOLE_INTERFACE_HPP
#define IBAG151_CONSOLE_INTERFACE_HPP

#include <iosfwd>
#include <string>

#include "drone.hpp"

namespace ibag151 {

/// Console adapter: reads text commands and forwards them to the drone.
///
/// Streams and drone are injected, so the adapter can be tested without
/// touching the real standard input/output (DIP). Every command is echoed as
/// "sent to the drone" before it is executed.
class ConsoleInterface {
public:
    ConsoleInterface(std::istream& in, std::ostream& out, Drone& drone);

    /// Runs the command loop until "salir" or end of input.
    /// Returns the process exit code.
    int run();

private:
    /// Executes one raw input line. Returns false when the loop must stop.
    bool execute(const std::string& line);

    void printStatus();
    void printHelp();

    std::istream& in_;
    std::ostream& out_;
    Drone& drone_;
};

}  // namespace ibag151

#endif  // IBAG151_CONSOLE_INTERFACE_HPP
