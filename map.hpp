#ifndef MAP_HPP
# define MAP_HPP

# include <functional> // less
# include <memory> // allocator
# include <limits> // numeric_limits, max
# include "utils/pair.hpp"
# include "tree_iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/iterators_traits.hpp"

namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key,T> > >
class map {
	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const Key, T>					value_type;
		typedef Compare									key_compare;
		class	value_compare {
			friend class map<Key, T, Compare, Alloc>;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) { }
			public:
				bool operator() (const value_type& x, const value_type& y) const {
					return (comp(x.first, y.first));
				}
		};
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef tree_iterator<value_type>				iterator;
		typedef tree_iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;

	private:
		BinarySearchTree<Key,T, Compare, Alloc> _bst;
		key_compare _comp;
		allocator_type _alloc;

	public:
		// default Ctor
		map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _bst(comp, alloc), _comp(comp), _alloc(alloc) { }

		// range Ctor
		template<typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _bst(comp, alloc), _comp(comp), _alloc(alloc) {
				while (first != last)
					insert(first++);
		}

		// copy Ctor
		map(const map& other) : _bst(other.comp, other.alloc), _comp(other.comp), _alloc(other.alloc) {
			insert(other.begin(), other.end());
		 }

		map& operator=(const map& rhs) {
			map tmp(rhs);
			swap(tmp);
			return *this;
		}

		// Dtor : allocation only happens in bst so we don't need to do anything.
		~map() { }

		// Iterators
		iterator		begin()			{ return iterator(_bst.min()); }
		const_iterator	begin() const	{ return const_iterator(_bst.min()); }
		iterator		end()			{ return iterator(_bst.end()); }
		const_iterator	end() const		{ return const_iterator(_bst.end()); }

		// Capacity
		bool		empty()		const { return (_bst.getSize() == 0); }
		size_type	size()		const { return _bst.getSize(); }
		size_type	max_size()	const { return std::numeric_limits<difference_type>::max() / sizeof(T); }

		// if k matches the key, returns a reference to its mapped value.
		// if not, inserts a new element with that key and returns a reference to its mapped value.
		mapped_type& operator[](const key_type& k) {
			iterator tmp = _bst.find(k);
			if (tmp == end())
				tmp = insert(ft::make_pair(k, mapped_type())).first;
			return (*tmp).second;

		}

		// insert single element
		ft::pair<iterator,bool>	insert(const value_type& val) {
			size_type before = _bst.getSize();
			iterator pos = _bst.insert(val.first, val.second);
			size_type after = _bst.getSize();
			return ft::make_pair<iterator, bool>(pos, before!=after);
		}

		// insert with hint
		iterator				insert(iterator position, const value_type& val) {
			// if (position->second < val) // if hint is valid
			if ( _comp(position->second, val) )
				return _bst.insert(position._node, val.first, val.second);
			else
				return _bst.insert(val.first, val.second);
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

		void		swap(map& x) {
			_bst.swap(x._bst);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
		}

		void		clear() {
			_bst.clear();
		}

		key_compare		key_comp() const	{ return key_compare(); }
		value_compare	value_com() const	{ return value_compare(key_compare()); }


		iterator 		find(const key_type& k)			{ return iterator(_bst.find(k)); }
		const_iterator	find(const key_type& k) const	{ return iterator(_bst.find(k)); }

		size_type		count(const key_type& k) const {
			if (find(k) == end())
				return 1;
			return 0;
		}

		iterator							lower_bound(const key_type& k) {
			iterator it = begin();
			while (it != end()) {
				if ( ! _comp(it->first, k) )	// return if   it->first >= k
					break;
				it++;
			}
			return it;
		}

		const_iterator						lower_bound(const key_type& k) const {
			return const_iterator(lower_bound(k));
		}

		iterator							upper_bound(const key_type& k) {
			iterator it = begin();
			while (it != end()) {
				if ( _comp(k, it->first) )		// return if   it->first > k
					break;
				it++;
			}
			return it;
		}

		const_iterator						upper_bound(const key_type& k) const {
			return const_iterator(upper_bound(k));
		}

		ft::pair<iterator,iterator>				equal_range(const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		allocator_type	get_allocator() const { return _alloc; }

};


}
#endif
