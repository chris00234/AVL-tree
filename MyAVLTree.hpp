#ifndef __PROJ_FOUR_AVL_HPP
#define __PROJ_FOUR_AVL_HPP

#include "runtimeexcept.hpp"
#include <iostream>
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException
{
public:
	ElementNotFoundException(const std::string& err) : RuntimeException(err) {}
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	struct Node 
	{
		Node* left = nullptr;
		Node* right = nullptr;
		Key k{};
		Value v{};
		Node* parent = nullptr;
	};
	Node* root;
	void pre_order_traversal(Node* tmp, std::vector<Key>& vec) const
	{
		if (tmp == nullptr)
			return;
		vec.push_back(tmp->k);
		pre_order_traversal(tmp->left, vec);
		pre_order_traversal(tmp->right, vec);
	}
	void in_order_traversal(Node* tmp, std::vector<Key>& vec) const
	{
		if (tmp == nullptr)
			return;
		in_order_traversal(tmp->left, vec);
		vec.push_back(tmp->k);
		in_order_traversal(tmp->right, vec);
	}
	void post_order_traversal(Node* tmp, std::vector<Key>& vec) const
	{
		if (tmp == nullptr)
			return;
		post_order_traversal(tmp->left, vec);
		post_order_traversal(tmp->right, vec);
		vec.push_back(tmp->k);
	}

	void get_size(Node* tmp, size_t& n) const
	{
		if (tmp == nullptr)
			return;
		n++;
		get_size(tmp->left, n);
		get_size(tmp->right, n);
	}
	void find_key(Node* tmp, Node* find, Key key)
	{
		if (tmp == nullptr)
			return;
		if (key == tmp->Key)
			find = tmp;
		pre_order_traversal(tmp->left);
		pre_order_traversal(tmp->right);
	}
	void destruct_tree(Node* tmp)
	{
		// base case: returns if tmp doesn't hold a node
		if (tmp == nullptr)
			return;

		// recursive cases: uses post-order traversal to delete three properly.
		destruct_tree(tmp->left);
		destruct_tree(tmp->right);
		delete tmp;
	}

	Node* regular_insert(const Key& k, const Value& v)
	{
		Node* tmp = root;
		Node* prev = tmp;
		if (isEmpty())
		{
			root = new Node;
			root->k = k;
			root->v = v;
			return root;
		}
		while (tmp != nullptr)
		{
			prev = tmp;
			if (k < tmp->k)
			{
				tmp = tmp->left;
				if (tmp == nullptr)
				{
					tmp = new Node;
					tmp->k = k;
					tmp->v = v;
					prev->left = tmp;
					tmp->parent = prev;
					return tmp;
				}
			}
			else if (k > tmp->k)
			{
				tmp = tmp->right;
				if (tmp == nullptr)
				{
					tmp = new Node;
					tmp->k = k;
					tmp->v = v;
					prev->right = tmp;
					tmp->parent = prev;
					return tmp;
				}
			}
		}
	}

	//should do -1 when calc
	int get_height(Node* node)
	{
		if (node== nullptr)
		{
			return -1;
		}
		else
		{
			int left_height = get_height(node->left);
			int right_height = get_height(node->right);

			if (left_height >= right_height)
			{
				return left_height + 1;
			}
			else
				return right_height + 1;
		}
	}
	
	bool balanced(Node* node)
	{
		if (get_height(node->left) - get_height(node->right) ==  -1 || get_height(node->left) - get_height(node->right) == 1 || get_height(node->left) - get_height(node->right) == 0)
			return true;
		return false;
	}

	void rotate(Node* z, Node* y, Node* x)
	{
		Node* t0 = nullptr;
		Node* t1 = nullptr;
		Node* t2 = nullptr;
		Node* t3 = nullptr;
		if (z->k < y->k && z->k < x->k)
		{
			t0 = z->left;
			if (y->k < x->k)
			{
				t1 = y->left;
				t2 = x->left;
				t3 = x->right;
				if (z->parent != nullptr)
				{
					if (z->parent->k < z->k)
					{
						z->parent->right = y;
						y->parent = z->parent;
					}
					else if (z->parent->k > z->k)
					{
						z->parent->left = y;
						y->parent = z->parent;
					}
				}
				else
				{
					root = y;
					y->parent = nullptr;
				}
				y->left = z;
				z->parent = y;
				y->right = x;
				x->parent = y;
				z->left = t0;
				if(t0 != nullptr)
					t0->parent = z;
				z->right = t1;
				if (t1 != nullptr)
					t1->parent = z;
				x->left = t2;
				if (t2 != nullptr)
					t2->parent = x;
				x->right = t3;
				if (t3 != nullptr)
					t3->parent = x;
			}
			if (x->k < y->k)
			{
				t1 = x->left;
				t2 = x->right;
				t3 = y->right;
				if (z->parent != nullptr)
				{
					if (z->parent->k < z->k)
					{
						z->parent->right = x;
						x->parent = z->parent;
					}
					else if (z->parent->k > z->k)
					{
						z->parent->left = x;
						x->parent = z->parent;
					}
				}
				else
				{
					root = x;
					x->parent = nullptr;
				}
				x->left = z;
				z->parent = x;
				x->right = y;
				y->parent = x;
				z->left = t0;
				if (t0 != nullptr)
					t0->parent = z;
				z->right = t1;
				if (t1 != nullptr)
					t1->parent = z;
				y->left = t2;
				if (t2 != nullptr)
					t2->parent = y;
				y->right = t3;
				if (t3 != nullptr)
					t3->parent = y;
			}
		}
		else if (z->k > y->k && z->k > x->k)
		{
			t3 = z->right;
			if (y->k > x->k)
			{
				t0 = x->left;
				t1 = x->right;
				t2 = y->right;
				if (z->parent != nullptr)
				{
					if (z->parent->k < z->k)
					{
						z->parent->right = y;
						y->parent = z->parent;
					}
					else if (z->parent->k > z->k)
					{
						z->parent->left = y;
						y->parent = z->parent;
					}
				}
				else
				{
					root = y;
					y->parent = nullptr;
				}

				y->right = z;
				z->parent = y;
				y->left = x;
				x->parent = y;
				x->left = t0;
				if (t0 != nullptr)
					t0->parent = x;
				x->right = t1;
				if (t1 != nullptr)
					t1->parent = x;
				z->left = t2;
				if (t2 != nullptr)
					t2->parent = z;
				z->right = t3;
				if (t3 != nullptr)
					t3->parent = z;
			}
			else if (x->k > y->k)
			{
				t0 = y->left;
				t1 = x->left;
				t2 = x->right;
				if (z->parent != nullptr)
				{
					if (z->parent->k < z->k)
					{
						z->parent->right = x;
						x->parent = z->parent;
					}
					else if (z->parent->k > z->k)
					{
						z->parent->left = x;
						x->parent = z->parent;
					}
				}
				else
				{
					root = x;
					x->parent = nullptr;
				}
				x->left = y;
				y->parent = x;
				x->right = z;
				z->parent = x;
				y->left = t0;
				if (t0 != nullptr)
					t0->parent = y;
				y->right = t1;
				if (t1 != nullptr)
					t1->parent = y;
				z->left = t2;
				if (t2 != nullptr)
					t2->parent = z;
				z->right = t3;
				if (t3 != nullptr)
					t3->parent = z;
			}
		}
	}
	


public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key& k) const noexcept;

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value& find(const Key& k);
	const Value& find(const Key& k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key& k, const Value& v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


};


