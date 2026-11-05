#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, BrakeDecreasesSpeed) {
    drone.takeOff();
    drone.accelerate(30);

    drone.brake(10);

    EXPECT_EQ(drone.speed(), 20);
}

TEST_F(DroneTest, BrakeNeverGoesBelowZero) {
    drone.takeOff();
    drone.accelerate(10);

    drone.brake(50);

    EXPECT_EQ(drone.speed(), 0);
}

TEST_F(DroneTest, BrakeRequiresFlying) {
    EXPECT_THROW(drone.brake(10), DroneError);
}

TEST_F(DroneTest, BrakeRejectsNonPositiveAmounts) {
    drone.takeOff();
    drone.accelerate(10);

    EXPECT_THROW(drone.brake(0), DroneError);
    EXPECT_THROW(drone.brake(-5), DroneError);
}

}  // namespace ibag151::test
