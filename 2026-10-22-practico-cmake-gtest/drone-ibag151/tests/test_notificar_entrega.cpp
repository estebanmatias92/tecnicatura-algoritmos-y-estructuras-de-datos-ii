#include "support/drone_fixture.hpp"

namespace ibag151::test {

namespace {

void completeDelivery(DroneIbag151& drone) {
    drone.unloadPackage();
    drone.takeReceptionPhoto();
}

}  // namespace

TEST_F(DroneTest, NotifyDeliveryAfterPhotoAdvancesStage) {
    completeDelivery(drone);

    drone.notifyDelivery();

    EXPECT_EQ(drone.deliveryStage(), DeliveryStage::DeliveryNotified);
}

TEST_F(DroneTest, NotifyDeliveryRequiresPhoto) {
    drone.unloadPackage();

    EXPECT_THROW(drone.notifyDelivery(), DroneError);
}

TEST_F(DroneTest, NotifyDeliveryRequiresUnloadedPackage) {
    EXPECT_THROW(drone.notifyDelivery(), DroneError);
}

TEST_F(DroneTest, NotifyDeliveryRequiresLanded) {
    completeDelivery(drone);
    drone.takeOff();

    EXPECT_THROW(drone.notifyDelivery(), DroneError);
}

TEST_F(DroneTest, NotifyDeliveryTwiceIsRejected) {
    completeDelivery(drone);
    drone.notifyDelivery();

    EXPECT_THROW(drone.notifyDelivery(), DroneError);
}

}  // namespace ibag151::test
