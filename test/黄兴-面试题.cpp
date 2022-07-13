struct TreeNode {
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
	while (!cache.empty()) {
		TreeNode* cur = cache.front();
		cache.pop();
		res->push_back(cur->value);
		if (root->right) {
			cache.push(root->right);
		}
		if (root->left) {
			cache.push(root->left);
		}
	}
}

TreeNode* LevelOrder(TreeNode* root, std::vector<int>* res) {
	if (root == nullptr) {
		return nullptr;
	}

	res->push_back(root->value);
	TreeNode* right = nullptr;
	TreeNode* left = nullptr;
	if (root->right) {
		right = LevelOrder(root->right, res);
	}
	if (root->left) {
		left = LevelOrder(root->left, res);
	}

	if (right) {
		res->push_back(right->value);
	}
	if (left) {
		res->push_back(left->value);
	}
	return root;
}
