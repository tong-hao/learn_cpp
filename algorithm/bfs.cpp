#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

// bfs
const int kVertexNum = 10000;

struct Graph {
public:
	void addEdge(int src, int dst) {
		auto iter = outEdges.find(src);
		if (iter == outEdges.end()) {
			std::vector<int> edges;
			edges.push_back(dst);
			outEdges.emplace(src, edges);
		} else {
			iter->second.push_back(dst);
		}
	}
	std::vector<int> getAdj(int srcVid) {
		return outEdges[srcVid];
	}
	void print() {
		for (auto& [src, dsts] : outEdges) {
			std::cout << src << ":";
			for (auto& dst : dsts) {
				std::cout << dst << ",";
			}
			std::cout << "\n";
		}
	}

private:
	std::unordered_map<int, std::vector<int>> outEdges;
};
class Bfs {
public:
	Bfs(Graph* g, int start) : graph(g), startVid(start) {
	}

	void init() {
		std::queue<int> q;
		visited[startVid] = true;
		q.push(startVid);

		while (!q.empty()) {
			int vid = q.front();
			q.pop();

			for (int adj : graph->getAdj(vid)) {
				if (!visited[adj]) {
					visited[adj] = true;
					q.push(adj);
					edgeTo[adj] = vid;
				}
			}
		}
	}

	std::stack<int> getPath(int dst) {
		std::stack<int> path;
		if (!visited[dst]) {
			return path;
		}
		for (int vid = dst; vid != startVid; vid = edgeTo[vid]) {
			path.push(vid);
		}
		path.push(startVid);

		return path;
	}

private:
	Graph* graph;
	bool visited[kVertexNum];
	std::unordered_map<int, int> edgeTo;
	int startVid;
};

int main() {
	Graph g;
	g.addEdge(1, 11);
	g.addEdge(1, 12);
	g.addEdge(1, 13);
	g.addEdge(11, 111);
	g.addEdge(11, 112);
	g.addEdge(11, 113);
	g.addEdge(111, 1111);
	g.addEdge(111, 1112);
	g.addEdge(111, 1113);
	g.addEdge(11, 1113);  // for test

	Bfs b(&g, 1);
	b.init();

	auto stack = b.getPath(1113);
	while (!stack.empty()) {
		int v = stack.top();
		stack.pop();
		std::cout << v;
		if (!stack.empty()) {
			std::cout << "->";
		}
	}
	std::cout << "\n";

	// 执行结果: 1->11->1113
	// 说明：
	// 1）构图：上面的图的顶点ID第一层用个位数，第二层用两位。。。
	// 2）为了测试11->1113是特意添加的。
}

// link:-std=c++17 -g