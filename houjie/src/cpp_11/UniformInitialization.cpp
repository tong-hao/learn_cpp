#include <vector>

int main(int argc, char const *argv[]) {
	// 1. uniform initialization用法
	int values[]{1, 2, 3};
	std::vector<int> v{1, 2, 4};
	// complex<double> c{4.0, 5.0};

	//背后是如果构造器里有initializer
	// list参数，则编译器后将大括弧里的打包，如果构造器没有initializer
	// list参数，则编译器会一个一个参数调用。

	// 2. 注意
	int i;     // 未知
	int i{};   // 0
	int *p{};  // nullptr
	int *q;    // 未知

	return 0;
}
