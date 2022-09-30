#ifndef _TREE_H_
#define _TREE_H_

#include <vector>
#include <float.h>
using namespace std;

class Tree
{
public:
	Tree();
	~Tree();

	struct TreeNode {
		vector<int> position;
		TreeNode* parent, * firstchild, * nextsibling;
		TreeNode() : position(vector<int>(2, 0)), parent(nullptr), firstchild(nullptr), nextsibling(nullptr) {};
		TreeNode(int x, int y) : position(vector<int>{x, y}), parent(nullptr), firstchild(nullptr), nextsibling(nullptr) {};
	};
	void setRoot(int x, int y);
	Tree::TreeNode* addNode(TreeNode* node_parent, vector<int> point_new);
	TreeNode* findNode(vector<int> pos);
	TreeNode* getNearestNode(vector<int> pos);

private:
	TreeNode* root_ = nullptr;
};

Tree::Tree() {}

Tree::~Tree() {}

void Tree::setRoot(int x, int y) {
	root_ = new TreeNode(x, y);
}

Tree::TreeNode* Tree::addNode(TreeNode* node_parent, vector<int> point_new) {
	TreeNode* node_new = new TreeNode(point_new[0], point_new[1]);
	if (!node_parent->firstchild) {
		node_parent->firstchild = node_new;
		node_new->parent = node_parent;
	}
	else {
		TreeNode* sibling = node_parent->firstchild;
		while (sibling->nextsibling) {
			sibling = sibling->nextsibling;
		}
		sibling->nextsibling = node_new;
		node_new->parent = sibling;
	}
	return node_new;
}


Tree::TreeNode* Tree::findNode(vector<int> pos) {
	TreeNode* cur_node = root_;
	vector<TreeNode*> stack;
	//preOrder traverce
	while (cur_node || !stack.empty()) {
		if (cur_node) {
			stack.emplace_back();
			cur_node = cur_node->firstchild;
		}
		else {
			cur_node = stack[stack.size()-1];
			stack.pop_back();
			cur_node = cur_node->nextsibling;
		}

		if (cur_node->position == pos) {
			break;
		}
	}
	return cur_node;
}

Tree::TreeNode* Tree::getNearestNode(vector<int> pos) {
	TreeNode* cur_node = root_;
	vector<TreeNode*> stack;
	double min_distance = DBL_MAX;
	TreeNode* nearest_node = nullptr;
	//preOrder traverce
	while (cur_node || !stack.empty()) {
		if (cur_node) {
			double dis = sqrt((cur_node->position[0] - pos[0]) * (cur_node->position[0] - pos[0]) + (cur_node->position[1] - pos[1]) * (cur_node->position[1] - pos[1]));
			if (min_distance > dis) {
				min_distance = dis;
				nearest_node = cur_node;
			}
			stack.emplace_back(cur_node);
			cur_node = cur_node->firstchild;
		}
		else {
			cur_node = stack[stack.size() - 1];
			double dis = sqrt((cur_node->position[0] - pos[0]) * (cur_node->position[0] - pos[0]) + (cur_node->position[1] - pos[1]) * (cur_node->position[1] - pos[1]));
			if (min_distance > dis) {
				min_distance = dis;
				nearest_node = cur_node;
			}
			stack.pop_back();
			cur_node = cur_node->nextsibling;
		}

	}
	return nearest_node;
}

#endif // !_TREE_H_