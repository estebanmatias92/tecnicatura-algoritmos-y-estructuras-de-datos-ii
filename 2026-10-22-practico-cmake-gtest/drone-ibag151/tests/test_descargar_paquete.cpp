#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, UnloadPackageAdvancesDeliveryStage) {
    drone.unloadPackage();

    EXPECT_EQ(drone.deliveryStage(), DeliveryStage::PackageUnloaded);
    EXPECT_FALSE(drone.hasPackage());
}

TEST_F(DroneTest, UnloadPackageRequiresLanded) {
    drone.takeOff();

    EXPECT_THROW(drone.unloadPackage(), DroneError);
}

TEST_F(DroneTest, UnloadPackageTwiceIsRejected) {
    drone.unloadPackage();

    EXPECT_THROW(drone.unloadPackage(), DroneError);
}

}  // namespace ibag151::test
