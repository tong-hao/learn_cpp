#include <folly/dynamic.h>
#include <folly/json.h>
#include <iostream>
#include <string>

using folly::dynamic;

//////////////////////////////
// 注意：
// 1. 声明类型不能用auto, 需要使用folly::dynamic声明
//
/////////////////////////////

int main(int argc, char const *argv[]) {
	// overview
	dynamic i = 100;
	std::cout << "i = " << i << std::endl;

	i = "hello";
	std::cout << "i = " << i << std::endl;

	// asInt asString asDouble
	dynamic i2 = 100;
	std::string s = i2.asString();
	i2.getInt();
	std::cout << s << std::endl;

	// map
	dynamic map = dynamic::object("a", 1)("b", "2");
	for (auto &e : map.items()) {
		std::cout << e.first << " " << e.second << std::endl;
	}
	map["c"] = 3;
	map.erase("c");
	map.keys();
	map.values();
	std::string str = folly::toJson(map);

	// array
	dynamic arr = dynamic::array("a", 1, "b", 2);
	arr.push_back(dynamic::object("c", 3));
	for (auto &e : arr) {
		std::cout << e << std::endl;
	}

	// json
	std::string jsonDocument =
	    R"({"key":12,"key2":[false, null, true, "yay"]})";
	dynamic parsed = folly::parseJson(jsonDocument);
	std::cout << parsed["key2"][2] << std::endl;

	// json graph-schema
	std::cout << "========== schema ========="
	          << "\n";
	std::string schema =
	    R"([{"db_id":1,"db_name":"db_1","vertex_types":[{"id":10,"name":"pin","props":[{"id":100,"name":"pin_no","value_type":9}]},{"id":11,"name":"mac","props":[{"id":110,"name":"mac_no","value_type":9}]}],"edge_types":[{"id":21,"name":"pin2mac","props":[{"id":210,"name":"rank","value_type":4}]}]}])";
	dynamic parsed_schema = folly::parseJson(schema);

	for (auto item : parsed_schema) {
		std::cout << "db_id:" << item["db_id"] << std::endl;
	}

	return 0;
}

// link: -lfolly -lglog -ldouble-conversion