#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include <cstddef> // ptrdiff_t
# include "utils/Binary_Search_Tree.hpp"

namespace ft {


template <typename T>
class tree_iterator {
	public:
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef ptrdiff_t							difference_type;
		typedef std::bidirectional_iterator_tag		iterator_category;
		nodeBase<T>* _node;
	
		tree_iterator() : _node(NULL) {}
		tree_iterator(nodeBase<T>* node) : _node(node) {}
		~tree_iterator() {}
		tree_iterator(const tree_iterator &other) : _node(other._node) {}
		tree_iterator &operator=(const tree_iterator &rhs) {
			_node = rhs._node;
			return *this;
		}

		reference operator*() const {
			return _node->value;
		}

		pointer operator->() const {
			return &(_node->value);
		}

		tree_iterator &operator++() {
			_node = _node->next();
			return *this;
		}

		tree_iterator operator++(int) {
			tree_iterator tmp(*this);
			_node = _node->next();
			return tmp;
		}

		tree_iterator &operator--() {
			_node = _node->prev();
			return *this;
		}

		tree_iterator operator--(int) {
			tree_iterator tmp(*this);
			_node = _node->prev();
			return tmp;
		}

		bool operator==(const tree_iterator &rhs) const {
			return (_node == rhs._node);
		}

		bool operator!=(const tree_iterator &rhs) const {
			return (_node != rhs._node);
		}

};


template <typename T>
class tree_const_iterator {
	public:
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef ptrdiff_t							difference_type;
		typedef std::bidirectional_iterator_tag		iterator_category;
		nodeBase<T>* _node;

		tree_const_iterator() : _node(NULL) {}
		tree_const_iterator(nodeBase<T>* node) : _node(node) {}
		~tree_const_iterator() {}
		tree_const_iterator(const tree_const_iterator &other) : _node(other._node) {}
		tree_const_iterator(const tree_iterator<T> &other) : _node(other._node) {}
		tree_const_iterator &operator=(const tree_const_iterator &rhs) {
			_node = rhs._node;
			return *this;
		}

		reference operator*() const {
			return _node->value;
		}

		pointer operator->() const {
			return &(_node->value);
		}

		tree_const_iterator &operator++() {
			_node = _node->next();
			return *this;
		}

		tree_const_iterator operator++(int) {
			tree_const_iterator tmp(*this);
			_node = _node->next();
			return tmp;
		}

		tree_const_iterator &operator--() {
			_node = _node->prev();
			return *this;
		}

		tree_const_iterator operator--(int) {
			tree_const_iterator tmp(*this);
			_node = _node->prev();
			return tmp;
		}

		bool operator==(const tree_const_iterator &rhs) const {
			return (_node == rhs._node);
		}

		bool operator!=(const tree_const_iterator &rhs) const {
			return (_node != rhs._node);
		}

};
}
#endif
