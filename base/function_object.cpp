#include <iostream>


class MyDivide
{
public:
	MyDivide() = default;
	~MyDivide() = default;

	MyDivide(double y):y_(y){}

	double operator()(double x){
		return x/y_;
	}

	double operator()(double x, double y){
		return x/y;
	}

private:
	double y_ = 1;
	
};


int main(int argc, char const *argv[])
{
	MyDivide d;

	std::cout << d(10, 5) << std::endl;

	std::cout << d(10) << std::endl;

	
	return 0;
}