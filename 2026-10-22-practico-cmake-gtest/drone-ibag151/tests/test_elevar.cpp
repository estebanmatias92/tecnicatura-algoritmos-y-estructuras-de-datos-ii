#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, AscendIncreasesAltitude) {
    drone.takeOff();

    drone.ascend(10);

    EXPECT_EQ(drone.altitude(), 10);
}

TEST_F(DroneTest, AscendAccumulatesAltitude) {
    drone.takeOff();

    drone.ascend(10);
    drone.ascend(5);

    EXPECT_EQ(drone.altitude(), 15);
}

TEST_F(DroneTest, AscendRequiresFlying) {
    EXPECT_THROW(drone.ascend(10), DroneError);
}

TEST_F(DroneTest, AscendRejectsNonPositiveAmounts) {
    drone.takeOff();

    EXPECT_THROW(drone.ascend(0), DroneError);
    EXPECT_THROW(drone.ascend(-5), DroneError);
}

}  // namespace ibag151::test
