#include <iostream>
#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/mem_streams.hpp>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

struct Msg {
	int vid;
	std::unordered_map<std::string, std::string> map;

	template <typename Ar>
	void serialize(Ar &ar) {
		ar &YAS_OBJECT(nullptr /* reserved */, vid, map);
	}
};

int main() {
	{
		int a = 3, aa{};
		short b = 4, bb{};
		float c = 3.14, cc{};

		constexpr std::size_t flags = yas::mem      // IO type
		                              | yas::json;  // IO format

		auto buf = yas::save<flags>(YAS_OBJECT("myobject", a, b, c));

		// buf = {"a":3,"b":4,"c":3.14}

		yas::load<flags>(
		    buf, YAS_OBJECT_NVP("myobject", ("a", aa), ("b", bb), ("c", cc)));
		// a == aa && b == bb && c == cc;
	}

	//========
	{
		constexpr std::size_t flags = yas::mem      // IO type
		                              | yas::json;  // IO format

		Msg msg;
		msg.vid = 100;
		std::unordered_map<std::string, std::string> map;
		map["abc"] = "123";
		msg.map = map;
		yas::shared_buffer buf2 = yas::save<flags>(msg);

		Msg msg2;
		yas::load<flags>(buf2, msg2);
		for (auto it : msg2.map) {
			std::cout << it.first << it.second;
		}
	}
}

// link: -g
