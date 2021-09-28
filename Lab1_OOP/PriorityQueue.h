#include <iostream>

using namespace std;

enum Colors
{
	BLACK,
	RED,
};


template<typename T>
class PriorityQueue {
private:
	class Node {
	public:
		T data;
		Node* parent, *left, *right; 
		Colors color; 
		Node(T data = T())
		{
			this->data = data;
			left = right = parent = nullptr;
			color = BLACK;
		}
	};

	Node* root;
	 Node * TNULL;

	//void initializeNULLNode(Node* node, Node* parent) {
	//	node->data = T();
	//	node->parent = parent;
	//	node->left = nullptr;
	//	node->right = nullptr;
	//	node->color = BLACK;
	//}

	Node* searchTreeHelper(Node* node, T key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	void fixDelete(Node* x) {
		Node* s;
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == RED) {
					// case 3.1
					s->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == BLACK && s->right->color == BLACK) {
					// case 3.2
					s->color = RED;
					x = x->parent;
				}
				else {
					if (s->right->color == BLACK) {
						// case 3.3
						s->left->color = BLACK;
						s->color = RED;
						rightRotate(s);
						s = x->parent->right;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == RED) {
					// case 3.1
					s->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == BLACK && s->left->color == BLACK) {
					// case 3.2
					s->color = RED;
					x = x->parent;
				}
				else {
					if (s->left->color == BLACK) {
						// case 3.3
						s->right->color = BLACK;
						s->color = RED;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = BLACK;
					s->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	void rbTransplant(Node* u, Node* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(Node* node, T key) {
		Node* z = TNULL;
		Node* x, *y;
		while (node != TNULL) {
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout << "Couldn't find key in the tree" << endl;
			return;
		}

		y = z;
		Colors y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == BLACK) {
			fixDelete(x);
		}
	}

	void fixInsert(Node* k) {
		Node* u;
		while (k->parent->color == RED) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == RED) {
					// case 3.1
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u->color == RED) {
					// mirror case 3.1
					u->color = BLACK;
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = BLACK;
	}

	void printHelper(Node* root, string indent, bool last) {
		if (root != TNULL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			}
			else {
				cout << "L----";
				indent += "|    ";
			}

			string sColor = root->color ? "RED" : "BLACK";
			cout << root->data << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

	void leftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	Node* searchTree(T k) {
		return searchTreeHelper(this->root, k);
	}

	Node* minimum(Node* node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	Node* maximum(Node* node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}


	void deleteNode(T data) {
		deleteNodeHelper(this->root, data);
	}
public:
	PriorityQueue() 
	{
		TNULL = new Node;
		TNULL->color = BLACK;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	~PriorityQueue() {
		while (root != TNULL) pop();
		root = nullptr;
		delete root;
		
	}
	
	void push(const T& key) {
		Node* node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = RED;

		Node* y = nullptr;
		Node* x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		
		if (node->parent == nullptr) {
			node->color = BLACK;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}


		fixInsert(node);
	}

	bool empty()
	{
		if (root == TNULL)
			return true;
		return false;
	}

	const T& top()
	{
		if (!empty())
			return this->maximum(root)->data;
		else
			exit(-1);
	}

	void pop()
	{
		if(!empty())
			deleteNode(top());
		return;
	}

	void print() {
		if (root) {
			printHelper(this->root, "", true);
		}
	}

};
