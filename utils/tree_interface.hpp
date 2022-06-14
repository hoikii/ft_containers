#ifndef TREE_INTERFACE_HPP
# define TREE_INTERFACE_HPP

# include "node.hpp"

namespace ft {

template <typename ValueType, typename Compare, typename Alloc>
class TreeInterface {
	protected:
		typedef nodeBase<ValueType>		node;
		node*	_end;
		node*	_root;
		size_t	_size;
		typedef typename Alloc::rebind<node>::other			NodeAlloc;
		Compare		_comp;
		NodeAlloc	_alloc;

	private:
		TreeInterface() { }
		TreeInterface& operator=(const TreeInterface& rhs);

		node* _copy_recurse(node* src, node* dst_parent) {
			if (!src)
				return NULL;
			//node* dst = new node(src->value, dst_parent);
			node* dst = _alloc.allocate(1);
			_alloc.construct(dst, node(src->value, dst_parent));
			dst->left = _copy_recurse(src->left, dst);
			dst->right = _copy_recurse(src->right, dst);
			return dst;
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

	public:
		TreeInterface(Compare comp, Alloc alloc) : _root(NULL), _size(0), _comp(comp), _alloc(NodeAlloc(alloc)) {
			//_end = new node;
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node());
		}

		virtual ~TreeInterface() {
			_deleteTree(_root);
			//delete _end;
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		}
		
		TreeInterface(const TreeInterface& other) : _root(NULL), _size(other._size), _comp(other._comp), _alloc(other._alloc) {
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node());
			_root = _copy_recurse(other._root, _end);
		}

		/* Return a pointer to newly inserted (or existing) element. */
		node* insert(ValueType value) {
			if (!_root) {
				//_root = new node(value, _end);
				_root = _alloc.allocate(1);
				_alloc.construct(_root, node(value, _end));
				_end->right = _root;
				_size++;
				_root->color = ft::BLACK;
				return _root;
			}
			return _insert(_root, value);
		}
		node* insert(node* hint, ValueType value) { return _insert(hint, value); }

		/* If key is not present, return tree end. */
		node* find(ValueType value) {
			node* result =_find(_root, value);
			if (result == NULL)
				return _end;
			return result;
		}

		void erase(ValueType value) {
			_erase(_root, value);
		}
		void erase(node* pos) {
			_erase(pos, pos->value);
		}

		node* begin() const {
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

		void	swap(TreeInterface& x) {
			std::swap(_end, x._end);
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
		}

		virtual node* _insert(node* cur, ValueType value) = 0;
		virtual node* _find(node* cur, ValueType value) = 0;
		virtual void _erase(node* cur, ValueType value) = 0;


};





}
#endif
