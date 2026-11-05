#include "support/drone_fixture.hpp"

namespace ibag151::test {

TEST_F(DroneTest, TakePhotoAfterUnloadingAdvancesStage) {
    drone.unloadPackage();

    drone.takeReceptionPhoto();

    EXPECT_EQ(drone.deliveryStage(), DeliveryStage::ReceptionPhotographed);
}

TEST_F(DroneTest, TakePhotoRequiresUnloadedPackage) {
    EXPECT_THROW(drone.takeReceptionPhoto(), DroneError);
}

TEST_F(DroneTest, TakePhotoRequiresLanded) {
    drone.unloadPackage();
    drone.takeOff();

    EXPECT_THROW(drone.takeReceptionPhoto(), DroneError);
}

TEST_F(DroneTest, TakePhotoTwiceIsRejected) {
    drone.unloadPackage();
    drone.takeReceptionPhoto();

    EXPECT_THROW(drone.takeReceptionPhoto(), DroneError);
}

}  // namespace ibag151::test
