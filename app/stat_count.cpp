#include <atomic>
//#include <filesystem>
#include <string.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using namespace std::placeholders;
std::string kToken = ",";

template <typename CALLBACK>
void readAndParse(std::fstream& reader, CALLBACK callback) {
	char* save_ptr = nullptr;
	char* token_ptr = nullptr;
	while (reader.good() && !reader.eof()) {
		std::unique_ptr<char[]> line_ptr(new char[1024]);
		reader.getline(line_ptr.get(), 1024);
		if (reader.fail() || '\0' == line_ptr[0] || line_ptr[0] == '#') {
			continue;
		}
		token_ptr = strtok(line_ptr.get(), kToken.c_str());
		auto src = strtoul(token_ptr, nullptr, 10);

		int count = 0;
		token_ptr = strtok(NULL, kToken.c_str());
		count = strtoul(token_ptr, nullptr, 10);

		callback(src, count);
	}
}

int main(int argc, char const* argv[]) {
	std::atomic_long num{0};
	auto stat = [&](int src, int count) { num += count; };
	// for (const auto& f : std::filesystem::directory_iterator(argv[1])) {
	// 	std::cout << f.path() << std::endl;
	// 	std::fstream reader(f.path());
	// 	readAndParse(reader, stat);
	// }

	for (int i = 1; i < argc; i++) {
		std::cout << argv[i] << ", num:" << num << std::endl;
		std::fstream reader(argv[i]);
		readAndParse(reader, stat);
	}
	std::cout << "num:" << num << std::endl;

	return 0;
}
