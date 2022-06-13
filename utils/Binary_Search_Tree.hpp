#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "tree_interface.hpp"

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


template <typename ValueType, typename Compare, typename Alloc>
class BinarySearchTree : public TreeInterface<ValueType, Compare, Alloc> {
	public:
		using TreeInterface<ValueType,Compare,Alloc>::_comp;
		using TreeInterface<ValueType,Compare,Alloc>::_alloc;
		using TreeInterface<ValueType,Compare,Alloc>::_end;
		using TreeInterface<ValueType,Compare,Alloc>::_root;
		using TreeInterface<ValueType,Compare,Alloc>::_size;
		typedef nodeBase<ValueType>		node;

		BinarySearchTree(Compare comp, Alloc alloc) : TreeInterface<ValueType,Compare,Alloc>(comp, alloc) { }

		BinarySearchTree(const BinarySearchTree& other) : TreeInterface<ValueType,Compare,Alloc>(other) { }

		virtual ~BinarySearchTree() { }

	private:
		BinarySearchTree() { }
		BinarySearchTree& operator=(const BinarySearchTree& rhs);

		virtual node* _insert(node* cur, ValueType value) {
			while (1) {
				if (_comp(value, cur->value)) {			// 추가하려는 key가 현재 node의 key보다 작다면
					if (cur->left == NULL) {
						//cur->left = new node(value, cur);
						cur->left = _alloc.allocate(1);
						_alloc.construct(cur->left, node(value, cur));
						_size++;
						return cur->left;
					}
					else
						cur = cur->left;
				}
				else if (_comp(cur->value, value)) {	// 추가하려는 key가 현재 node의 key보다 크다면
					if ( cur->right == NULL) {
						//cur->right = new node(value, cur);
						cur->right = _alloc.allocate(1);
						_alloc.construct(cur->right, node(value, cur));
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

		virtual node* _find(node* cur, ValueType value) {
			while (cur != NULL) {
				if (_comp(value, cur->value))		// 찾으려는 key가 현재 node의 key보다 작다면
					cur = cur->left;
				else if (_comp(cur->value, value))	// 찾으려는 key가 현재 node의 key 보다 크다면
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
		virtual void _erase(node* cur, ValueType value) {
			node* del = _find(cur, value);
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

		node* _find_min(node* cur) {
			while (cur->left)
				cur = cur->left;
			return cur;
		}


};




}
#endif
