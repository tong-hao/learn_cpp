#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

void add_edge(vector<int> vec[], int u, int v) {
	vec[u].push_back(v);
	vec[v].push_back(u);
}

int main() {
	//點個數量
	int v = 6;
	//用vector來存，比較簡單，不用自己去建立Linked List
	vector<int> vec[6];
	//建立圖的部分
	add_edge(vec, 0, 1);
	add_edge(vec, 0, 2);
	add_edge(vec, 0, 3);
	add_edge(vec, 1, 2);
	add_edge(vec, 1, 4);
	add_edge(vec, 2, 5);
	add_edge(vec, 3, 5);
	add_edge(vec, 4, 5);

	//使用iterator印資料
	vector<int>::iterator it;

	//印出陣列
	for (int i = 0; i < v; ++i) {
		cout << i << " : ";
		for (it = vec[i].begin(); it < vec[i].end(); ++it)
			cout << *it << " ";
		cout << endl;
	}
	return 0;
}