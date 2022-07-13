

int main(int argc, char const *argv[])
{

	// 值捕获
	auto print1 = [=](){};

	// 引用捕获
	auto print2 = [&](){};

	auto print3 = [&]() mutable {};
	
	return 0;
}