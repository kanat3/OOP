#include <iostream>
#pragma once	

enum COLOR { RED, BLACK };


template <typename T1, typename T2>
class Node {
public:

	T1 key;
	T2 data;
	COLOR color;
	Node<T1, T2>* left, * right, * parent;

	Node(T1 key, T2 data) : key(key), data(data) {
		parent = left = right = nullptr;
		color = RED;
	}
	~Node() = default;
	// returns pointer to uncle 
	Node<T1, T2>* uncle() {
		// If no parent or grandparent, then no uncle 
		if (parent == nullptr || parent->parent == nullptr)
			return nullptr;
		if (parent->isOnLeft())
			// uncle on right 
			return parent->parent->right;
		else
			// uncle on left 
			return parent->parent->left;
	}
	// check if node is left child of parent 
	bool isOnLeft() { return this == parent->left; }
	// returns pointer to sibling 
	Node<T1, T2>* sibling() {
		// sibling nullptr if no parent 
		if (parent == nullptr)
			return nullptr;
		if (isOnLeft())
			return parent->right;
		return parent->left;
	}
	// moves node down and moves given node in its place 
	void moveDown(Node<T1, T2>* nParent) {
		if (parent != nullptr) {
			if (isOnLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}
	bool has0Child() {
		return (left != nullptr && left->color == 0) ||
			(right != nullptr && right->color == 0);
	}
};