#include <cstring>
#include <iostream>
#include <unordered_map>

#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/mem_streams.hpp>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

class string_lite {
public:
	string_lite() : data_(nullptr) {
	}

	string_lite(const std::string &str) {
		size_t len = str.size();
		data_ = new char[len + 1];
		data_[len] = '\0';
		memcpy(data_, str.c_str(), len);
	}

	string_lite(const char *str) {
		size_t len = strlen(str);
		data_ = new char[len + 1];
		data_[len] = '\0';
		memcpy(data_, str, len);
	}

	string_lite(const string_lite &other) {
		size_t len = strlen(other.data_);
		data_ = new char[len + 1];
		data_[len] = '\0';
		memcpy(data_, other.data_, len);
	}

	string_lite &operator=(const string_lite &other) {
		if (this != &other) {
			delete[] data_;
			size_t len = strlen(other.data_);
			data_ = new char[len + 1];
			data_[len] = '\0';
			memcpy(data_, other.data_, len);
		}
		return *this;
	}

	~string_lite() {
		delete[] data_;
	}

	std::string to_string() const {
		if (!data_) {
			return "";
		}
		return std::string(data_);
	}

	operator std::string() const {
		return to_string();
	}

	template <typename Ar>
	void serialize(Ar &ar) {
		// ar &YAS_OBJECT(nullptr /* reserved */, data_);
		// "object0", ("i0", i0)

		ar &YAS_OBJECT_NVP("object0", ("i0", data_));
	}

public:
	char *data_;
};

struct broadcast_message_t {
	int vid;
	string_lite str;

	template <typename Ar>
	void serialize(Ar &ar) {
		ar &YAS_OBJECT(nullptr /* reserved */, vid, str);
	}
};

using oarchive_detail_t =
    yas::binary_oarchive<yas::mem_ostream,
                         yas::binary | yas::ehost | yas::no_header>;

using iarchive_detail_t =
    yas::binary_iarchive<yas::mem_istream,
                         yas::binary | yas::ehost | yas::no_header>;
struct msg_t {
	int vid;
	char *str;

	// template <typename Ar>
	// void serialize(Ar &ar) {
	// 	// yas::intrusive_buffer(str, strlen(str))
	// 	ar &YAS_OBJECT(nullptr, vid);

	// 	std::cout << typeid(ar).name() << std::endl;
	// }

	void serialize(oarchive_detail_t &ar) {
		// if (!str) {
		// 	str = new char[1]{'\0'};
		// 	std::cout << "111" << std::endl;
		// }
		ar &YAS_OBJECT(nullptr, vid, yas::intrusive_buffer(str, strlen(str)));
	}

	void serialize(iarchive_detail_t &ar) {
		std::string s;
		ar &YAS_OBJECT(nullptr, vid, s);
		str = new char[s.size() + 1];
		memcpy(str, s.c_str(), s.size());

		std::cout << "222:" << s << std::endl;
	}
};
int main() {
	std::string abc = "123\123";
	msg_t msg1;
	msg1.vid = 100;
	msg1.str = nullptr;
	msg_t msg2;

	constexpr std::size_t flags =
	    yas::mem | yas::binary | yas::ehost | yas::no_header;
	auto buf = yas::save<flags>(msg1);
	yas::load<flags>(buf, msg2);

	std::cout << msg2.vid << std::endl;
	std::cout << msg2.str << std::endl;
}
