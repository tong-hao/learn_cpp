#include <stdint.h>

int main(int argc, char const *argv[])
{
	bool b = true;
	char c = 'a';
	//byte bt = 1; error
	wchar_t wc = 'a';
	char16_t c2= 'a';
	char32_t c3= 'b';

	short st = 1;
	int i = 1;
	long l = 1;
	long long ll = 1;


	float f = 3.14;
	double d = 3.14;
	long double ld = 3.14;

	//-------

	int8_t i1 = 1;
	int16_t i2;
	int32_t i3;
	int64_t i4;

	//---------

	{
		bool b = 1;
		bool b2 = 'c';
		int i = true;
		int i2 = 3.14; //warning
		int i3 = 'c';


	}

	//
	{
		int i1 = 0123; // 八进制
		int i2 = 0x123; // 16进制
		int i3 = 123; // 十进制
	}

	
	return 0;
}