#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
const long ASIZE = 10000;

void test_array() {
	array<long, ASIZE> c;
	clock_t timeStart = clock();
	for (long i = 0; i < ASIZE; ++i) {
		c[i] = rand();
	}
	cout << (clock() - timeStart) << std::endl;
	cout << c.size() << endl;
	cout << c.front() << endl;
	cout << c.back() << endl;
	cout << c.data() << endl;

	// qsort(c.data(), ASIZE, sizeof(long), compareLongs);
	// bsearch…
}
