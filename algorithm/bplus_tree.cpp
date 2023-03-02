#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#define maxn 100010
#define maxm 500010
#define maxnode 500010
#define M 5
#define inf 2e9

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

struct Node {
	int key[M + 1];
	int val[M + 1];
	int tag[M + 1];
	int n;
	int son[M + 2];
	int fa;
} node[maxnode];
int cnt;
int root;

void update(int x) {
	int i, j;
	for (i = 1; i <= node[x].n; i++) {
		node[node[x].son[i]].fa = x;
		if (node[x].tag[i] == 0)
			continue;
		node[node[x].son[i]].key[1] = node[x].key[i];
		node[node[x].son[i]].val[1] = node[x].val[i];
		node[node[x].son[i]].tag[1] = 1;
		for (j = 2; j <= node[node[x].son[i]].n; j++) {
			node[node[x].son[i]].key[j] = inf;
			node[node[x].son[i]].val[j] = inf;
			node[node[x].son[i]].tag[j] = 0;
		}
		node[x].tag[i] = 0;
	}
}

void split(int x) {
	int i;
	if (node[x].n == M) {
		update(x);
		int mid = (M + 1) / 2;
		cnt++;
		node[cnt].fa = node[x].fa;
		node[cnt].n = M - mid;
		for (i = 1; i <= M - mid; i++) {
			node[cnt].key[i] = node[x].key[i + mid];
			node[cnt].val[i] = node[x].val[i + mid];
			node[cnt].son[i] = node[x].son[i + mid];
		}
		node[cnt].son[M - mid + 1] = node[x].son[M + 1];
		for (i = 1; i <= M - mid; i++)
			node[cnt].tag[i] = 0;
		node[x].n = mid - 1;
		node[x].son[mid] = cnt;
		if (node[x].fa == 0) {
			root = ++cnt;
			node[root].fa = 0;
			node[root].n = 1;
			node[root].son[1] = x;
			node[root].key[1] = node[x].key[mid];
			node[root].val[1] = node[x].val[mid];
			node[root].tag[1] = 0;
			node[x].fa = root;
		} else {
			int fa = node[x].fa;
			int p = lower_bound(node[fa].key + 1, node[fa].key + node[fa].n + 1,
			                    node[x].key[mid]) -
			        node[fa].key;
			for (i = node[fa].n; i >= p; i--) {
				node[fa].key[i + 1] = node[fa].key[i];
				node[fa].val[i + 1] = node[fa].val[i];
				node[fa].son[i + 1] = node[fa].son[i];
				node[fa].tag[i + 1] = node[fa].tag[i];
			}
			node[fa].key[p] = node[x].key[mid];
			node[fa].val[p] = node[x].val[mid];
			node[fa].son[p] = x;
			node[fa].son[p + 1] = cnt;
			node[fa].n++;
			node[fa].tag[p] = 0;
			node[fa].tag[p + 1] = 0;
			split(fa);
		}
	}
}

void insert(int x, int val) {
	if (node[x].n == 0) {
		node[x].n = 1;
		node[x].key[1] = val;
		node[x].val[1] = val;
		split(x);
	} else {
		int i;
		i = lower_bound(node[x].key + 1, node[x].key + node[x].n + 1, val) -
		    node[x].key;
		if (node[x].key[i] == val) {
			node[x].val[i] = val;
			return;
		}
		node[x].n++;
		for (int j = node[x].n; j > i; j--) {
			node[x].key[j] = node[x].key[j - 1];
			node[x].val[j] = node[x].val[j - 1];
			node[x].son[j + 1] = node[x].son[j];
			node[x].tag[j] = node[x].tag[j - 1];
		}
		node[x].key[i] = val;
		node[x].val[i] = val;
		node[x].son[i] = ++cnt;
		node[x].son[i + 1] = ++cnt;
		node[cnt].n = 0;
		node[cnt].fa = x;
		node[cnt - 1].n = 0;
		node[cnt - 1].fa = x;
		split(x);
	}
}

int find(int x, int val) {
	int i;
	i = lower_bound(node[x].key + 1, node[x].key + node[x].n + 1, val) -
	    node[x].key;
	if (node[x].key[i] == val)
		return node[x].val[i];
	else {
		if (node[x].son[i] == 0)
			return -1;
		return find(node[x].son[i], val);
	}
}

int main() {
	root = ++cnt;
	node[root].n = 0;
	node[root].fa = 0;
	int opt, x;
	while (scanf("%d%d", &opt, &x) != EOF) {
		if (opt == 1)
			insert(root, x);
		else
			printf("%d\n", find(root, x));
	}
	return 0;
}
