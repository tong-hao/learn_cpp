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

int main() {
	//
	{
		yas::mem_ostream os;
		yas::binary_oarchive<yas::mem_ostream,
		                     yas::binary | yas::ehost | yas::no_header>
		    oa(os);

		broadcast_message_t msg;
		msg.vid = 100;
		std::unordered_map<int, double> map;
		map[1] = 1.1;
		msg.weights = map;
		oa &msg;
	}
}

// link: -g
