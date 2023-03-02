#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Graph {
public:
	int v_count;
	list<int> *adj;

public:
	Graph(int v);
	void addEdge(int v, int w);

	Graph getTranspose();
};

Graph::Graph(int v_count) {
	this->v_count = v_count;
	adj = new list<int>[v_count];
}

Graph Graph::getTranspose() {
	Graph g(v_count);
	for (int i = 0; i < v_count; i++) {
		// Recur for all the vertices adjacent to this vertex
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
			g.adj[*it].push_back(i);
		}
	}
	return g;
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);  // Add w to v’s list.
}

void fillOrder2(Graph &g, int v, bool visited[], stack<int> &s) {
	visited[v] = true;

	for (auto it = g.adj[v].begin(); it != g.adj[v].end(); ++it) {
		std::cout << v << "->" << *it << "\n";
		if (!visited[*it]) {
			fillOrder2(g, *it, visited, s);
		}
	}
	s.push(v);
	std::cout << "push2:" << v << std::endl;
}
void fillOrder3(Graph &g, int v, bool visited[], stack<int> &s) {
	stack<int> dfs;
	dfs.push(v);
	visited[v] = true;
	while (!dfs.empty()) {
		int vertex = dfs.top();
		dfs.pop();
		for (auto it = g.adj[vertex].begin(); it != g.adj[vertex].end(); ++it) {
			if (!visited[*it]) {
				dfs.push(*it);
				visited[*it] = true;
			}
		}
		s.push(vertex);
		std::cout << "push2:" << vertex << std::endl;
	}
}

void fillOrder(Graph &g, int v, bool visited[], stack<int> &s) {
	stack<int> dfs;
	dfs.push(v);
	std::stack<int> s2;
	while (!dfs.empty()) {
		int vertex = dfs.top();
		dfs.pop();
		// std::cout << "vertex:" << vertex << std::endl;
		if (visited[vertex]) {
			continue;
		}
		visited[vertex] = true;
		bool hasNonVisited = false;
		for (auto it = g.adj[vertex].begin(); it != g.adj[vertex].end(); ++it) {
			if (!visited[*it]) {
				hasNonVisited = true;
				dfs.push(*it);
			}
		}

		if (hasNonVisited) {
			s2.push(vertex);
		} else {
			s.push(vertex);
			// std::cout << "push:" << vertex << std::endl;
		}
	}
	while (!s2.empty()) {
		int vertex = s2.top();
		s2.pop();
		s.push(vertex);  // 这里有问题
		                 // std::cout << "push:" << vertex << std::endl;
	}
}

void dfsUtil2(Graph &g, int v, bool visited[], int label) {
	visited[v] = true;
	cout << v << "," << label << "\n";

	for (auto it = g.adj[v].begin(); it != g.adj[v].end(); ++it) {
		if (!visited[*it]) {
			dfsUtil2(g, *it, visited, label);
		}
	}
}

// void dfsUtil(Graph &g, int v, bool visited[], int label) {
// 	stack<int> dfs;
// 	dfs.push(v);
// 	visited[v] = true;
// 	cout << v << "," << label << "\n";

// 	while (!dfs.empty()) {
// 		int vertex = dfs.top();
// 		dfs.pop();
// 		for (auto it = g.adj[vertex].begin(); it != g.adj[vertex].end(); ++it) {
// 			if (!visited[*it]) {
// 				dfs.push(*it);
// 				visited[*it] = true;
// 				cout << *it << "," << label << "\n";
// 			}
// 		}
// 	}
// }

void dfsUtil(Graph &g, int v, bool visited[], int label) {
	stack<int> dfs;
	dfs.push(v);
	// visited[v] = true;
	// cout << v << "," << label << "\n";

	while (!dfs.empty()) {
		int vertex = dfs.top();
		dfs.pop();
		if (visited[vertex]) {
			continue;
		}
		visited[vertex] = true;
		cout << vertex << "," << label << "\n";
		for (auto it = g.adj[vertex].begin(); it != g.adj[vertex].end(); ++it) {
			if (!visited[*it]) {
				dfs.push(*it);
			}
		}
	}
}

void calcSCC(Graph &g) {
	std::stack<int> stack;

	bool *visited = new bool[g.v_count];
	for (int i = 0; i < g.v_count; i++)
		visited[i] = false;

	// first dfs
	std::cout << "first dfs" << std::endl;
	for (int i = 0; i < g.v_count; i++) {
		if (!visited[i]) {
			fillOrder(g, i, visited, stack);
		}
	}

	// reset visited
	Graph gr = g.getTranspose();
	for (int i = 0; i < g.v_count; i++)
		visited[i] = false;

	// second dfs
	std::cout << "second dfs" << std::endl;
	int wcc_count = 0;
	while (stack.empty() == false) {
		int v = stack.top();
		stack.pop();

		if (!visited[v]) {
			int label = v;
			wcc_count++;
			dfsUtil(gr, v, visited, label);
		}
	}
	std::cout << "community num:" << wcc_count << std::endl;
}

std::istream &safe_get_line(std::istream &is, std::string &t) {
	t.clear();
	std::istream::sentry se(is, true);
	std::streambuf *sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case std::streambuf::traits_type::eof():
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += (char)c;
		}
	}
}

void split(const std::string &line, std::vector<std::string> &ret,
           const std::string &token) {
	std::string::size_type pos1, pos2;
	size_t len = line.length();
	pos2 = line.find(token);
	pos1 = 0;
	while (std::string::npos != pos2) {
		ret.emplace_back(line.substr(pos1, pos2 - pos1));

		pos1 = pos2 + token.size();
		pos2 = line.find(token, pos1);
	}
	if (pos1 != len)
		ret.emplace_back(line.substr(pos1));
}

void csv_parser(std::ifstream &fin, Graph &g) {
	std::string line;
	int line_count = 0;
	while (fin.good() && (false == fin.eof())) {
		safe_get_line(fin, line);
		line_count++;
		if (line_count % 1000000 == 0) {
			std::cout << "parse, line:" << line_count << std::endl;
		}
		if (fin.fail() || ('\0' == line[0])) {
			continue;
		}
		std::vector<std::string> columns;
		columns.reserve(2);
		split(line, columns, ",");
		g.addEdge(stoi(columns[0]), stoi(columns[1]));
	}
}

// scc_kosaraju
int main(int argc, char const *argv[]) {
	Graph g(8);  // 4847571 这点不好

	for (int i = 0; i < argc; i++) {
		std::cout << "arg:" << argv[i] << std::endl;
	}

	std::ifstream ifs;
	ifs.open(argv[1], std::ifstream::in);
	csv_parser(ifs, g);
	calcSCC(g);
	return 0;
}
