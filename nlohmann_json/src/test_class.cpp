#include <iostream>
#include <unordered_map>
#include <variant>
#include <vector>
#include "json.h"

struct Person {
	std::string name;
	int age;
	std::vector<std::string> phones;
};

void from_json(const nlohmann::json& j, Person& p) {
	j.at("name").get_to(p.name);
	j.at("age").get_to(p.age);
	j.at("phones").get_to(p.phones);
}

void to_json(nlohmann::json& j, const Person& p) {
	j = nlohmann::json{{"name", p.name}, {"age", p.age}, {"phones", p.phones}};
}

void from_json(const nlohmann::json& j, std::vector<Person>& persons) {
	for (const auto& item : j) {
		Person p;
		item.get_to(p);
		persons.push_back(p);
	}
}

void to_json(nlohmann::json& j, const std::vector<Person>& persons) {
	j = nlohmann::json::array();
	for (const auto& p : persons) {
		j.push_back(p);
	}
}

int main() {
	{
		Person p;
		p.name = "ht";
		p.age = 30;
		p.phones.push_back("phone1");

		nlohmann::json jsonVec(p);
		auto json_str = jsonVec.dump();
		std::cout << json_str << std::endl;

		nlohmann::json j = nlohmann::json::parse(json_str);
		auto p2 = j.get<Person>();

		std::cout << "p2 == p ? " << (p2.name == p.name) << std::endl;
	}

	// struct to string
	{
		std::vector<Person> vct;
		Person p;
		p.name = "ht";
		p.age = 30;
		p.phones.push_back("phone1");
		vct.push_back(p);

		nlohmann::json jsonVec(vct);
		auto json_str = jsonVec.dump();
		std::cout << json_str << std::endl;

		nlohmann::json j = nlohmann::json::parse(json_str);
		auto vct2 = j.get<std::vector<Person>>();
	}

	{
		std::vector<Person> people = {
		    {"John", 30, {"123-456-7890", "234-567-8901"}},
		    {"Alice", 25, {"987-654-3210"}},
		    {"Bob", 40, {"555-123-4567", "555-987-6543"}}};
		nlohmann::json j = people;
		std::string json_str = j.dump(4);
		std::cout << json_str << std::endl;

		nlohmann::json j2 = nlohmann::json::parse(json_str);
		auto vct2 = j2.get<std::vector<Person>>();
		std::cout << vct2.size() << std::endl;

		return 0;
	}
}
