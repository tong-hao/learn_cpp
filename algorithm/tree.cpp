
#include <iostream>
#include <queue>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int v) : val(v) {
	}
};

void print(TreeNode *r) {
	if (r == nullptr)
		return;

	std::queue<TreeNode *> q;
	q.push(r);

	while (!q.empty()) {
		auto *cur = q.front();
		q.pop();
		std::cout << cur->val << std::endl;

		if (cur->left != nullptr) {
			q.push(cur->left);
		}
		if (cur->right != nullptr) {
			q.push(cur->right);
		}
	}
}

int main(int argc, char const *argv[]) {
	TreeNode *n1 = new TreeNode(1);
	TreeNode *n11 = new TreeNode(11);
	TreeNode *n12 = new TreeNode(12);
	TreeNode *n111 = new TreeNode(111);
	TreeNode *n112 = new TreeNode(112);
	TreeNode *n121 = new TreeNode(121);
	TreeNode *n122 = new TreeNode(122);

	n1->left = n11;
	n1->right = n12;
	n11->left = n111;
	n11->right = n112;
	n12->left = n121;
	n12->right = n122;

	print(n1);

	return 0;
}

// link: -std=c++11
