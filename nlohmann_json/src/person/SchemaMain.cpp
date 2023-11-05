#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../json.h"

struct IdElement {
	std::string type_;
	int index_;
};
struct PropElement {
	std::string name_;
	std::string type_;
	int index_;
};
struct VertexElement {
	std::string path_;
	std::string delimiter_;
	std::string name_;
	IdElement id_;
	std::vector<PropElement> props_;
};
struct EdgeElement {
	std::string path_;
	std::string delimiter_;
	std::string name_;
	IdElement src_;
	IdElement dst_;
	std::vector<PropElement> props_;
};
struct CsvSchema {
	std::vector<VertexElement> vertices_;
	std::vector<EdgeElement> edges_;
};

void from_json(const nlohmann::json& j, IdElement& e) {
	j.at("type").get_to(e.type_);
	j.at("index").get_to(e.index_);
}
void from_json(const nlohmann::json& j, PropElement& e) {
	j.at("name").get_to(e.name_);
	j.at("type").get_to(e.type_);
	j.at("index").get_to(e.index_);
}
void from_json(const nlohmann::json& j, VertexElement& e) {
	j.at("path").get_to(e.path_);
	j.at("delimiter").get_to(e.delimiter_);
	j.at("name").get_to(e.name_);
	j.at("id").get_to(e.id_);
	j.at("props").get_to(e.props_);
}
void from_json(const nlohmann::json& j, EdgeElement& e) {
	j.at("path").get_to(e.path_);
	j.at("delimiter").get_to(e.delimiter_);
	j.at("name").get_to(e.name_);
	j.at("src").get_to(e.src_);
	j.at("dst").get_to(e.dst_);
	j.at("props").get_to(e.props_);
}
void from_json(const nlohmann::json& j, CsvSchema& s) {
	j.at("vertices").get_to(s.vertices_);
	j.at("edges").get_to(s.edges_);
}

void to_json(nlohmann::json& j, const IdElement& e) {
	j = nlohmann::json{{"type", e.type_}, {"index", e.index_}};
}
void to_json(nlohmann::json& j, const PropElement& e) {
	j = nlohmann::json{
	    {"name", e.name_}, {"type", e.type_}, {"index", e.index_}};
}
void to_json(nlohmann::json& j, const VertexElement& e) {
	j = nlohmann::json{{"path", e.path_},
	                   {"delimiter", e.delimiter_},
	                   {"name", e.name_},
	                   {"id", e.id_},
	                   {"props", e.props_}};
}
void to_json(nlohmann::json& j, const EdgeElement& e) {
	j = nlohmann::json{{"path", e.path_}, {"delimiter", e.delimiter_},
	                   {"name", e.name_}, {"src", e.src_},
	                   {"dst", e.dst_},   {"props", e.props_}};
}
void to_json(nlohmann::json& j, const CsvSchema& s) {
	j = nlohmann::json{{"vertices", s.vertices_}, {"edges", s.edges_}};
}

int main(int argc, char const* argv[]) {
	{
		CsvSchema csv;
		{
			EdgeElement e1;
			e1.path_ = "path_e1.csv";
			e1.delimiter_ = "|";
			e1.name_ = "knows";
			e1.src_ = IdElement{"string", 1};
			e1.dst_ = IdElement{"string", 2};
			std::vector<PropElement> props{{"p1", "string", 3},
			                               {"p2", "int", 4}};
			e1.props_ = std::move(props);

			csv.edges_.emplace_back(std::move(e1));
		}

		{
			VertexElement v1;
			v1.path_ = "path_v1.csv";
			v1.delimiter_ = "|";
			v1.name_ = "person";
			v1.id_ = IdElement{"string", 1};
			std::vector<PropElement> props{{"p1", "string", 2},
			                               {"p2", "int", 3}};
			v1.props_ = std::move(props);
			csv.vertices_.emplace_back(v1);
			csv.vertices_.emplace_back(v1);
		}

		nlohmann::json j(csv);
		auto json_str = j.dump();
		std::cout << json_str << std::endl;

		std::fstream f("../data/schema.json");
		if (!f) {
			std::cerr << "read schema.json fail." << std::endl;
			return 1;
		}
		nlohmann::json j2 = nlohmann::json::parse(f);
		auto schema = j2.get<CsvSchema>();
		std::cout << "vertex:" << schema.vertices_.size() << std::endl;
		std::cout << "edges:" << schema.edges_.size() << std::endl;
	}

	return 0;
}
