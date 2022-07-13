#include <folly/hash/FarmHash.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <string>

uint32_t PartID(int64_t vertex_id, int32_t part_num) {
	int8_t bit_num = 32 - log2(part_num);
	return (folly::hash::farmhash::Fingerprint32(
	            reinterpret_cast<const char *>(&vertex_id),
	            sizeof(vertex_id)) >>
	        bit_num)
	       << bit_num;
}

uint32_t PartID2(int64_t vertex_id, int32_t part_num) {
	std::hash<std::string> hasher;
	int8_t H = 32 - log2(part_num);
	return (hasher(std::to_string(vertex_id)) >> H) << H;
}

int main(int argc, char const *argv[]) {
	const int64_t start_vertex_id = 10000;
	const int num = 2;
	const int part_num = 1024;

	std::cout << "======================" << std::endl;
	std::set<uint32_t> part_ids;
	for (int i = 0; i < part_num; i++) {
		uint32_t part_id = i << 22;
		part_ids.insert(part_id);
		std::cout << part_id << ",";
	}
	std::cout << std::endl;
	std::cout << "======================" << std::endl;

	for (int64_t i = start_vertex_id; i <= (start_vertex_id + num); i++) {
		auto part_id1 = PartID(i, part_num);
		// auto part_id2 = PartID2(i, part_num);
		auto iter = part_ids.find(part_id1);
		bool is_contain = (iter != part_ids.end());

		std::cout << part_id1 << ", " << is_contain << std::endl;
	}

	{
		int32_t i = 1023 << 22;
		uint32_t ui = 1023 << 22;
		uint32_t ui2 = i;
		int32_t i2 = ui;
		std::cout << i << ", " << i2 << std::endl;
		std::cout << ui << ", " << ui2 << std::endl;
	}

	return 0;
}

// link:-lfolly