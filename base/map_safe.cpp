#include <iostream>
#include <map>
#include <memory>
#include <mutex>

struct CacheData {};

class Cache3 {
	mutable std::mutex _mtx;
	std::map<int, std::shared_ptr<CacheData> > _map;

public:
	std::shared_ptr<CacheData> get(int key) const {
		std::lock_guard<std::mutex> l(_mtx);
		std::map<int, std::shared_ptr<CacheData> >::const_iterator it;
		if ((it = _map.find(key)) != _map.end()) {
			auto val = it->second;
			return val;
		}
		return std::shared_ptr<CacheData>();
	}  // auto unlock (lock_guard, RAII)

	void insert(int key, std::shared_ptr<CacheData> value) {
		std::lock_guard<std::mutex> l(_mtx);
		_map.insert(std::make_pair(key, value));
	}  // auto unlock (lock_guard, RAII)
};

int main(int argc, char const *argv[]) {
	Cache3 cache;
	cache.insert(1, std::make_shared<CacheData>());
	auto v1 = cache.get(1);
	if (v1) {
		std::cout << "v1=" << v1 << std::endl;
	} else {
		std::cout << "can not find key=1" << std::endl;
	}

	return 0;
}
