#include <string.h>
#include <array>
#include <cstdlib>
#include <iostream>

inline std::array<char, 8> to_array(std::string str_id) {
	std::array<char, 8> ret{0};
	int idx = 0;
	for (char c : str_id) {
		ret[idx++] = c;
	}
	return ret;
}

union smart_array {
	char *point_;
	std::array<char, 8> array_;
};

class string_lite {
public:
	explicit string_lite() : len_(0), data_{.array_ = {0}} {
	}

	explicit string_lite(const std::string &str) {
		len_ = str.size();
		if (len_ > 8) {
			data_.point_ = new char[len_ + 1];
			data_.point_[len_] = '\0';
			memcpy(data_.point_, str.c_str(), len_);
		} else {
			data_.array_ = to_array(str);
		}
	}

	explicit string_lite(const char *str) {
		if (str) {
			len_ = strlen(str);
			if (len_ > 8) {
				data_.point_ = new char[len_ + 1];
				data_.point_[len_] = '\0';
				memcpy(data_.point_, str, len_);
			} else {
				data_.array_ = to_array(str);
			}
		} else {
			len_ = 0;
			data_.array_ = {0};
		}
	}

private:
	uint8_t len_;
	smart_array data_;
};

int main() {
	for (int i = 0; i < 100; i++) {
		string_lite s("abc");
	}

	return 0;
}
