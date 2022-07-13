#include <gtest/gtest.h>
#include <string>

class FooTest : public testing::Test {
protected:
	static void SetUpTestCase() {
		shared_resource_ = "hello test";
	}
	static void TearDownTestCase() {
		shared_resource_.clear();
	}
	static std::string shared_resource_;
};
std::string FooTest::shared_resource_;

TEST_F(FooTest, Test1) {
	// you can refer to shared_resource here
	ASSERT_TRUE(shared_resource_.size() > 0);
}
TEST_F(FooTest, Test2) {
	// you can refer to shared_resource here
	ASSERT_FALSE(shared_resource_.empty());
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}