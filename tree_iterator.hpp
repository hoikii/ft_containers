#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

namespace ft {


template <typename T>
class tree_iterator {
	public:
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef ptrdiff_t							difference_type;
		typedef std::bidirectional_iterator_tag		iterator_category;
	
	private:
		nodeBase<T>* _node;
	
	public:
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


}
#endif
