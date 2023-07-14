#include "graph.h"
#include "../plato.h"

std::vector<int> getNbrs(int vid) {
	return plato::getNeighbors(vid);
}
