#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, AccelerateIncreasesSpeed) {
    drone.takeOff();

    drone.accelerate(10);

    EXPECT_EQ(drone.speed(), 10);
}

TEST_F(DroneTest, AccelerateAccumulatesSpeed) {
    drone.takeOff();

    drone.accelerate(10);
    drone.accelerate(5);

    EXPECT_EQ(drone.speed(), 15);
}

TEST_F(DroneTest, AccelerateRequiresFlying) {
    EXPECT_THROW(drone.accelerate(10), DroneError);
}

TEST_F(DroneTest, AccelerateRejectsNonPositiveAmounts) {
    drone.takeOff();

    EXPECT_THROW(drone.accelerate(0), DroneError);
    EXPECT_THROW(drone.accelerate(-5), DroneError);
}

}  // namespace ibag151::test
