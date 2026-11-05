#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, StartsLanded) {
    EXPECT_EQ(drone.flightState(), FlightState::Landed);
}

TEST_F(DroneTest, StartsAtGroundLevel) {
    EXPECT_EQ(drone.altitude(), 0);
}

TEST_F(DroneTest, StartsStopped) {
    EXPECT_EQ(drone.speed(), 0);
}

TEST_F(DroneTest, StartsFacingNorth) {
    EXPECT_EQ(drone.heading(), 0);
}

TEST_F(DroneTest, StartsWithPackageAndPendingDelivery) {
    EXPECT_TRUE(drone.hasPackage());
    EXPECT_EQ(drone.deliveryStage(), DeliveryStage::WithPackage);
}

}  // namespace ibag151::test
