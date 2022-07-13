#include <fstream>
#include <iostream>

class FileUtil
{
public:
	FileUtil() = default;
	~FileUtil() = default;

	static bool Exist(const std::string& name);


};

bool FileUtil::Exist(const std::string& name) {
	std::ifstream ifs(name, std::ifstream::in);
	bool exist = ifs.good();
	std::cout << exist << std::endl;
	ifs.close();
	return exist;
}

int main(int argc, char const *argv[])
{

	FileUtil::Exist("1.txt");

	return 0;
}