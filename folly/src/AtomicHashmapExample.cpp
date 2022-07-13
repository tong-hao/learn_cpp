#include <folly/AtomicHashMap.h>
#include <folly/portability/Atomic.h>
#include <iostream>
#include <string>
#include <utility>

using namespace folly;

int main(int argc, char const *argv[]) {
	AtomicHashMap<int64_t, int64_t> map{1024};

	// insert
	auto ret = map.insert(std::make_pair(100, 1));

	// increment
	__sync_fetch_and_add(&ret.first->second, 3);

	// get
	auto getValue = [&map](int64_t k) {
		auto ret = map.find(k);
		return ret != map.end() ? ret->second : 0;
	};

	std::cout << "key=100, value=" << getValue(100) << std::endl;

	return 0;
}
// link:-lfolly