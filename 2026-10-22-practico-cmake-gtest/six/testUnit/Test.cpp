#include "../ext/googletest/googletest/include/gtest/gtest.h"
#include "../librerias/Myfunctions.h"

TEST(Suma, Prueba)
{
    EXPECT_EQ(10,sum(5,5));
    EXPECT_EQ(50,sum(20,30));
}

TEST(Suma, PruebaCero)
{
    EXPECT_EQ(12,sum(10,2));
    
}

TEST(Resta, Prueba)
{
    EXPECT_EQ(10,substract(15,5));
    
}

