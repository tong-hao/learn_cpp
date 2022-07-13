

int main() {
	int i = 0; // copy
	int i2 = {1};

	int i3{0}; // init
	int i4{1};


	// 
	{
		extern int i; // 只声明 未定义
		int j; // 声明 + 定义
		extern double d = 3.14; // 定义
	}
	// 1. 声明是为了支持分离式编译
	// 2. 可以声明多次，只能定义一次

	


}