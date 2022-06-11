#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "pair.hpp"

/*       end
          |
          6
        /   \
	   4     9
     /  \   /  \
    2    5  8   12
               /  \
		     10    13
			  \
			   11
 * Simple Binary Search Tree
 *
 * Each node has key and value. value contains key-val pair.
 * parent of root will be used for indicating end of iterator.
 * 
 */

namespace ft {

template <typename KV_Pair>
struct nodeBase {
	typedef typename KV_Pair::first_type KeyType;
	const KeyType key;
	KV_Pair value;
	nodeBase* left;
	nodeBase* right;
	nodeBase* parent;

	nodeBase() : key() { }
	nodeBase(KV_Pair kvPair, nodeBase* parent = NULL)
		: key(kvPair.first), value(kvPair), left(NULL), right(NULL), parent(parent) { }

	nodeBase* next() {
		if (this->parent == NULL)
			return max(this->right);
		nodeBase* next;
		if (this->right)
		{
			next = this->right;
			while (next->left)
				next = next->left;
		}
		else
		{
			next = this;
			while (next->parent && next->parent->right == next)
				next = next->parent;
			if (next->parent)
				next = next->parent;
		}
		return next;
	}

	nodeBase* prev() {
		if (this->parent == NULL)
			return max(this->right);
		nodeBase* prev;
		if (this->left)
		{
			prev = this->left;
			while (prev->right)
				prev = prev->right;
		}
		else
		{
			prev = this;
			while (prev->parent && prev->parent->left == prev)
				prev = prev->parent;
			prev =prev->parent;
		}
		return prev;
	}

	nodeBase* max(nodeBase* cur) {
		while (cur && cur->right)
			cur = cur->right;
		return cur;
	}


};

template <typename KeyType, typename ValueType>
class BinarySearchTree {
	private:
		typedef nodeBase<ft::pair<const KeyType,ValueType> > node;
		node* _end;
		node* _root;
		size_t _size;

		node* _insert(node* cur, KeyType key, ValueType val) {
			if (cur->key < key)
			{
				if (cur->right)
					return _insert(cur->right, key, val);
				else {
					cur->right = new node(ft::make_pair(key, val), cur);
					_size++;
					return cur->right;
				}
			}
			else if (cur->key > key)
			{
				if (cur->left)
					return _insert(cur->left, key, val);
				else {
					cur->left = new node(ft::make_pair(key, val), cur);
					_size++;
					return cur->left;
				}
			}
			return cur;
		}

		node* _find(node* cur, KeyType key) {
			if (cur == NULL)
				return NULL;
			if (cur->key < key)
				return _find(cur->right, key);
			else if (cur->key > key)
				return _find(cur->left, key);
			return cur;
		}

		node* _erase(node* cur, KeyType key) {
			if (cur == NULL)
				return cur;
			if (cur->key > key)
				cur->left = _erase(cur->left, key);
			else if (cur->key < key)
				cur->right = _erase(cur->right, key);
			else
			{
				if (cur->left == NULL) {
					node* tmp = cur->right;
					if (cur == _root) 
						_root = tmp;
					tmp->parent = cur->parent;
					delete cur;
					_size--;
					return tmp;
				}
				if (cur->right == NULL) {
					node* tmp = cur->left;
					if (cur == _root)
						_root = tmp;
					tmp->parent = cur->parent;
					delete cur;
					_size--;
					return tmp;
				}
				node* successor = _find_min(cur->right);
				node* tmp = new node(successor->value, cur->parent);
				tmp->left = cur->left;
				tmp->right = cur->right;

				/*******************
				if (cur->parent->left == cur)
					cur->parent->left = tmp;
				else if (cur->parent->right == cur)
					cur->parent->right = tmp;
				******************/
				if (cur == _root) { _root = tmp; tmp->parent = _end; }
				delete cur;
				tmp->right = _erase(tmp->right, tmp->key);
				return tmp;
			}
			return cur;
		}

		void _deleteTree(node* cur) {
			if (cur == NULL)
				return;
			_deleteTree(cur->left);
			_deleteTree(cur->right);
			delete cur;
		}

		node* _find_min(node* cur) {
			while (cur->left)
				cur = cur->left;
			return cur;
		}

		BinarySearchTree(const BinarySearchTree& other) { }
		BinarySearchTree& operator=(const BinarySearchTree& rhs) { }
	public:
		BinarySearchTree() : _root(NULL), _size(0) {
			_end = new node;
		}
		~BinarySearchTree() {
			_deleteTree(_root);
			delete _end;
		}

		/* Return a pointer to newly inserted (or existing) element. */
		node* insert(KeyType key) { return insert(key, key); }
		node* insert(KeyType key, ValueType val) {
			if (!_root) {
				_root = new node(ft::make_pair(key, val), _end);
				_end->right = _root;
				_size++;
				return _root;
			}
			return _insert(_root, key, val);
		}

		/* If key is not present, return tree end. */
		node* find(KeyType key) {
			node* tmp =_find(_root, key);
			if (!tmp)
				tmp = _end;
			return tmp;
		}

		/* Always return a pointer to _root element. */
		node* erase(KeyType key) { return _erase(_root, key); }

		node* min() const {
			if (_root == NULL)
				return _end;
			node* cur = _root;
			while (cur->left)
				cur = cur->left;
			return cur;
		}

		node* end() const { return _end; }

		size_t getSize() const { return _size; }

};


}
#endif
