#include <iostream>
#include <string>
#include <iomanip>

void Write(std::string& ret, int32_t i) {
	char* p = reinterpret_cast<char*>(&i);
	ret.append(p, sizeof(int32_t));
}

int32_t ReadInt32(std::string& encoding_str) {
	const int32_t* i = reinterpret_cast<const int32_t*>(encoding_str.data());
	int32_t ret = *i;
	encoding_str.erase(0, sizeof(int32_t));
	return ret;
}


int main1(int argc, char const *argv[])
{
	int32_t num = 100 + (101 << 16) + (102 << 24) ; //+ (103<<24);
	std::cout << "num:" << (num) << std::endl;

	std::string str;
	char* p = reinterpret_cast<char*>(&num);
	char* p2 = p;
	str.append(p, sizeof(int32_t));
	int i = 0;

	const char*p3 = str.data();
	/*while (i < 4) {
		std::cout << *p3 << std::endl;
		p3++;
		i++;
	}*/


	const int32_t* i1 = reinterpret_cast<const int32_t*>(p3);
	std::cout << std::setprecision(3) << (*i1) << std::endl;


	return 0;
}

int main(int argc, char const *argv[]) {

	std::string ret;
	int32_t i11 = 100;
	Write(ret, i11);

	int32_t i12= 105;
	Write(ret, i12);

	int32_t i13 = 108;
	Write(ret, i13);



	int32_t i21 = ReadInt32(ret);
	std::cout << i21 << std::endl;

	int32_t i22 = ReadInt32(ret);
	std::cout << i22 << std::endl;

	int32_t i23 = ReadInt32(ret);
	std::cout << i23 << std::endl;


	std::string s = "abc";
	std::cout << "str.length:" << s.length() << std::endl;

}
