#ifndef _TREE_H_
#define _TREE_H_

#include <vector>
#include <float.h>
#include <cmath>

#include "../common/point.h"

using namespace std;

class Tree
{
public:
	Tree();
	~Tree();

	struct TreeNode {
		common::Point position;
		TreeNode* parent, * firstchild, * nextsibling;
		TreeNode() : position(common::Point(2, 0)), parent(nullptr), firstchild(nullptr), nextsibling(nullptr) {};
		TreeNode(int x, int y) : position(common::Point{x, y}), parent(nullptr), firstchild(nullptr), nextsibling(nullptr) {};
	};

	/**
	 * @brief allocate space for the root of the tree, with the postion of the start point
	 * @param the postion of the start point
	 */
	void setRoot(int x, int y);

	/**
	 * @brief add a node to the tree
	 * @param pointer of the new node's parent; position of the new node
	 * @return pointer of the new node
	 */
	Tree::TreeNode* addNode(TreeNode* node_parent, common::Point point_new);

	TreeNode* findNode(common::Point pos);

	/**
	 * @brief get the node that is closest with the given position by traversal
	 * @param position
	 * @return pointer of the closest node 
	 */
	TreeNode* getNearestNode(common::Point pos);

	//TODO(gcx): kd-tree
private:
	TreeNode* root_ = nullptr;
};

Tree::Tree() {}

Tree::~Tree() {}

void Tree::setRoot(int x, int y) {
	root_ = new TreeNode(x, y);
}

Tree::TreeNode* Tree::addNode(TreeNode* node_parent, common::Point point_new) {
	TreeNode* node_new = new TreeNode(point_new.x, point_new.y);
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


Tree::TreeNode* Tree::findNode(common::Point pos) {
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

Tree::TreeNode* Tree::getNearestNode(common::Point pos) {
	TreeNode* cur_node = root_;
	vector<TreeNode*> stack;
	double min_distance = DBL_MAX;
	TreeNode* nearest_node = nullptr;
	//preOrder traverce
	while (cur_node || !stack.empty()) {
		if (cur_node) {
			double dis = sqrt((cur_node->position.x - pos.x) * (cur_node->position.x - pos.x) + (cur_node->position.y - pos.y) * (cur_node->position.y - pos.y));
			if (min_distance > dis) {
				min_distance = dis;
				nearest_node = cur_node;
			}
			stack.emplace_back(cur_node);
			cur_node = cur_node->firstchild;
		}
		else {
			cur_node = stack[stack.size() - 1];
			double dis = sqrt((cur_node->position.x - pos.x) * (cur_node->position.x - pos.x) + (cur_node->position.y - pos.y) * (cur_node->position.y - pos.y));
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