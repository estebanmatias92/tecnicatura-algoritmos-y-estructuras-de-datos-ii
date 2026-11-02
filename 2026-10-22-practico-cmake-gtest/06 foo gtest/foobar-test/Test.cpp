#include "../ext/googletest/googletest/include/gtest/gtest.h"
#include "../libfoobar/example.h"



	TEST(ExampleTests, Example) {
		Example example;
		int valor ;
		valor =  example.getValue();
        EXPECT_EQ(99,valor);
		
	}

