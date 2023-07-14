#include "plato.h"

namespace plato {
std::vector<int> getNeighbors(int src) {
	std::vector<int> ret;
	ret.push_back(src + 1);
	ret.push_back(src + 2);
	ret.push_back(src + 3);
	return ret;
}
}  // namespace plato
