#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, LandChangesStateToLanded) {
    drone.takeOff();

    drone.land();

    EXPECT_EQ(drone.flightState(), FlightState::Landed);
}

TEST_F(DroneTest, LandRequiresFlying) {
    EXPECT_THROW(drone.land(), DroneError);
}

TEST_F(DroneTest, LandTwiceIsRejected) {
    drone.takeOff();
    drone.land();

    EXPECT_THROW(drone.land(), DroneError);
}

}  // namespace ibag151::test
