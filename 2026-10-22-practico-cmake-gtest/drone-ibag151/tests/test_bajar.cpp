#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, DescendDecreasesAltitude) {
    drone.takeOff();
    drone.ascend(30);

    drone.descend(10);

    EXPECT_EQ(drone.altitude(), 20);
}

TEST_F(DroneTest, DescendCanReachGroundLevel) {
    drone.takeOff();
    drone.ascend(10);

    drone.descend(10);

    EXPECT_EQ(drone.altitude(), 0);
    EXPECT_EQ(drone.flightState(), FlightState::Flying);
}

TEST_F(DroneTest, DescendBelowGroundIsRejected) {
    drone.takeOff();
    drone.ascend(10);

    EXPECT_THROW(drone.descend(11), DroneError);
    EXPECT_EQ(drone.altitude(), 10);
}

TEST_F(DroneTest, DescendRequiresFlying) {
    EXPECT_THROW(drone.descend(10), DroneError);
}

TEST_F(DroneTest, DescendRejectsNonPositiveAmounts) {
    drone.takeOff();
    drone.ascend(10);

    EXPECT_THROW(drone.descend(0), DroneError);
    EXPECT_THROW(drone.descend(-5), DroneError);
}

}  // namespace ibag151::test
