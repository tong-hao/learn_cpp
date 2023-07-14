#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "json.h"

using json = nlohmann::json;

// string_lite is a lightweight string. And its member `data_` is a `char*`. It
// can be used as an alternative to std::string.
// std::string occupies at least 32 bytes, while string_lite occupies
// 8+strlen(data_).
// string_lite can be used for string vid or string properties.
//
// issues:
// 1) '\0' is a string termination symbol. string_lite is not supported '\0'.
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

	friend void to_json(nlohmann::json &j, const string_lite &str) {
		j = str.to_string();
		std::cout << "to_json:" << str.to_string() << std::endl;
	}
	friend void from_json(const nlohmann::json &j, string_lite &str) {
		str = string_lite(j.get<std::string>());
		std::cout << "from_json:" << str.to_string() << std::endl;
	}

private:
	char *data_;
};

// Define a custom hash function for string_lite
namespace std {
template <>
struct hash<string_lite> {
	std::size_t operator()(const string_lite &s) const noexcept {
		std::size_t h = 0;
		return h;
	}
};
}  // namespace std

struct vertex_t {
public:
	std::string tag_name_;
	std::string vid_;
	std::map<string_lite, std::string> props_;

	vertex_t() {
	}

	// vertex_t(const std::string &tag_name, std::string vid,
	//          const std::unordered_map<string_lite, std::string> &props)
	//     : tag_name_(tag_name), vid_(vid), props_(props) {
	// }
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(vertex_t, tag_name_, vid_, props_);
};

int main() {
	{
		string_lite str("abc");
		nlohmann::json j(str);
		std::cout << j.dump() << std::endl;

		string_lite s2 = j;
		std::cout << s2.to_string() << std::endl;
	}
	{
		vertex_t v;
		v.tag_name_ = "t1";
		v.vid_ = "100";
		v.props_.emplace(string_lite("p1"), "v1");

		nlohmann::json j(v);
		std::cout << j.dump() << std::endl;
	}

	return 0;
}
