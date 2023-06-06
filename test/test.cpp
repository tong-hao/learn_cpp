#include <array>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

struct mem_status_t {
	size_t vm_peak;  // KBytes
	size_t vm_size;  // KBytes
	size_t vm_hwm;   // KBytes
	size_t vm_rss;   // KBytes
};

inline void self_mem_usage(mem_status_t *status) {
	char buffer[1024] = "";

	FILE *file = fopen("/proc/self/status", "r");
	while (fscanf(file, " %1023s", buffer) == 1) {
		if (strcmp(buffer, "VmRSS:") == 0) {
			fscanf(file, " %lu", &status->vm_rss);
		}
		if (strcmp(buffer, "VmHWM:") == 0) {
			fscanf(file, " %lu", &status->vm_hwm);
		}
		if (strcmp(buffer, "VmSize:") == 0) {
			fscanf(file, " %lu", &status->vm_size);
		}
		if (strcmp(buffer, "VmPeak:") == 0) {
			fscanf(file, " %lu", &status->vm_peak);
		}
	}
	fclose(file);
}

class string_lite {
public:
	explicit string_lite() : data_(nullptr) {
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

	string_lite(string_lite &&other) noexcept : data_(other.data_) {
		other.data_ = nullptr;
	}

	string_lite &operator=(const string_lite &other) {
		if (this != &other) {
			string_lite temp(other);
			std::swap(data_, temp.data_);
		}
		return *this;
	}

	string_lite &operator=(string_lite &&other) noexcept {
		if (this != &other) {
			delete[] data_;
			data_ = other.data_;
			other.data_ = nullptr;
		}
		return *this;
	}

	bool operator==(const string_lite &other) const {
		if (data_ == nullptr || other.data_ == nullptr) {
			return false;
		}
		return strcmp(data_, other.data_) == 0;
	}

	bool operator<(const string_lite &other) const {
		if (data_ == nullptr || other.data_ == nullptr) {
			return false;
		}
		return strcmp(data_, other.data_) < 0;
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

// ==========

inline std::array<char, 8> to_array(std::string str_id) {
	std::array<char, 8> ret{0};
	int idx = 0;
	for (char c : str_id) {
		ret[idx++] = c;
	}
	return ret;
}
template <typename T, size_t N>
inline std::string to_string(const std::array<T, N> &t) {
	std::string str;
	for (char c : t) {
		if (c == 0) {
			break;
		}
		str.push_back(c);
	}
	return str;
}

class string_lite2 {
	union smart_array {
		char *point_;
		std::array<char, 8> array_;
	};

public:
	explicit string_lite2() : len_(0), data_{.array_ = {0}} {
	}

	explicit string_lite2(const std::string &str) {
		len_ = str.size();
		if (len_ > 8) {
			data_.point_ = new char[len_ + 1];
			data_.point_[len_] = '\0';
			memcpy(data_.point_, str.c_str(), len_);
		} else {
			data_.array_ = to_array(str);
		}
	}

	explicit string_lite2(const char *str) {
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

	std::string to_string() const {
		if (len_ > 8) {
			return std::string(data_.point_);
		} else {
			return ::to_string(data_.array_);
		}
	}

	~string_lite2() {
		if (len_ > 8) {
			delete[] data_.point_;
			data_.point_ = nullptr;
		}
	}

private:
	uint8_t len_;
	smart_array data_;
};

void print_mem() {
	mem_status_t s;
	self_mem_usage(&s);
	std::cout << s.vm_rss / 1024.0 << " MBytes" << std::endl;
}

int main() {
	const int N = 1000000;
	print_mem();  // 1.52734 MBytes

	// string_lite2 s1("abc");
	// std::cout << s1.to_string() << std::endl;
	// string_lite2 s2("abc0123456789");
	// std::cout << s2.to_string() << std::endl;

	// string_lite 19.5352 MBytes, 19.4219 MBytes
	{
		using T = string_lite;
		std::vector<T> vct;
		for (int i = 0; i < N; i++) {
			vct.emplace_back("abc");
		}
		print_mem();
	}

	// 标准malloc
	// {
	// 	int8_t i1;
	// 	int8_t i2;
	// 	std::cout << (&i2) - (&i1) << std::endl;  // 输出1

	// 	char *p1 = new char[1];
	// 	char *p2 = new char[1];
	// 	std::cout << p2 - p1 << std::endl;  // 输出32
	// 	std::cout << p3 - p2 << std::endl;
	// }

	// jemalloc
	// {
	// 	int8_t i1;
	// 	int8_t i2;
	// 	std::cout << (&i2) - (&i1) << std::endl;  // 输出1

	// 	char *p1 = new char[1];
	// 	char *p2 = new char[1];
	// 	char *p3 = new char[1];
	// 	std::cout << p2 - p1 << std::endl;  // 输出8
	// 	std::cout << p3 - p2 << std::endl;  // 输出8
	// }

	// string_lite // 10.8945 MBytes
	// {
	// 	using T = string_lite;
	// 	std::vector<T> vct;
	// 	vct.resize(N);
	// 	for (int i = 0; i < N; i++) {
	// 		T t;
	// 		vct[i] = t;
	// 	}
	// 	print_mem();
	// }

	// string_lite 41.3594 MBytes
	// {
	// 	using T = string_lite;
	// 	std::vector<T> vct;
	// 	vct.resize(N);
	// 	for (int i = 0; i < N; i++) {
	// 		T t("abc");
	// 		vct[i] = t;
	// 	}
	// 	print_mem();
	// }

	// string_lite
	// {
	// 	using T = string_lite;
	// 	std::vector<T> vct;
	// 	vct.reserve(N);
	// 	for (int i = 0; i < N; i++) {
	// 		vct.emplace_back("a");
	// 	}
	// 	print_mem();
	// }

	// std::string 33.8711 MBytes
	// {
	// 	using T = std::string;
	// 	std::vector<T> vct;
	// 	vct.resize(N);
	// 	for (int i = 0; i < N; i++) {
	// 		T t;
	// 		vct[i] = t;
	// 	}
	// 	print_mem();
	// }
	return 0;
}

// 1. 使用默认的malloc
// g++ test.cpp

// 2. 使用jemalloc
// export LD_LIBRARY_PATH=/usr/local/jemalloc-5.1.0/lib/:LD_LIBRARY_PATH
//  g++ test.cpp -ljemalloc -L/usr/local/jemalloc-5.1.0/lib/
// export MALLOC_CONF="background_thread:true,dirty_decay_ms:0,muzzy_decay_ms:0"
