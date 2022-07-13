#include <folly/container/EvictingCacheMap.h>
#include <iostream>
#include <tuple>

std::string tostring(int i1, int i2, int i3) {
	std::string key;
	key.append(std::to_string(i1)).append(",");
	key.append(std::to_string(i2)).append(",");
	key.append(std::to_string(i3));
	return key;
}

int main2(int argc, char const *argv[]) {
	// folly::EvictingCacheMap<int, int> lru{100, 10};
	folly::EvictingCacheMap<std::string, int> lru(100);
	for (int i = 0; i < 1000; i++) {
		auto key = tostring(i, i * 2, i * 4);
		lru.set(key, i * 3);
	}

	for (int i = 0; i < 1000; i++) {
		auto key = tostring(i, i * 2, i * 4);
		if (lru.exists(key)) {
			auto v = lru.get(key);
			std::cout << i << ", " << v << std::endl;
		}
	}

	return 0;
}

int main(int argc, char const *argv[]) {
	folly::EvictingCacheMap<std::tuple<int32_t, int32_t, std::string>, int> lru(
	    100);
	for (int i = 0; i < 1000; i++) {
		auto s = tostring(i, i * 2, i * 4);
		auto key = std::make_tuple(i, i + 1, s);
		lru.set(key, i * 3);
	}

	for (int i = 0; i < 1000; i++) {
		auto s = tostring(i, i * 2, i * 4);
		auto key = std::make_tuple(i, i + 1, s);
		if (lru.exists(key)) {
			auto v = lru.get(key);
			std::cout << i << ", " << v << std::endl;
		}
	}

	return 0;
	return 0;
}

// link: -lfolly -lboost_context -lboost_system -ldl -levent -ldouble-conversion
// link: -lz -llz4 -lsnappy -liberty -lfmt -lssl -lcrypto -lpthread -lglog
// link: -lgflags  -lfolly -fopenmp -lnuma