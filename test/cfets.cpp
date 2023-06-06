// build:
// g++ -std=c++17 cfets.cpp -o cfets
//
// schema：vid_type=int64
// tag fx_instn(instn_cn_full_nm string,
//			    instn_cn_shrt_nm string,
// 				instn_en_full_nm string,
// 				instn_en_shrt_nm string,
// 				instn_tp string,
//			    tp_of_org_id int,
//  			instn_st string,
// 				instn_grnd_tp_cn string
//  );
// tag rmb_instn(instn_cn_full_nm string,
//			    instn_cn_shrt_nm string,
// 				instn_en_full_nm string,
// 				instn_en_shrt_nm string,
// 				instn_tp string,
//			    tp_of_org_id int,
//  			instn_st string,
// 				instn_grnd_tp_cn string
//  );
// 交易产品、货币对、即期利率、交易量
// edge fxspt(dl_tm datatime, // 成交时间
// 			  dl_cd string,   // 成交编号
// 			  prdct_cd string, // 交易产品代码         // 交易产品
// 			  ccy_pair_cd string, // 货币对代码        // 货币对
// 			  prd string,         // 期限
// 			  dlt_amnt double,    // 交易货币金额（汇率）// 即期利率
// 			  txn_all_prc double, // 成交全价          // 交易量
//            tkr_dir string      // 发起方交易方向
// );
//
#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using VID_T = std::string;
using PROPVAL_T = std::variant<std::string, bool, int, double>;
using PROPS_T = std::unordered_map<std::string, PROPVAL_T>;

std::string to_string(const PROPVAL_T& p) {
	std::string s;
	switch (p.index()) {
		case 0:
			return std::get<std::string>(p);
		case 1:
			return std::get<bool>(p) ? "true" : "false";
		case 2:
			return std::to_string(std::get<int>(p));
		case 3:
			return std::to_string(std::get<double>(p));

		default:
			return "";
	}
}

std::string to_string(const PROPS_T& props) {
	std::string s;
	for (const auto& p : props) {
		s.append(p.first).append("=").append(to_string(p.second)).append(",");
	}
	return s;
}

struct Node {
	VID_T id_;
	PROPS_T props_;
};
struct Edge {
	VID_T src_;
	VID_T dst_;
	int rank_;
	PROPS_T props_;
};

class Graph {
public:
	void addNode(VID_T id, const PROPS_T& props);
	void addEdge(VID_T src, VID_T dst, const PROPS_T& props, int rank = 0);
	std::pair<bool, Node> getNode(VID_T src) const;
	std::vector<Edge> getOutEdges(VID_T src) const;
	std::vector<Edge> getInEdges(VID_T src) const;
	std::unordered_set<VID_T> getOutVertices(VID_T src) const;
	std::unordered_set<VID_T> getInVertices(VID_T src) const;

private:
	std::unordered_map<VID_T, Node> nodes_;
	std::unordered_map<VID_T, std::vector<Edge>> outEdges_;
	std::unordered_map<VID_T, std::vector<Edge>> inEdges_;
};

void Graph::addNode(VID_T id, const PROPS_T& props) {
	Node n;
	n.id_ = id;
	n.props_ = props;

	nodes_.emplace(id, n);
}

void Graph::addEdge(VID_T src, VID_T dst, const PROPS_T& props, int rank) {
	auto found1 = nodes_.find(src);
	auto found2 = nodes_.find(dst);
	if (found1 == nodes_.end()) {
		std::cerr << "Cannot find src. id=" << src << std::endl;
		return;
	}
	if (found2 == nodes_.end()) {
		std::cerr << "Cannot find dst. id=" << dst << std::endl;
		return;
	}
	Edge edge{src, dst, rank, props};

	outEdges_[src].push_back(edge);
	inEdges_[dst].push_back(edge);
}

std::pair<bool, Node> Graph::getNode(VID_T src) const {
	auto found = nodes_.find(src);
	if (found != nodes_.end()) {
		return {true, found->second};
	}
	return {false, Node()};
}

std::vector<Edge> Graph::getOutEdges(VID_T src) const {
	auto found = outEdges_.find(src);
	if (found != outEdges_.end()) {
		return found->second;
	}
	return {};
}

std::vector<Edge> Graph::getInEdges(VID_T src) const {
	auto found = inEdges_.find(src);
	if (found != inEdges_.end()) {
		return found->second;
	}
	return {};
}

std::unordered_set<VID_T> Graph::getOutVertices(VID_T src) const {
	std::unordered_set<VID_T> ret;
	auto found = outEdges_.find(src);
	if (found != outEdges_.end()) {
		for (const auto& e : found->second) {
			ret.insert(e.dst_);
		}
	}
	return ret;
}

std::unordered_set<VID_T> Graph::getInVertices(VID_T src) const {
	std::unordered_set<VID_T> ret;
	auto found = inEdges_.find(src);
	if (found != inEdges_.end()) {
		for (const auto& e : found->second) {
			ret.insert(e.src_);
		}
	}
	return ret;
}

