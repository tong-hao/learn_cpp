#include <gtest/gtest.h>

class Foo {
public:
	Foo() = default;
	~Foo() = default;

	FRIEND_TEST(FooTest, friend_test);

private:
	bool isRunning() {
		return running_;
	}

private:
	bool running_{true};
};

class FooTest : public testing::Test {};

TEST(FooTest, friend_test) {
	Foo f;
	ASSERT_TRUE(f.isRunning());
	ASSERT_TRUE(f.running_);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}