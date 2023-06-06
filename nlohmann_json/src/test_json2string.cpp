#include <iostream>
#include <unordered_map>
#include <variant>
#include <vector>
#include "json.h"

int main() {
	// vector to string
	{
		std::vector<std::unordered_map<std::string, std::string>> myVec = {
		    {{"player.name", ">= f"},
		     {"player.age", ">= 30"},
		     {"like.likeness", ">= 1"}},  // condition1
		    {{"player.name", "< c"}}      // or condition2
		};

		nlohmann::json jsonVec(myVec);
		std::cout << jsonVec.dump() << std::endl;
	}

	return 0;
}