std::vector<std::vector<Edge>> combinations(const std::vector<Edge>& inputs) {
	std::vector<std::vector<Edge>> result;
	const int n = inputs.size();
	for (int mask = 0; mask < (1 << n); ++mask) {
		std::vector<Edge> combination;
		for (int i = 0; i < n; ++i) {
			if (mask & (1 << i)) {
				combination.push_back(inputs[i]);
			}
		}
		if (combination.empty()) {
			continue;
		}
		result.push_back(combination);
	}
	return result;
}

// 时间格式为：2023-03-28T06:07:01.987
// input format: 2021-10-12T10:10:10.0900
int64_t diff_sec(const char* time1, const char* time2) {
	if (strlen(time1) < 19 || strlen(time2) < 19) {
		std::cerr << "Cannot parse time. time1=" << time1 << ", time2=" << time2
		          << "\n";
		return std::numeric_limits<int64_t>::max();
	}
	int64_t iY1 = atoi(time1);
	int64_t iM1 = atoi(time1 + 5);
	int64_t iD1 = atoi(time1 + 8);
	int64_t iH1 = atoi(time1 + 11);
	int64_t iMin1 = atoi(time1 + 14);
	int64_t iS1 = atoi(time1 + 17);

	int64_t iY2 = atoi(time2);
	int64_t iM2 = atoi(time2 + 5);
	int64_t iD2 = atoi(time2 + 8);
	int64_t iH2 = atoi(time2 + 11);
	int64_t iMin2 = atoi(time2 + 14);
	int64_t iS2 = atoi(time2 + 17);

	int64_t timestamp1 = iY1 * 31536000 + iM1 * 2592000 + iD1 * 86400 +
	                     iH1 * 3600 + iMin1 * 60 + iS1;
	int64_t timestamp2 = iY2 * 31536000 + iM2 * 2592000 + iD2 * 86400 +
	                     iH2 * 3600 + iMin2 * 60 + iS2;
	return timestamp1 - timestamp2;
}

std::unordered_set<VID_T> intersect(const std::unordered_set<VID_T>& set1,
                                    const std::unordered_set<VID_T>& set2) {
	std::vector<VID_T> vec1(set1.begin(), set1.end());
	std::vector<VID_T> vec2(set2.begin(), set2.end());

	std::sort(vec1.begin(), vec1.end());
	std::sort(vec2.begin(), vec2.end());

	std::vector<VID_T> intersection(vec1.size() + vec2.size());
	std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
	                      intersection.begin());

	std::unordered_set<VID_T> ret;
	for (const auto& id : intersection) {
		ret.insert(id);
	}
	return ret;
}

bool match(const Edge& e1, const Edge& e2) {
	if (std::get<std::string>(e1.props_.at("prdct_cd")) ==
	        std::get<std::string>(e2.props_.at("prdct_cd")) &&
	    std::get<std::string>(e1.props_.at("ccy_pair_cd")) ==
	        std::get<std::string>(e2.props_.at("ccy_pair_cd")) &&
	    std::get<double>(e1.props_.at("dlt_amnt")) ==
	        std::get<double>(e2.props_.at("dlt_amnt")) &&
	    std::get<double>(e1.props_.at("txn_all_prc")) ==
	        std::get<double>(e2.props_.at("txn_all_prc"))) {
		return true;
	}

	return false;
}

bool match(const std::vector<Edge>& vct1, const std::vector<Edge>& vct2) {
	if (vct1.empty() || vct2.empty()) {
		return false;
	}
	double prc1_total;
	double prc2_total;
	const auto& e1 = vct1[0];
	for (const auto& e : vct1) {
		if (std::get<std::string>(e1.props_.at("prdct_cd")) !=
		        std::get<std::string>(e.props_.at("prdct_cd")) ||
		    std::get<std::string>(e1.props_.at("ccy_pair_cd")) !=
		        std::get<std::string>(e.props_.at("ccy_pair_cd")) ||
		    std::get<double>(e1.props_.at("dlt_amnt")) !=
		        std::get<double>(e.props_.at("dlt_amnt"))) {
			return false;
		}

		prc1_total += std::get<double>(e.props_.at("txn_all_prc"));
	}
	for (const auto& e : vct2) {
		if (std::get<std::string>(e1.props_.at("prdct_cd")) !=
		        std::get<std::string>(e.props_.at("prdct_cd")) ||
		    std::get<std::string>(e1.props_.at("ccy_pair_cd")) !=
		        std::get<std::string>(e.props_.at("ccy_pair_cd")) ||
		    std::get<double>(e1.props_.at("dlt_amnt")) !=
		        std::get<double>(e.props_.at("dlt_amnt"))) {
			return false;
		}
		prc2_total += std::get<double>(e.props_.at("txn_all_prc"));
	}

	if (fabsf(prc1_total - prc2_total) >= 0.000001) {
		false;
	}
	return true;
}

