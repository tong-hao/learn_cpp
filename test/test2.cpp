#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
	TreeNode(TreeNode* l, TreeNode* r, int v) : left(l), right(r), value(v) {
	}

	int value;
	TreeNode* left;
	TreeNode* right;
};
void LevelOrder(TreeNode* root, std::vector<int>* res) {
	res->clear();
	if (root == nullptr)
		return;
	std::queue<TreeNode*> cache;
	cache.push(root);

	int i = 0;
	while (!cache.empty()) {
		i++;
		TreeNode* cur = cache.front();
		cache.pop();
		res->push_back(cur->value);
		std::cout << "res push back:" << cur->value << std::endl;
		if (cur->right) {
			cache.push(cur->right);
		}
		if (cur->left) {
			cache.push(cur->left);
		}
		if (i > 10) {
			break;
		}
	}
}

TreeNode* LevelOrder2(TreeNode* root, std::vector<int>* res) {
	if (root == nullptr) {
		return nullptr;
	}

	res->push_back(root->value);
	TreeNode* right = nullptr;
	TreeNode* left = nullptr;
	if (root->right) {
		right = LevelOrder2(root->right, res);
	}
	if (root->left) {
		left = LevelOrder2(root->left, res);
	}

	if (right) {
		res->push_back(right->value);
	}
	if (left) {
		res->push_back(left->value);
	}
	return root;
}

void printQueue(std::queue<TreeNode*>& cache) {
}

int main(int argc, char const* argv[]) {
	TreeNode* n111 = new TreeNode(nullptr, nullptr, 111);
	TreeNode* n112 = new TreeNode(nullptr, nullptr, 112);
	TreeNode* n11 = new TreeNode(n111, n112, 11);

	TreeNode* n121 = new TreeNode(nullptr, nullptr, 121);
	TreeNode* n122 = new TreeNode(nullptr, nullptr, 122);
	TreeNode* n12 = new TreeNode(n121, n122, 12);
	TreeNode* n1 = new TreeNode(n11, n12, 1);

	std::vector<int> res;
	LevelOrder2(n1, &res);

	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << " ";
	}

	return 0;
}
