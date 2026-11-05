#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, TurnRightFromNorthFacesEast) {
    drone.takeOff();

    drone.turnRight();

    EXPECT_EQ(drone.heading(), 90);
}

TEST_F(DroneTest, TurnRightAccumulates) {
    drone.takeOff();

    drone.turnRight();
    drone.turnRight();

    EXPECT_EQ(drone.heading(), 180);
}

TEST_F(DroneTest, TurnRightWrapsAround) {
    drone.takeOff();

    drone.turnRight();
    drone.turnRight();
    drone.turnRight();
    drone.turnRight();

    EXPECT_EQ(drone.heading(), 0);
}

TEST_F(DroneTest, TurnRightRequiresFlying) {
    EXPECT_THROW(drone.turnRight(), DroneError);
}

}  // namespace ibag151::test
