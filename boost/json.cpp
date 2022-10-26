

#include <iostream>
#include <sstream>

#include <boost/property_tree/json_parser.hpp>

int main(int argc, char** argv) {
	std::stringstream ss;
	ss << "{'a':'1','b','2'}";

	boost::property_tree::ptree pt;
	boost::property_tree::read_json(ss, pt);
	std::cout << pt.get<std::string>("a") << std::endl;
}

// link: -lboost_serialization
