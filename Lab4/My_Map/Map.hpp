#include <iostream>
#include "Node.h"
#include "NormalList.h"

template<typename T1, typename T2>
class Map_Iterator {
public:
    Node <T1, T2>* _node;
    Node <T1, T2>* root;
    Map_Iterator() { _node = root = nullptr; };
    Map_Iterator(Node <T1, T2>* a, Node <T1, T2>* b) {
        _node = a; root = b;
    }
    bool operator != (Map_Iterator<T1, T2> b) {
        return this->_node != b._node;
    }
    bool operator == (Map_Iterator<T1, T2> b) {
        return this->_node == b._node;
    }
    Map_Iterator<T1, T2> operator++ (void) {
		if (_node->right != nullptr) {
				_node = _node->right;
				while (_node->left != nullptr)
						_node = _node->left;
				return *this;
		}
		else {
			Node<T1, T2>* q = root;
			Node<T1, T2>* suc = nullptr;

			while (q != nullptr) {		
				if (q->key > _node->key) {
						suc = q;
						q = q->left;
				}
				else if (q->key < _node->key)
						q = q->right;
				else		
						break;
			}
			_node = suc;
			return *this;

		}
    }
    const Map_Iterator<T1, T2> operator++ (int) {
        Map_Iterator<T1, T2> obj = *this;
        if (_node->right != nullptr) {
                _node = _node->right;
                while (_node->left != nullptr)
                        _node = _node->left;
                return obj;
        }
        else {
            Node<T1, T2>* q = root;
            Node<T1, T2>* suc = nullptr;

            while (q != nullptr) {		
                if (q->key > _node->key) {
                        suc = q;
                        q = q->left;
                }
                else if (q->key < _node->key)
                        q = q->right;
                else		
                        break;
            }
            _node = suc;
            return obj;

        }
    }
};

template<typename T1, typename T2>
class Map {
public:
    typedef Map_Iterator<T1, T2> iterator;
    iterator m_begin() const {
        iterator it;
        it._node = root;
        while (it._node->left != nullptr)
                it._node = it._node->left;
        it.root = root;
        return it;
    }
    iterator m_end() const {
        iterator it;
        it._node = root;
        while(it._node != NULL){
            it._node = it._node->right;
        }
        it.root = root;

        return it;
    }
	iterator m_find (T1 x) const {
		Node<T1, T2>* tmp = root;

		while (tmp != NULL) {
			if (tmp->key < x)
					tmp = tmp->right;
			else if (tmp->key > x)
					tmp = tmp->left;
			else
					break;
		}
		return iterator(tmp, root);
	}
private:
	Node <T1, T2>* root;
private:
	void leftRotate(Node<T1, T2>* x) {
		Node <T1, T2>* nParent = x->right;
		if (x == root)
			root = nParent;
		x->moveDown(nParent);
		x->right = nParent->left;
		if (nParent->left != nullptr)
			nParent->left->parent = x;
		nParent->left = x;
	}

	void rightRotate(Node<T1, T2>* x) {
		Node<T1, T2>* nParent = x->left;
		if (x == root)
			root = nParent;
		x->moveDown(nParent);
		x->left = nParent->right;
		if (nParent->right != nullptr)
			nParent->right->parent = x;
		nParent->right = x;
	}

