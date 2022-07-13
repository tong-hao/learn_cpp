#include <gtest/gtest.h>
#include <string>

TEST(AssertTest, all) {
	ASSERT_TRUE(true);
	ASSERT_FALSE(false);

	int v = 5;
	ASSERT_EQ(v, 5);
	ASSERT_NE(v, 4);
	ASSERT_LT(v, 6);
	ASSERT_LE(v, 6);
	ASSERT_GT(v, 3);
	ASSERT_GE(v, 3);

	EXPECT_EQ(v, 5);
	EXPECT_NE(v, 4);
	EXPECT_LT(v, 6);
	EXPECT_LE(v, 6);
	EXPECT_GT(v, 3);
	EXPECT_GE(v, 3);

	std::string str{"abc"};
	ASSERT_STREQ(str.data(), "abc");
	ASSERT_STRNE(str.data(), "123");
	ASSERT_STRCASEEQ(str.data(), "ABc");
	ASSERT_STRCASENE(str.data(), "ab1");

	// FAIL();
	// ADD_FAILURE();
	SUCCEED() << "test pass1";
	// FAIL() << "fail....";

	auto throw1 = []() { throw std::logic_error("error"); };
	ASSERT_THROW(throw1(), std::logic_error);
	ASSERT_NO_THROW(2 / 1);
	ASSERT_ANY_THROW(throw1());

	int m = 5, n = 5;
	auto eq = [](int i1, int i2) { return i1 == i2; };
	EXPECT_PRED2(eq, m, n);

	ASSERT_FLOAT_EQ(3.1415926, 3.141592);
	ASSERT_DOUBLE_EQ(3.1415926, 3.1415926);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}