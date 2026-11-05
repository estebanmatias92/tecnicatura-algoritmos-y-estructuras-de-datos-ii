#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, TakeOffChangesStateToFlying) {
    drone.takeOff();

    EXPECT_EQ(drone.flightState(), FlightState::Flying);
}

TEST_F(DroneTest, TakeOffTwiceIsRejected) {
    drone.takeOff();

    EXPECT_THROW(drone.takeOff(), DroneError);
}

}  // namespace ibag151::test
