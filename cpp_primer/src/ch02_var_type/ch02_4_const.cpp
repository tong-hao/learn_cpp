#include <iostream>

int main(int argc, char const *argv[])
{
	const int i = 0;

	// const reference
	{
		int i = 0;
		const int &r_i = i; // => const int tmp = i; const int &r_i = tmp;

	}

	// const & point
	{
		
		const int ci = 10; //底层const
		const int *p2 = &ci; // p2->const int //底层const
		
		int i = 0;
		int *const p1 = &i; // 不能改变p1的值 //顶层const
 
		const int *const p3 = &ci; // 底层const + 顶层const
	}

	// 常量表达式
	{
		constexpr int i = 0; // 字面值
		constexpr int c = i + 1; // 表达式


		const int *p = nullptr; // p指向一个常量
		constexpr int *q = nullptr; // q是一个常量指针
	}


	
	return 0;
}