std::vector<Edge> cfets(const Graph& g, const Edge& e_a2b) {
	std::vector<Edge> ret;
	auto a = e_a2b.src_;
	auto b = e_a2b.dst_;
	auto time = std::get<std::string>(e_a2b.props_.at("dl_tm"));

	// 1） 1对1情况
	// 存在b->a的边，与a->b的交易产品、货币对、即期利率、交易量 4个属性相同
	for (const auto& edge : g.getOutEdges(b)) {
		if (edge.dst_ == a && match(edge, e_a2b)) {
			ret.push_back(edge);
			ret.push_back(e_a2b);
			return ret;
		}
	}
	// 2）多对多情况
	// 交易产品、货币对、即期利率 相同，交易量（累加）

	// 排除的环情况
	auto exclude_for_a = intersect(g.getOutVertices(a), g.getInVertices(a));
	auto exclude_for_b = intersect(g.getOutVertices(b), g.getInVertices(b));

	// 获取A->B的边(10s)
	std::vector<Edge> edges_a2b;
	for (auto& edge : g.getOutEdges(a)) {
		auto dl_tm = std::get<std::string>(edge.props_.at("dl_tm"));
		auto dl_tm_diff = diff_sec(time.c_str(), dl_tm.c_str());
		if (edge.dst_ == b && dl_tm_diff <= 10 && dl_tm_diff >= 0) {
			edges_a2b.push_back(edge);
		}
	}

	// 获取A的入边 e->a
	std::unordered_map<VID_T, std::vector<Edge>> edges_e2a;
	for (auto& edge : g.getInEdges(a)) {
		auto dl_tm = std::get<std::string>(edge.props_.at("dl_tm"));
		auto dl_tm_diff = diff_sec(time.c_str(), dl_tm.c_str());
		if (exclude_for_a.find(edge.src_) == exclude_for_a.end() &&
		    dl_tm_diff <= 10 && dl_tm_diff >= 0) {
			edges_e2a[edge.src_].push_back(edge);
		}
	}

	// 获取B的出边 b->f
	std::unordered_map<VID_T, std::vector<Edge>> edges_b2f;
	for (auto& edge : g.getOutEdges(b)) {
		auto dl_tm = std::get<std::string>(edge.props_.at("dl_tm"));
		auto dl_tm_diff = diff_sec(time.c_str(), dl_tm.c_str());
		if (exclude_for_b.find(edge.dst_) == exclude_for_b.end() &&
		    dl_tm_diff <= 10 && dl_tm_diff >= 0) {
			edges_b2f[edge.dst_].push_back(edge);
		}
	}

	auto stat = [](const std::vector<Edge>& vct1, const std::vector<Edge> vct2,
	               std::vector<Edge>& ret) {
		auto combs1 = combinations(vct1);
		auto combs2 = combinations(vct2);
		for (const auto& c1 : combs1) {
			for (const auto& c2 : combs2) {
				if (match(c1, c2)) {
					ret.insert(ret.end(), c1.begin(), c1.end());
					ret.insert(ret.end(), c2.begin(), c2.end());
				}
			}
		}
	};

	// 模式：E->A->B
	for (const auto& e : edges_e2a) {
		stat(e.second, edges_a2b, ret);
	}
	// 模式：A->B->F
	for (const auto& e : edges_b2f) {
		stat(e.second, edges_a2b, ret);
	}

	return ret;
}

void test() {
	Graph g;
	g.addNode("100", {{std::string("name"), std::string("v100")}});
	g.addNode("101", {{"name", "v101"}});
	g.addNode("102", {});
	g.addNode("1001", {});
	g.addNode("1002", {});
	g.addNode("1003", {});
	g.addNode("1011", {});
	g.addNode("1021", {});
	g.addNode("1032", {});
	g.addNode("1043", {});

	g.addEdge("100", "1001", {{"weight", 1}}, 0);
	g.addEdge("100", "1001", {{"weight", 2}}, 1);
	g.addEdge("100", "1002", {{"weight", 2}}, 0);
	g.addEdge("100", "1003", {{"weight", 3}}, 0);
	g.addEdge("100", "1011", {{"weight", 3}}, 5);

	g.addEdge("101", "1011", {{"weight", 1}}, 0);
	g.addEdge("101", "1021", {{"weight", 2}}, 1);
	g.addEdge("101", "1032", {{"weight", 2}}, 0);
	g.addEdge("101", "1043", {{"weight", 3}}, 0);

	std::cout << "out edges of 100:" << std::endl;
	for (auto& edge : g.getOutEdges("100")) {
		std::cout << "src:" << edge.src_ << ", dst:" << edge.dst_
		          << ", rank:" << edge.rank_
		          << ", values:" << to_string(edge.props_) << std::endl;
	}

	std::cout << "in edges of 1011:" << std::endl;
	for (auto& edge : g.getInEdges("1011")) {
		std::cout << "src:" << edge.src_ << ", dst:" << edge.dst_
		          << ", rank:" << edge.rank_
		          << ", values:" << to_string(edge.props_) << std::endl;
	}

	std::cout << "out vertices of 100:" << std::endl;
	for (auto& id : g.getOutVertices("100")) {
		std::cout << "id:" << id << std::endl;
	}

	std::cout << "in vertices of 1011:" << std::endl;
	for (auto& id : g.getInVertices("1011")) {
		std::cout << "id:" << id << std::endl;
	}
}

int main() {
	test();
	return 0;
}
