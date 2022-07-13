#include <iostream>
#include <string>

inline int to_vid_t(const int& vid) {
	return vid;
}

inline int to_vid_t(const std::string& vid) {
	return std::stoi(vid);
}

int main(int argc, char const* argv[]) {
	std::string s = "123";
	auto r1 = to_vid_t(s);
	std::cout << r1 << std::endl;

	uint i = 100;
	auto r2 = to_vid_t(i);
	std::cout << r2 << std::endl;

	return 0;
}