template<typename Key, typename Value>
MyAVLTree<Key, Value>::MyAVLTree() : root(nullptr) {}

template<typename Key, typename Value>
MyAVLTree<Key, Value>::~MyAVLTree()
{
	destruct_tree(root);
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	size_t n = 0;
	Node* tmp = root;
	get_size(tmp, n);
	return n;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	if (root == nullptr)
	{
		return true;
	}
	return false;
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key& k) const noexcept
{
	if (isEmpty())
		return false;
	Node* tracker = root;
	while (tracker != nullptr)
	{
		if (k == tracker->k)
		{
			return true;
		}
		else if (k < tracker->k)
		{
			tracker = tracker->left;
		}
		else
		{
			tracker = tracker->right;
		}
		
	}
	return false;
}



template<typename Key, typename Value>
Value& MyAVLTree<Key, Value>::find(const Key& k)
{
	if (!contains(k))
	{
		throw ElementNotFoundException("No element in tree");
	}
	Node* tracker = root;
	while (tracker != nullptr)
	{
		if (k == tracker->k)
		{
			break;
		}
		else if (k < tracker->k)
		{
			tracker = tracker->left;
		}
		else
		{
			tracker = tracker->right;
		}

	}
	return tracker->v; // not only a stub, but a terrible idea.
}

template<typename Key, typename Value>
const Value& MyAVLTree<Key, Value>::find(const Key& k) const
{
	if (!contains(k))
	{
		throw ElementNotFoundException("No element in tree");
	}
	Node* tracker = root;
	while (tracker != nullptr)
	{
		if (k == tracker->k)
		{
			break;
		}
		else if (k < tracker->k)
		{
			tracker = tracker->left;
		}
		else
		{
			tracker = tracker->right;
		}

	}
	return tracker->v; // not only a stub, but a terrible idea.
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key& k, const Value& v)
{
	Node* inserted;
	Node* z;
	Node* y;
	Node* x;
	inserted = regular_insert(k, v);  // regular bst
	Node* tmp = inserted;
	while (tmp->parent != nullptr)
	{
		tmp = tmp->parent;
		if (!balanced(tmp))
		{
			z = tmp;
			//std::cout <<"unbalance at " << z->k << std::endl;
			if (get_height(z->left) > get_height(z->right))
				y = z->left;
			else
				y = z->right;
			while (inserted->parent != y)
			{
				inserted = inserted->parent;
			}
			x = inserted;
			rotate(z, y, x);
			break;
		}
	}

	return;
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
	Node* tmp = root;
	in_order_traversal(tmp, foo);
	return foo;
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
	Node* tmp = root;
	pre_order_traversal(tmp, foo);
	return foo;
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
	Node* tmp = root;
	post_order_traversal(tmp, foo);
	return foo;
}
#endif 
