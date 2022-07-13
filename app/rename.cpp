#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

int main() {
	std::string path = "/Users/haotong/reading/09_other/rename/";
	for (const auto& entry : fs::directory_iterator(path)) {
		auto path_ = entry.path().generic_string();
		auto pos = path_.find("E");
		auto name = path_.substr(pos);

		auto new_path_ = (path + name);
		std::cout << entry.path() << "  " << new_path_ << std::endl;

		rename(path_.c_str(), new_path_.c_str());
	}
}