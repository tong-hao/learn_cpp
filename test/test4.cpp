#include <string.h>
#include <iomanip>
#include <iostream>
#include <tuple>

class string_lite {
public:
	string_lite() : data_(nullptr) {
	}

	explicit string_lite(const std::string &str) {
		size_t len = str.size();
		data_ = new char[len + 1];
		data_[len] = '\0';
		memcpy(data_, str.c_str(), len);
	}

	explicit string_lite(const char *str) {
		if (str) {
			size_t len = strlen(str);
			data_ = new char[len + 1];
			data_[len] = '\0';
			memcpy(data_, str, len);
		} else {
			data_ = nullptr;
		}
	}

	string_lite(const string_lite &other) {
		if (other.data_) {
			size_t len = strlen(other.data_);
			data_ = new char[len + 1];
			data_[len] = '\0';
			memcpy(data_, other.data_, len);
		} else {
			data_ = nullptr;
		}
	}

	string_lite(string_lite &&other) : data_(other.data_) {
		other.data_ = nullptr;
	}

	string_lite &operator=(const string_lite &other) {
		if (this != &other) {
			if (data_) {
				delete[] data_;
				data_ = nullptr;
			}
			if (other.data_) {
				size_t len = strlen(other.data_);
				data_ = new char[len + 1];
				data_[len] = '\0';
				memcpy(data_, other.data_, len);
			}
		}
		return *this;
	}

	string_lite &operator=(string_lite &&other) {
		if (this != &other) {
			if (data_) {
				delete[] data_;
				data_ = nullptr;
			}
			data_ = other.data_;
			other.data_ = nullptr;
		}
		return *this;
	}

	bool operator==(const string_lite &other) const {
		if (data_ == nullptr && other.data_ == nullptr) {
			return true;
		} else if (data_ == nullptr || other.data_ == nullptr) {
			return false;
		}

		return strcmp(data_, other.data_) == 0;
	}

	bool operator<(const string_lite &other) const {
		if (data_ == nullptr || other.data_ == nullptr) {
			return false;
		}

		return strcmp(data_, other.c_str()) < 0;
	}

	bool operator>(const string_lite &other) const {
		if (data_ == nullptr || other.data_ == nullptr) {
			return false;
		}

		return strcmp(data_, other.c_str()) > 0;
	}

	size_t size() const {
		if (data_) {
			return strlen(data_);
		} else {
			return 0;
		}
	}

	const char *c_str() const {
		return data_;
	}

	~string_lite() {
		if (data_) {
			delete[] data_;
			data_ = nullptr;
		}
	}

	std::string to_string() const {
		if (!data_) {
			return "";
		}
		return std::string(data_);
	}

private:
	char *data_;
};

std::tuple<string_lite, string_lite> test() {
	string_lite a;
	string_lite b;
	return std::make_tuple(a, b);
}

int main() {
	float f = 15;
	float ret = f / 16;
	std::cout << ret << std::endl;

	return 0;
}