	void swapColors(Node<T1, T2>* x1, Node<T1, T2>* x2) {
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapkeyues(Node<T1, T2>* u, Node<T1, T2>* v) {
		int temp;
		temp = u->key;
		u->key = v->key;
		v->key = temp;
	}


	void fixRedRed(Node<T1, T2>* newElement) {
		if (newElement == root) {
			newElement->color = BLACK;
			return;
		}
		Node<T1, T2>* parent = newElement->parent, * grandparent = parent->parent,
			* uncle = newElement->uncle();
		if (parent->color != 1) {
			if (uncle != nullptr && uncle->color == 0) {
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			}
			else {
				// Else perform LR, LL, RL, RR 
				if (parent->isOnLeft()) {
					if (newElement->isOnLeft()) {
						// for left right 
						swapColors(parent, grandparent);
					}
					else {
						leftRotate(parent);
						swapColors(newElement, grandparent);
					}
					// for left left and left right 
					rightRotate(grandparent);
				}
				else {
					if (newElement->isOnLeft()) {
						// for right left 
						rightRotate(parent);
						swapColors(newElement, grandparent);
					}
					else {
						swapColors(parent, grandparent);
					}
					// for right right and right left 
					leftRotate(grandparent);
				}
			}
		}
	}

	Node<T1, T2>* successor(Node<T1, T2>* x) {
		Node<T1, T2>* temp = x;
		while (temp->left != nullptr)
			temp = temp->left;
		return temp;
	}

	Node<T1, T2>* BSTreplace(Node<T1, T2>* x) {
		if (x->left != nullptr && x->right != nullptr)
			return successor(x->right);
		if (x->left == nullptr && x->right == nullptr)
			return nullptr;
		if (x->left != nullptr)
			return x->left;
		else
			return x->right;
	}

	void deleteNode(Node<T1, T2>* v) {
		Node<T1, T2>* u = BSTreplace(v);
		// True when u and v are both 1 
		bool uv1 = ((u == nullptr || u->color == 1) && (v->color == 1));
		Node<T1, T2>* parent = v->parent;
		if (u == nullptr) {
			// u is nullptr therefore v is leaf 
			if (v == root) {
				// v is root, making root nullptr 
				root = nullptr;
			}
			else {
				if (uv1) {
					// u and v both black 
					// v is leaf, fix double black at v 
					fixDoubleBlack(v);
				}
				else {
					// u or v is 0 
					if (v->sibling() != nullptr)
						// sibling is not nullptr, make it 0" 
						v->sibling()->color = RED;
				}
				// delete v from the tree 
				if (v->isOnLeft()) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			delete v;
			return;
		}
		if (v->left == nullptr || v->right == nullptr) {
			// v has 1 child 
			if (v == root) {
				// v is root, assign the keyue of u to v, and delete u 
				v->key = u->key;
				v->left = v->right = nullptr;
				delete u;
			}
			else {
				// Detach v from tree and move u up 
				if (v->isOnLeft()) {
					parent->left = u;
				}
				else {
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uv1) {
					// u and v both 1, fix double 1 at u 
					fixDoubleBlack(u);
				}
				else {
					// u or v 0, color u 1 
					u->color = BLACK;
				}
			}
			return;
		}
		// v has 2 children, swap keyues with successor and recurse 
		swapkeyues(u, v);
		deleteNode(u);
	}

	void fixDoubleBlack(Node<T1, T2>* x) {
		if (x == root)
			// Reached root 
			return;
		Node<T1, T2>* sibling = x->sibling(), * parent = x->parent;
		if (sibling == nullptr) {
			// No sibiling, double black pushed up 
			fixDoubleBlack(parent);
		}
		else {
			if (sibling->color == 0) {
				// Sibling red
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) {
					// left case 
					rightRotate(parent);
				}
				else {
					// right case 
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else {
				// Sibling 1 
				if (sibling->has0Child()) {
					// at least 1 0 children 
					if (sibling->left != nullptr && sibling->left->color == 0) {
						if (sibling->isOnLeft()) {
							// left left 
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else {
							// right left 
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else {
						if (sibling->isOnLeft()) {
							// left right 
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else {
							// right right 
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else {
					// 2 1 children 
					sibling->color = RED;
					if (parent->color == 1)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

public:

	Map() { root = nullptr; }
	~Map() { clear(root); 
	root = nullptr;
	};

	Node<T1, T2>* getRoot() { return root; }
	Node<T1, T2>* find(T1 n) {
		Node<T1, T2>* temp = root;
		while (temp != nullptr) {
			if (n < temp->key) {
				if (temp->left == nullptr)
					break;
				else
					temp = temp->left;
			}
			else if (n == temp->key) {
				break;
			}
			else {
				if (temp->right == nullptr)
					break;
				else
					temp = temp->right;
			}
		}
		return temp;
	}


	void insert(T1 key, T2 data) {
		Node<T1, T2>* newNode = new Node<T1, T2>(key, data);
		if (root == nullptr) {
			newNode->color = BLACK;
			root = newNode;
		}
		else {
			Node<T1, T2>* temp = find(key);
			if (temp->key == key) {
				temp->data= temp->data+1;
				return;
			}
			newNode->parent = temp;
			if (key < temp->key)
				temp->left = newNode;
			else
				temp->right = newNode;
			fixRedRed(newNode);
		}
	}

	void remove(T1 n) {
		if (root == nullptr)
			// Tree is empty 
			return;
		Node<T1, T2>* v = find(n), * u;
		if (v->key != n) {
			std::cout << "No Node<T1, T2> found to delete with keyue:" << n << std::endl;
			return;
		}
		deleteNode(v);
	}


	void print(Node<T1, T2>* root, int lvl)
	{
		if (root != nullptr)
		{
			print(root->right, lvl + 2);
			for (int i = 0; i < lvl; i++)
			{
				std::cout << "  ";
			}
			if (root->parent != nullptr && root->parent->key >= root->key)
			{
				if (root->color == 0)
					std::cout << "r"; //SetColor(12, 0);
				else
					std::cout << "b"; //SetColor(9, 0);
				std::cout << "\\" << root->data;	
				std::cout << std::endl;
			}
			else if (root->parent != nullptr && root->parent->key < root->key)
			{
				if (root->color == 0)
					std::cout << "r";
				else
					std::cout << "b";
				std::cout << "/" << root->data;
				std::cout << std::endl;
			}
			else
			{
				std::cout << "b";
				std::cout << root->data;
			}
			std::cout << std::endl;
			print(root->left, lvl + 2);
		}
	}


	List<T1>* getListKey(Node<T1, T2>* root, List<T1>* A)
	{
		if (root)
		{
			getListKey(root->left, A);
			getListKey(root->right, A);
			A->push_back(root->key);
		}
		return A;
	}

	List<T2>* getListData(Node<T1, T2>* root, List<T2>* A)
	{
		if (root)
		{
			getListData(root->left, A);
			getListData(root->right, A);
			A->push_back(root->data);

		}
		return A;
	}
	
	void printListKey(List<T1>* list)
	{
		while (!list->isEmpty())
		{
			std::cout << list->at(0);
			std::cout << std::endl;
			list->pop_front();
		}
	}

	void printListData(List<T2>* list)
	{
		while (!list->isEmpty())
		{
			std::cout << list->at(0);
			std::cout << std::endl;
			list->pop_front();
		}
	}

	void clear(Node<T1,T2>* root)
	{
		if (root)
		{
			clear(root->left);
			clear(root->right);
			delete root;
		}
	}
};

