#include <map>
#include <utility>
#include <string>


class Element
{
public:
	Element() = default;
	~Element() = default;
	
};

int main(int argc, char const *argv[])
{
	std::map<std::pair<int16_t, std::string>,Element> map;

	int16_t i = 1;
	std::string s = "a";
	auto k = std::make_pair(i, s);

	map.emplace(k, Element()); 
	map[k] = Element();
	


	
	return 0;
}