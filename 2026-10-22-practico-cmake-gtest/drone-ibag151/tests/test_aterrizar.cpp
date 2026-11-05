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

TEST_F(DroneTest, LandResetsAltitudeAndSpeed) {
    drone.takeOff();
    drone.ascend(40);
    drone.accelerate(20);

    drone.land();

    EXPECT_EQ(drone.altitude(), 0);
    EXPECT_EQ(drone.speed(), 0);
}

}  // namespace ibag151::test
