#ifndef MAP_HPP
# define MAP_HPP

# include <functional> // less
# include <memory> // allocator
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
		// TODO: value_compare
		typedef Alloc									allocator_type;
		typedef typename Alloc::reference				reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef tree_iterator<value_type>				iterator;
		typedef tree_iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;
		public:

	private:
		// TODO: Use Compare, Alloc in our tree
		BinarySearchTree<Key,T> _bst;
		key_compare _comp;
		allocator_type _alloc;

	public:
		// default Ctor
		map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _bst(), _comp(comp), _alloc(alloc) { }

		// range Ctor
		template<typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _bst(), _comp(comp), _alloc(alloc) {
				while (first != last)
					insert(first++);
		}

		// copy Ctor
		/*
		map(const map& other) : _bst(), _comp(other.comp), _alloc(other.alloc) {
			insert(other.begin(), other.end());
		 }
*/
		map& operator=(const map& rhs) { }

		~map() { }

		bool		empty()	const { return (_bst.getSize() == 0); }
		size_type	size()	const { return _bst.getSize(); }

		iterator		begin()			{ return iterator(_bst.min()); }
		const_iterator	begin() const	{ return const_iterator(_bst.min()); }
		iterator		end()			{ return iterator(_bst.end()); }
		const_iterator	end() const		{ return const_iterator(_bst.end()); }

		mapped_type& operator[](const key_type& k) {
			iterator tmp = _bst.find(k);
			if (tmp == end())
				tmp = insert(ft::make_pair(k, mapped_type())).first;
			return (*tmp).second;

		}

		ft::pair<iterator,bool> insert(const value_type& val) {
			size_type before = _bst.getSize();
			iterator pos = _bst.insert(val.first, val.second);
			size_type after = _bst.getSize();
			return ft::make_pair<iterator, bool>(pos, before!=after);
		}

		size_type erase(const key_type& k) {
			size_type before = _bst.getSize();
			_bst.erase(k);
			size_type after = _bst.getSize();
			return after - before;
		}

		iterator 		find(const key_type& k)			{ return iterator(_bst.find(k)); }
		const_iterator	find(const key_type& k) const	{ return iterator(_bst.find(k)); }



};


}
#endif
