#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <string>

TEST(StrMatch, all) {
	std::string response{"1234567"};
	std::string expected{"123"};
	using ::testing::HasSubstr;
	ASSERT_THAT(response, HasSubstr(expected));
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// link: -lgtest