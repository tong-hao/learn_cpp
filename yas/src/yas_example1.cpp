#include <iostream>
#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/mem_streams.hpp>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

struct broadcast_message_t {
	int vid;
	std::unordered_map<int, double> weights;

	template <typename Ar>
	void serialize(Ar &ar) {
		ar &YAS_OBJECT(nullptr /* reserved */, vid, weights);
	}
};

void print(const char *p, size_t size) {
	std::cout << size << std::endl;
	std::cout << "{\n";
	for (size_t i = 0; i < size; i++) {
		std::cout << *(p + i);
	}
	std::cout << "\n}\n";
}

int main() {
	yas::mem_ostream os;
	yas::binary_oarchive<yas::mem_ostream,
	                     yas::binary | yas::ehost | yas::no_header>
	    oa(os);

	// send
	std::cout << "send -->" << std::endl;
	broadcast_message_t msg;
	{
		msg.vid = 100;
		std::unordered_map<int, double> map;
		map[1] = 1.1;
		msg.weights = map;
	}
	oa &msg;
	auto buf2 = os.get_intrusive_buffer();
	print(buf2.data, buf2.size);

	// recv
	std::cout << "recv <--" << std::endl;
	constexpr std::size_t flags = yas::binary | yas::mem | yas::no_header;
	broadcast_message_t msg2;
	yas::load<flags>(buf2, msg2);
	for (auto it : msg2.weights) {
		std::cout << it.first << "=" << it.second << "\n";
	}
}

// export
// CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/home/caton.hao/build_code/nebula-analytics/3rd/yas/include
