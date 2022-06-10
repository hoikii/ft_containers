#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

/*
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
 * Each node has KeyType key, ValueType value, left_ptr, right_ptr, parent_ptr.
 * key is used for comparison.
 */

namespace ft {

template <typename KeyType, typename ValueType>
struct nodeBase {
	KeyType key;
	ValueType value;
	nodeBase* left;
	nodeBase* right;
	nodeBase* parent;

	nodeBase(KeyType key, ValueType value, nodeBase* parent = NULL)
		: key(key), value(value), left(NULL), right(NULL), parent(parent) { }
};

template <typename KeyType, typename ValueType>
class BinarySearchTree {
	private:
		typedef nodeBase<KeyType,ValueType> node;
		node* root;

		node* _insert(node* cur, KeyType key, ValueType val) {
			if (cur->key < key)
			{
				if (cur->right)
					return _insert(cur->right, key, val);
				else {
					cur->right = new node(val,val, cur);
					return cur->right;
				}
			}
			else if (cur->key > key)
			{
				if (cur->left)
					return _insert(cur->left, key, val);
				else {
					cur->left = new node(val,val, cur);
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

		node* _find_min(node* cur) {
			if (cur->left == NULL)
				return cur;
			return (cur->left);
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
					delete cur;
					return tmp;
				}
				if (cur->right == NULL) {
					node* tmp = cur->left;
					delete cur;
					return tmp;
				}
				node* tmp = _find_min(cur->right);
				cur->key = tmp->key;
				cur->value = tmp->value;
				cur->right = _erase(cur->right, tmp->key);
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

		BinarySearchTree(const BinarySearchTree& other) { }
		BinarySearchTree& operator=(const BinarySearchTree& rhs) { }
	public:
		BinarySearchTree() : root(NULL) { }
		~BinarySearchTree() { _deleteTree(root); }

		/* Return a pointer to newly inserted element.
		 * When insertion fails ie key is already present, return NULL. */
		node* insert(KeyType key) { return insert(key, key); }
		node* insert(KeyType key, ValueType val) {
			if (root != NULL)
				return _insert(root, key, val);
			root = new node(key, val);
			return root;
		}

		/* If key is not present, return NULL */
		node* find(KeyType key) { return _find(root, key); }

		/* Always return a pointer to root element. */
		node* erase(KeyType key) { return _erase(root, key); }

		void prn() { prn(root);}
		void prn(node* cur) {
			if (cur==NULL)
				return;
			prn(cur->left);
			std::cout << cur->value << ' ';
			prn(cur->right);
		}
};


}
#endif
