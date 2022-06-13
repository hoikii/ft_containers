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

	nodeBase() : key(), left(NULL), right(NULL), parent(NULL) { }
	nodeBase(const KV_Pair kvPair, nodeBase* parent = NULL)
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

template <typename KeyType, typename ValueType, typename Compare, typename Alloc>
class BinarySearchTree {
	private:
		typedef nodeBase<ft::pair<const KeyType,ValueType> >	node;
		node*	_end;
		node*	_root;
		size_t	_size;

		typedef typename Alloc::rebind<node>::other			NodeAlloc;
		Compare		_comp;
		NodeAlloc	_alloc;

		node* _insert(node* cur, KeyType key, ValueType val) {
			while (1) {
				if (_comp(key, cur->key)) {			// 추가하려는 key가 현재 node의 key보다 작다면
					if (cur->left == NULL) {
						//cur->left = new node(ft::make_pair(key, val), cur);
						cur->left = _alloc.allocate(1);
						_alloc.construct(cur->left, node(ft::make_pair(key,val), cur));
						_size++;
						return cur->left;
					}
					else
						cur = cur->left;
				}
				else if (_comp(cur->key, key)) {	// 추가하려는 key가 현재 node의 key보다 크다면
					if ( cur->right == NULL) {
						//cur->right = new node(ft::make_pair(key, val), cur);
						cur->right = _alloc.allocate(1);
						_alloc.construct(cur->right, node(ft::make_pair(key, val), cur));
						_size++;
						return cur->right;
					}
					else
						cur = cur->right;
				}
				else
					return cur;
			}
		}

		node* _find(node* cur, KeyType key) {
			while (cur != NULL) {
				if (_comp(key, cur->key))		// 찾으려는 key가 현재 node의 key보다 작다면
					cur = cur->left;
				else if (_comp(cur->key, key))	// 찾으려는 key가 현재 node의 key 보다 크다면
					cur = cur->right;
				else
					return cur;
			}
			return cur;
		}

		/* del의 부모와 child를 서로 연결.
		 * del 이 root node라면 child를 새로운 root로 지정
		*/
		void _link_parent_child(node* del, node* child) {
			if (del == _root)
				_end->right = _root = child;
			else
			{
				if (del == del->parent->left)
					del->parent->left = child;
				else
					del->parent->right = child;
			}
			if (child != NULL)
				child -> parent = del->parent;
		}

		/* cur를 기점으로 key를 탐색, 해당 노드를 삭제 */
		void _erase(node* cur, KeyType key) {
			node* del = _find(cur, key);
			if (!del)	// 삭제할 노드가 존재하지 않음
				return;

			if (del->left == NULL && del->right == NULL) {
				// 삭제할 노드가 leaf node라면
				_link_parent_child(del, NULL);
			}
			else if (del->left && del->right) {
				// 삭제할 노드가 2개라면
				node* successor = _find_min(del->right);	// 오른쪽 서브트리에서 최소값 찾기

				// successor는 left child가 없다. right child와 successor-parent 를 연결
				_link_parent_child(successor, successor->right);

				// successor를 del 자리로 옮김
				successor->left = del->left;
				successor->right = del->right;
				successor->parent = del->parent;
				del->left->parent = successor;
				del->right->parent = successor;
				_link_parent_child(del, successor);
			}
			else {
				// 삭제할 노드의 자식이 왼쪽, 오른쪽 중 하나만 있다면
				node* child = (del->left) ? del->left : del->right;
				_link_parent_child(del, child);
			}

			//delete del;
			_alloc.destroy(del);
			_alloc.deallocate(del, 1);
			_size--;
		}

		void _deleteTree(node* cur) {
			if (cur == NULL)
				return;
			_deleteTree(cur->left);
			_deleteTree(cur->right);
			//delete cur;
			_alloc.destroy(cur);
			_alloc.deallocate(cur, 1);
			_size--;
		}

		node* _find_min(node* cur) {
			while (cur->left)
				cur = cur->left;
			return cur;
		}

		BinarySearchTree() { }
		BinarySearchTree(const BinarySearchTree& other) { }
		BinarySearchTree& operator=(const BinarySearchTree& rhs);
	public:
		BinarySearchTree(Compare comp, Alloc alloc) : _root(NULL), _size(0), _comp(comp), _alloc(NodeAlloc(alloc)) {
			//_end = new node;
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node());
		}
		~BinarySearchTree() {
			_deleteTree(_root);
			//delete _end;
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		}

		/* Return a pointer to newly inserted (or existing) element. */
		node* insert(KeyType key, ValueType val) {
			if (!_root) {
				//_root = new node(ft::make_pair(key, val), _end);
				_root = _alloc.allocate(1);
				_alloc.construct(_root, node(ft::make_pair(key, val), _end));
				_end->right = _root;
				_size++;
				return _root;
			}
			return _insert(_root, key, val);
		}
		node* insert(node* hint, KeyType key, ValueType val) { return _insert(hint, key, val); }

		/* If key is not present, return tree end. */
		node* find(KeyType key) {
			node* tmp =_find(_root, key);
			if (tmp)
				return tmp;
			return _end;
		}

		void erase(KeyType key) {
			_erase(_root, key);
		}
		void erase(node* pos) {
			_erase(pos, pos->key);
		}

		node* min() const {
			if (_root == NULL)
				return _end;
			node* cur = _root;
			while (cur->left)
				cur = cur->left;
			return cur;
		}

		node*	end() const { return _end; }

		size_t	getSize() const { return _size; }

		void	clear() { _deleteTree(_root); }

		void	swap(BinarySearchTree& x) {
			std::swap(_end, x._end);
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
		}

};


}
#endif
