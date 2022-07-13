#include <folly/Function.h>
#include <folly/PackedSyncPtr.h>
#include <iostream>
#include <string>

using folly::PackedSyncPtr;

template <typename T>
class SyncVec {
	PackedSyncPtr<T> base;

public:
	SyncVec() {
		base.init();
	}

	void push_back(const T& t) {
		base.set(static_cast<T*>(
		    realloc(base.get(), (base.extra() + 1) * sizeof(T))));
		base[base.extra()] = t;
		base.setExtra(base.extra() + 1);
	}

	size_t size() const {
		return base.extra();
	}

	void lock() {
		base.lock();
	}

	void unlock() {
		base.unlock();
	}

	T* begin() const {
		return base.get();
	}

	T* end() const {
		return base.get() + base.extra();
	}
};

int main(int argc, char const* argv[]) {
	// multi thread
	SyncVec<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(15);

	for (auto p = vec.begin(); p != vec.end(); p++) {
		std::cout << *p << std::endl;
	}

	return 0;
}

// link:-lfolly -lgflags -lglog