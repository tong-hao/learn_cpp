#include <gtest/gtest.h>

class FooEnvironment : public testing::Environment {
public:
	virtual void SetUp() {
		std::cout << "Foo FooEnvironment SetUP" << std::endl;
	}
	virtual void TearDown() {
		std::cout << "Foo FooEnvironment TearDown" << std::endl;
	}
};

TEST(Test, test1) {
	ASSERT_TRUE(true);
}

TEST(Test, test2) {
	ASSERT_TRUE(true);
}

int main(int argc, char *argv[]) {
	testing::AddGlobalTestEnvironment(new FooEnvironment);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}