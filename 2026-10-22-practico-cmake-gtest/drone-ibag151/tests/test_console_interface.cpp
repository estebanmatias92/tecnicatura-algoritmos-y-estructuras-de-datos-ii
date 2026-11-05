#include <sstream>
#include <string>

#include "ibag151/console_interface.hpp"
#include "support/drone_fixture.hpp"

namespace ibag151::test {

namespace {

::testing::AssertionResult Contains(const std::string& text, const std::string& needle) {
    if (text.find(needle) != std::string::npos) {
        return ::testing::AssertionSuccess();
    }

    return ::testing::AssertionFailure() << "'" << needle << "' not found in:\n" << text;
}

class ConsoleTest : public ::testing::Test {
protected:
    std::string run(const std::string& input) {
        std::istringstream in(input);
        std::ostringstream out;
        ConsoleInterface console(in, out, drone);
        console.run();
        return out.str();
    }

    DroneIbag151 drone;
};

}  // namespace

TEST_F(ConsoleTest, TakeOffCommandIsForwardedToTheDrone) {
    const std::string output = run("despegar\n");

    EXPECT_TRUE(Contains(output, "> despegar"));
    EXPECT_EQ(drone.flightState(), FlightState::Flying);
}

TEST_F(ConsoleTest, AscendUsesExplicitAmount) {
    run("despegar\nelevar 25\n");

    EXPECT_EQ(drone.altitude(), 25);
}

TEST_F(ConsoleTest, AscendDefaultsToOneMeter) {
    run("despegar\nelevar\n");

    EXPECT_EQ(drone.altitude(), 1);
}

TEST_F(ConsoleTest, InvalidAmountIsReported) {
    const std::string output = run("despegar\nelevar abc\n");

    EXPECT_TRUE(Contains(output, "ERROR"));
    EXPECT_EQ(drone.altitude(), 0);
}

TEST_F(ConsoleTest, DroneErrorsArePrintedWithoutStoppingTheLoop) {
    const std::string output = run("elevar 10\ndespegar\n");

    EXPECT_TRUE(Contains(output, "ERROR"));
    EXPECT_EQ(drone.flightState(), FlightState::Flying);
}

TEST_F(ConsoleTest, UnknownCommandKeepsTheLoopRunning) {
    const std::string output = run("foo\nestado\n");

    EXPECT_TRUE(Contains(output, "comando desconocido"));
    EXPECT_TRUE(Contains(output, "Estado:"));
}

TEST_F(ConsoleTest, StatusReportsFlightData) {
    const std::string output = run("despegar\nelevar 10\nestado\n");

    EXPECT_TRUE(Contains(output, "Altitud: 10"));
    EXPECT_TRUE(Contains(output, "Estado: en vuelo"));
}

TEST_F(ConsoleTest, SalirStopsProcessing) {
    const std::string output = run("salir\ndespegar\n");

    EXPECT_TRUE(Contains(output, "Hasta luego"));
    EXPECT_EQ(drone.flightState(), FlightState::Landed);
}

TEST_F(ConsoleTest, FullDeliveryWorkflowCompletes) {
    const std::string output = run(
        "despegar\n"
        "elevar 20\n"
        "girar derecha\n"
        "bajar 20\n"
        "aterrizar\n"
        "descargar paquete\n"
        "sacar foto\n"
        "notificar entrega\n"
        "estado\n");

    EXPECT_TRUE(Contains(output, "Entrega: notificada"));
    EXPECT_EQ(drone.deliveryStage(), DeliveryStage::DeliveryNotified);
}

}  // namespace ibag151::test
