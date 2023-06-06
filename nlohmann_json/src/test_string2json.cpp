#include <iostream>
#include <unordered_map>
#include <vector>
#include "json.h"

int main() {
	{
		// string to vector
		nlohmann::json j = {{"vertices", {"a", "b"}}, {"name", "ht"}};

		if (j["vertices"].size() > 0 && j["vertices"][0].is_number_integer()) {
			std::vector<int> vct = j["vertices"].get<std::vector<int>>();
			for (auto id : vct) {
				std::cout << id << std::endl;
			}
		} else {
			std::vector<std::string> vct =
			    j["vertices"].get<std::vector<std::string>>();
			for (auto id : vct) {
				std::cout << id << std::endl;
			}
		}
	}

	{
		std::unordered_map<std::string, int> m{{"code", 0}, {"code1", 1}};
		nlohmann::json j_res(m);

		nlohmann::json j = {{"name", "Alice"}, {"age", 25}};
		std::cout << (j["code"] == 0) << std::endl;
		std::string name = j["name"];
		std::cout << name << std::endl;
	}
	{
		std::string resp = "{\"vertices\":[{\"vid_\":\"1\"}]}";
		nlohmann::json j = nlohmann::json::parse(resp);
		std::cout << j["vertices"][0]["vid_"].is_number_integer() << std::endl;
		// if (j["vertices"].size() > 0 &&
		//     j["vertices"][0]["vid_"].is_number_integer()) {
		// 	auto t = j["vertices"].get<std::vector<int>>();
		// } else {
		// 	auto t = j["vertices"].get<std::vector<std::string>>();
		// }
	}

	return 0;
}
