#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void test_vector() {
	vector<string> c;
	char buf[10];
	clock_t timeStart = clock();
	for (long i = 0; i < 10000; ++i) {
		try {
			snprintf(buf, 10, "%d", rand());
			c.push_back(string(buf));
		} catch (exception& p) {
		}
	}

	// find
	long target = 124;
	auto p = ::find(c.begin(), c.end(), target);

	//
	// sort(c.begin(), b.end());
	// bsearch(&target, (c.data()), c.size(), sizof(strimng), );
}
