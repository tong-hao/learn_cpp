#include <iostream>

int main(int argc, char const *argv[])
{
	int i = 0;
	int *p_i = &i;

	int i2 = 2;
	p_i = &i2;
	std::cout << "i=" << i << ", p_i=" << *p_i << std::endl;

	*p_i = 3;
	std::cout << "i=" << i << ", i2=" << i2 << ", p_i=" << *p_i << std::endl;


	// void * 可以指向任意类型
	{
		int i = 0;
		double d = 3.14;
		void *p = &i;
		p = &d;

	}

	// 指针的指针
	{
		int i = 0;
		int *p_i = &i;
		int **pp_i = &p_i;
	}

	// 指针的饮用
	{
		int i = 42;
		int *p = &i;
		int *&rp = p; // 引用
	}

	
	return 0;
}