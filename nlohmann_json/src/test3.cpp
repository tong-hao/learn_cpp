#include <iostream>
#include <string>
#include <vector>
#include "json.h"

using json = nlohmann::json;

struct Person {
	std::string name;
	int age;
	std::vector<std::string> phones;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Person, name, age, phones)
};

struct Null {
	const bool is_null = true;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Null, is_null)
};

int main() {
	{
		Null n;
		json j = n;
		std::string json_str = j.dump();
		std::cout << json_str << std::endl;
	}

	std::vector<Person> people = {
	    {"John", 30, {"123-456-7890", "234-567-8901"}},
	    {"Alice", 25, {"987-654-3210"}},
	    {"Bob", 40, {"555-123-4567", "555-987-6543"}}};
	json j = people;
	std::string json_str = j.dump();
	std::cout << json_str << std::endl;

	nlohmann::json j2 = nlohmann::json::parse(json_str);
	auto vct2 = j2.get<std::vector<Person>>();
	std::cout << vct2.size() << std::endl;

	return 0;
}
