#include <folly/Conv.h>
#include <folly/GroupVarint.h>
#include <iostream>
#include <string>

using folly::GroupVarint32;

int main(int argc, char const* argv[]) {
	uint32_t a = 1111180;
	uint32_t b = 2380;
	uint32_t c = 830;
	uint32_t d = 1180;
	uint32_t e = 1180;
	uint32_t f = 1180;

	// encode
	size_t size = GroupVarint32::size(a, b, c, d);
	std::cout << "size=" << size << std::endl;

	std::vector<char> foundBytes;
	foundBytes.resize(std::max<size_t>(size + 4, 17UL));

	char* start = &(foundBytes.front());
	char* p = GroupVarint32::encode(start, a, b, c, d);

	// print byte
	for (auto e : foundBytes) {
		std::cout << folly::to<int>(e) << std::endl;
	}

	// decode
	uint32_t fa, fb, fc, fd;
	const char* r = GroupVarint32::decode(start, &fa, &fb, &fc, &fd);

	// compare
	std::cout << a << " " << fa << std::endl;
	std::cout << b << " " << fb << std::endl;
	std::cout << c << " " << fc << std::endl;
	std::cout << d << " " << fd << std::endl;

	return 0;
}

// link: -lfolly -lgflags -lglog -ldouble-conversion