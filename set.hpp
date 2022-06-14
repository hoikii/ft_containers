#ifndef SET_HPP
# define SET_HPP

# include <functional> // less
# include <memory> // allocator
# include <limits> // numeric_limits, max
# include <cstddef> // ptrdiff_t
# include "tree_iterator.hpp"
# include "utils/pair.hpp"
# include "utils/RB_Tree.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/iterators_traits.hpp"
# include <iostream>

namespace ft {

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
class set {
	public:
		typedef T										key_type;
		typedef T										value_type;
		typedef Compare									key_compare;
		typedef Compare									value_compare;
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Alloc::pointer					pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef tree_iterator<value_type>				iterator;
		typedef tree_const_iterator<value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;

	private:
		RB_Tree<value_type, value_compare, Alloc> _bst;
		key_compare _comp;
		allocator_type _alloc;

	public:
		// default Ctor
		set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _bst(value_compare(comp), alloc), _comp(comp), _alloc(alloc) { }

		// range Ctor
		template<typename InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _bst(value_compare(comp), alloc), _comp(comp), _alloc(alloc) {
				while (first != last)
					insert(first++);
		}

		// copy Ctor
		set(const set& other) : _bst(other._bst), _comp(other._comp), _alloc(other._alloc) { }

		set& operator=(const set& rhs) {
			set tmp(rhs);
			swap(tmp);
			return *this;
		}

		// Dtor : allocation only happens in bst so we don't need to do anything.
		~set() { }

		// Iterators
		iterator		begin()			{ return iterator(_bst.begin()); }
		const_iterator	begin() const	{ return const_iterator(_bst.begin()); }
		iterator		end()			{ return iterator(_bst.end()); }
		const_iterator	end() const		{ return const_iterator(_bst.end()); }

		reverse_iterator		rbegin()		{ return reverse_iterator(_bst.end()); }
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(_bst.end()); }
		reverse_iterator		rend()			{ return reverse_iterator(_bst.begin()); }
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(_bst.begin()); }

		// Capacity
		bool		empty()		const { return (_bst.getSize() == 0); }
		size_type	size()		const { return _bst.getSize(); }
		size_type	max_size()	const { return std::numeric_limits<difference_type>::max() / sizeof(T); }

		// insert single element
		ft::pair<iterator,bool>	insert(const value_type& val) {
			size_type before = _bst.getSize();
			iterator pos = _bst.insert(val);
			size_type after = _bst.getSize();
			return ft::make_pair<iterator, bool>(pos, before!=after);
		}

		// insert with hint
		iterator				insert(iterator position, const value_type& val) {
			// if (position->second < val) // if hint is valid
			if ( _comp(position, val) )
				return _bst.insert(position._node, val);
			else
				return _bst.insert(val);
		}

		// insert range
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last) {
			difference_type n = std::distance(first, last);
			while (n--)
				insert(*(first++));
		}

		void		erase(iterator position) {
			_bst.erase(position._node);
		}

		size_type	erase(const key_type& k) {
			size_type before = _bst.getSize();
			_bst.erase(k);
			size_type after = _bst.getSize();
			return after - before;
		}

		void		erase(iterator first, iterator last) {
			while (first != last) {
				erase((first++._node));
			}
		}

		void		swap(set& x) {
			_bst.swap(x._bst);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
		}

		void		clear() {
			_bst.clear();
		}

		key_compare		key_comp() const	{ return _comp; }
		value_compare	value_comp() const	{ return value_compare(_comp); }


		iterator 		find(const key_type& k)			{ return iterator(_bst.find(k)); }
		const_iterator	find(const key_type& k) const	{ return iterator(_bst.find(k)); }

		size_type		count(const key_type& k) const {
			if (find(k) == end())
				return 1;
			return 0;
		}

		iterator		lower_bound(const key_type& k) {
			iterator it = begin();
			while (it != end()) {
				if ( ! _comp(it->first, k) )	// return if   it->first >= k
					break;
				it++;
			}
			return it;
		}

		const_iterator	lower_bound(const key_type& k) const {
			return const_iterator(lower_bound(k));
		}

		iterator		upper_bound(const key_type& k) {
			iterator it = begin();
			while (it != end()) {
				if ( _comp(k, it->first) )		// return if   it->first > k
					break;
				it++;
			}
			return it;
		}

		const_iterator	upper_bound(const key_type& k) const {
			return const_iterator(upper_bound(k));
		}

		ft::pair<iterator,iterator>				equal_range(const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		allocator_type	get_allocator() const { return _alloc; }


		void tree_info() const {
			std::cout << std::boolalpha << "2. root가 블랙인가? " << _bst.isRootBlack() << "\n";
			std::cout << "4. 중복된 red가 없는가? " << !(_bst.isRedDup(_bst._root)) << "\n";
			size_t minH = _bst.getMinHeight(_bst._root);
			size_t maxH = _bst.getMaxHeight(_bst._root);
			std::cout << "5. 최대거리가 최소거리의 2배를 넘지 않는가? (" << minH << "," << maxH << ")  "<< (maxH <= 2 * minH ) << "\n\n";
		}

};


}
#endif
