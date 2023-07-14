#include <iostream>
#include <vector>

// 2.1.21 Gas Station

// There are N gas stations along a circular route, where the amount of gas at
// station i is gas[i].

// You have a car with an unlimited gas tank and it costs cost[i] of gas to
// travel from station i to its next station (i+1). You begin the journey with
// an empty tank at one of the gas stations.

// Return the starting gas station’s index if you can travel around the circuit
// once, otherwise return -1. Note: The solution is guaranteed to be unique.

class Solution1 {
public:
	// find starting gas station
	int find(const std::vector<int>& gas, const std::vector<int>& cost) {
		int total = 0;
		int stat = 0;
		size_t starting = 0;

		// cost[i] 是 i 到 i+1的汽油消耗
		// gas[i] 是 i station的汽油量

		for (size_t i = 0; i < gas.size(); i++) {
			total += (gas[i] - cost[i]);
			stat += (gas[i] - cost[i]);
			if (stat <= 0) {
				starting = i;
			}
		}
		if (total > 0) {
			return starting;
		}
		return -1;
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<int> gas{1, 2, 5, 4, 5};
		std::vector<int> cost{1, 3, 3, 4, 5};

		Solution1 s;
		std::cout << s.find(gas, cost) << std::endl;
	}

	return 0;
}
