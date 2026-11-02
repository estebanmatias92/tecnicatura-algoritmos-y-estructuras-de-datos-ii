#include "../ext/googletest/googletest/include/gtest/gtest.h"
#include "../library/Myfunctions.h"
#include "../library/Car.h"

//Test Function
TEST(Suma, Prueba)
{
    EXPECT_EQ(10,sum(5,5));
    EXPECT_EQ(50,sum(20,30));
}

TEST(Suma, PruebaCero)
{
    EXPECT_EQ(14,sum(10,4));
    
}

TEST(Resta, Prueba)
{
    EXPECT_EQ(10,substract(15,5));
    
}


// Test Car Object


TEST(Car, Acelerate)
{
    Car *myCarTest3 = new Car() ; ;
    myCarTest3->accelerate(10);
    std::cout << "***" <<  myCarTest3->getSpeed() << "***" << std::endl ;
    EXPECT_EQ(20,myCarTest3->getSpeed());
    
}

TEST(Car, Brakes)
{
   Car *myCarTest2 = new Car() ;
   
   //int velocidad = myCarTest2->getSpeed();
   
    EXPECT_EQ(0,myCarTest2->brake(10));
    
}
