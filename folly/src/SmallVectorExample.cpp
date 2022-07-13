#include <folly/small_vector.h>
#include <iostream>

int main(int argc, char const* argv[]) {
	folly::small_vector<int, 2> vec;
	vec.push_back(0);  // Stored in-place on stack
	vec.push_back(1);  // Still on the stack
	vec.push_back(2);  // Switches to heap buffer.

	for (auto& e : vec) {
		std::cout << e << std::endl;
	}

	// With space for 32 in situ unique pointers, and only using a
	// 4-byte size_type.
	folly::small_vector<std::unique_ptr<int>, 32, uint32_t> v;

	// A inline vector of up to 256 ints which will not use the heap.
	folly::small_vector<int, 256, folly::small_vector_policy::NoHeap> v2;

	// Same as the above, but making the size_type smaller too.
	folly::small_vector<int, 256, folly::small_vector_policy::NoHeap, uint16_t>
	    v3;

	return 0;
}

// link:-lfolly