#include "boost/algorithm/string.hpp"
#include "boost/filesystem.hpp"
#include "boost/iostreams/device/file.hpp"

#include <iostream>

void touch_dir(const std::string &path) {
	boost::filesystem::path full_path;
	if (path[0] == '~') {
		// prepend the user's home directory if the path starts with `~`
		full_path = boost::filesystem::path("~") / path;
	} else {
		full_path = boost::filesystem::path(path);
	}

	std::cout << full_path.c_str();
}

int main(int argc, char const *argv[]) {
	touch_dir("~/a/b/c");
	return 0;
}
