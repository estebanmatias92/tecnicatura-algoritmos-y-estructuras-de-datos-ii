#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, TurnLeftFromNorthFacesWest) {
    drone.takeOff();

    drone.turnLeft();

    EXPECT_EQ(drone.heading(), 270);
}

TEST_F(DroneTest, TurnLeftAccumulates) {
    drone.takeOff();

    drone.turnLeft();
    drone.turnLeft();

    EXPECT_EQ(drone.heading(), 180);
}

TEST_F(DroneTest, TurnLeftWrapsAround) {
    drone.takeOff();

    drone.turnLeft();
    drone.turnLeft();
    drone.turnLeft();

    EXPECT_EQ(drone.heading(), 90);
}

TEST_F(DroneTest, TurnLeftRequiresFlying) {
    EXPECT_THROW(drone.turnLeft(), DroneError);
}

}  // namespace ibag151::test
