#include <gtest/gtest.h>
#include <string>

class FooTest : public testing::Test {
protected:
	void SetUp() {
		shared_resource_ = "hello test";
		std::cout << "SetUp()..." << std::endl;
	}
	void TearDown() {
		shared_resource_.clear();
	}
	std::string shared_resource_;
};

TEST_F(FooTest, Test1) {
	shared_resource_ = "123";
	ASSERT_EQ(shared_resource_, "123");
}
TEST_F(FooTest, Test2) {
	ASSERT_EQ(shared_resource_, "hello test");
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}