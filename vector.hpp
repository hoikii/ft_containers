#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include <limits>
# include <algorithm>
# include "random_access_iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
#include <iostream>

namespace ft {

template < typename T, typename Alloc = std::allocator<T> >
class vector {
	public:
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef T&					reference;
		typedef const T&			const_reference;
		typedef T*					pointer;
		typedef const T*			const_pointer;
		typedef random_access_iterator<T>				iterator;
		typedef random_access_iterator<const T>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;

	private:
		T				*_ptr_start;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
		// Ctor

		// default
		vector(const allocator_type& alloc = allocator_type()) : _ptr_start(NULL), _size(0), _capacity(0), _alloc(alloc) {}

		// fill
		vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
			_alloc = alloc;
			_size = n;
			_capacity = n;
			_ptr_start = _alloc.allocate(n);
			for (size_t i = 0; i < n; i++)
				_ptr_start[i] = val;
		}

		// range
		// 템플릿 인자가 (정수형,정수형)인 경우, range initializer를 오버로딩 후보군에서 제외한다.
		template <typename InputIterator>
		vector(InputIterator first,
			typename ft::enable_if< ! ft::is_integral<InputIterator>::value , InputIterator >::type last,
			const allocator_type& alloc = allocator_type() )
		{
			size_type n = std::distance(first, last);
			_alloc = alloc;
			_size = n;
			_capacity = n;
			_ptr_start = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_ptr_start[i] = *(first++);
		}

		// Dtor
		~vector() {
			clear();
			if (_ptr_start)
				_alloc.deallocate(_ptr_start, _capacity);
		}
		// Copy Ctor
		vector(const vector& other) {
			_ptr_start = _alloc.allocate(other._capacity);
			_size = other._size;
			_capacity = other._capacity;
			for (size_t i = 0; i < _size; i++)
				_ptr_start[i] = other._ptr_start[i];
		}

		// operator=
		vector& operator=(const vector& rhs) {
			vector tmp(rhs);
			swap(tmp);
			return *this;
		}

		// Iterators
		iterator				begin()			{ return iterator(_ptr_start); }
		const_iterator			begin() const	{ return const_iterator(_ptr_start); }
		iterator				end() 			{ return iterator(_ptr_start + _size); }
		const_iterator			end() const		{ return const_iterator(_ptr_start + _size); }
		reverse_iterator		rbegin()		{ return reverse_iterator(_ptr_start + _size); }
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(_ptr_start + _size); }
		reverse_iterator		rend()			{ return reverse_iterator(_ptr_start); }
		const_reverse_iterator	rend() const	{ return cosnt_reverse_iterator(_ptr_start); }

		// capacity
		size_type		size() const { return _size; }

		/* returns the maximum number of elements that vector can hold.
		 * This is the maximum potential size the container can reach due to system or implementation limitations.
		 * container isn't guaranteed to to be able to reach that size: it can still fail to allocate before that size is reached.
		 */
		size_type		max_size() const {
			return std::numeric_limits<difference_type>::max() / sizeof(T);
		}

		/* container will contain n elements
		 * if n is smaller than current size, contents are reduced to n elements, and removing those beyond.
		 * if n is greater than current size, capacity is expanded to n, and new elements are initialized as val.
		 * if n is also greater than current capacity, automatic reallocation will occur.
		 */
		void			resize(size_type n, value_type val = value_type()) {
			if (n > _capacity)
			{
				vector tmp(n);
				for (size_t i = 0; i < n; i++)
					if (i < _size)
						tmp._ptr_start[i] = _ptr_start[i];
					else
						tmp._ptr_start[i] = val;
				swap(tmp);
				return;
			}
			else
			{
				for (size_t i = _size; i < _capacity; i++)
					_ptr_start[i] = val;
				_size = n;
			}
		}

		size_type		capacity() const { return _capacity; }

		bool			empty() const { return _size == 0; }

		/* capacity will be at least n.
		 * if n is greater than current capacity, automatic reallocation will accur.
		 * otherwise, do nothing.
		 * This function has no effect on the vector size and cannot alter its elements.
		 */
		void			reserve(size_type n) {
			if ( n > _capacity) {
				vector tmp(n);
				tmp._size = _size;
				for (size_t i = 0; i < _size; i++)
					tmp._ptr_start[i] = _ptr_start[i];
				swap(tmp);
			}
		}

		// element access
		reference		operator[] (size_type n) { return _ptr_start[n]; }

		const_reference	operator[] (size_type n) const { return _ptr_start[n]; }

		reference		at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("ft_vector");
			return _ptr_start[n];
		}

		const_reference	at(size_type n) const {
			if (n >= _size)
				throw std::out_of_range("ft_vector");
			return _ptr_start[n];
		}

		reference		front()			{ return _ptr_start[0]; }
		const_reference	front() const	{ return _ptr_start[0]; }

		reference		back()			{ return _ptr_start[_size - 1]; }
		const_reference	back() const	{ return _ptr_start[_size - 1]; }

		// modifiers
		// range
		template <typename InputIterator>
		void			assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			clear();
			size_type n = std::distance(first, last);
			if (n > _capacity)
				reserve(n);
			while (first != last)
				push_back(*first++);
		}

		// fill
		void 			assign(size_type n, const value_type& val) {
			clear();
			if (n > _capacity)
				reserve(n);
			for (size_t i = 0; i < n; i++)
				push_back(val);
		}

		void			push_back(const value_type& val) {
			if (_size >= _capacity)
				reserve((_capacity == 0) ? 1 : _capacity * 2);
			_ptr_start[_size++] = val;
		}

		void			pop_back() {
			if (_size) {
				_alloc.destroy(_ptr_start + _size - 1);
//				_ptr_start[--_size].value_type::~value_type();
				_size--;
			}
		}

		// insert, erase: capacity 변화가 없으면 삽입,삭제된 요소 이전을 가리키는 iterator들은 유효해야 한다.
		// single element
		iterator		insert(iterator position, const value_type& val) {
			pointer p_pos = &(*position);
			if (_size < _capacity) {
				iterator i = end() - 1;
				for (i = end() -1; i != position; i--)
					*i = *(i - 1);
				*i = val;
				_size++;
			}
			else {
				vector tmp;
				tmp.reserve(_size + 1);
				iterator i = begin();
				for (i = begin(); i != position; i++)
					(tmp._ptr_start)[&(*i) - _ptr_start] = *i;
				(tmp._ptr_start)[&(*i) - _ptr_start] = val;
				for (i = position; i != end(); i++)
					(tmp._ptr_start)[&(*i) - _ptr_start + 1] = *i;
				swap(tmp);
				return iterator(_ptr_start + &(*position) - &(*tmp.begin()));

			}
		}

		//fill
		void			insert(iterator position, size_type n, const value_type& val) {
			size_type insertion_idx = position - begin();

			if (_size + n <= _capacity) {
				for (size_type i = _size + n; i > insertion_idx; i--)
					_ptr_start[i] = _ptr_start[i - n];
				_size += n;
				while (n)
					_ptr_start[insertion_idx + n-- - 1] = val;
			}
			else
			{
				vector tmp(_alloc);
				tmp.reserve(_size + n);
				tmp._size = _size + n;
				for (size_type i = 0; i < insertion_idx; i++)
					tmp[i] = *(_ptr_start + i);
				for (size_type i = insertion_idx; i < insertion_idx + n; i++)
					tmp[i] = val;
				for (size_type i = insertion_idx + n; i < _size + n; i++)
					tmp[i] = *(_ptr_start + i - n);
				swap(tmp);
			}
		}

		// range
		template <typename InputIterator>
		void			insert(iterator position,
							InputIterator first,
							typename ft::enable_if< ! ft::is_integral<InputIterator>::value, InputIterator>::type last)
		{
			size_type n = std::distance(first, last);
			size_type insertion_idx = position - begin();

			if (_size + n <= _capacity) {
				for (size_type i = _size + n; i > insertion_idx; i--)
					_ptr_start[i] = _ptr_start[i - n];
				size_type i = 0;
				while (first != last)
					_ptr_start[insertion_idx + i++] = *(first++);
				_size += n;
			}
			else
			{
				vector tmp(_alloc);
				tmp.reserve(_size + n);
				tmp._size = _size + n;
				for (size_type i = 0; i < insertion_idx; i++)
					tmp[i] = *(_ptr_start + i);
				for (size_type i = insertion_idx; i < insertion_idx + n; i++)
					tmp[i] = *(first++);
				for (size_type i = insertion_idx + n; i < _size + n; i++)
					tmp[i] = *(_ptr_start + i - n);
				swap(tmp);
			}
		}

		iterator		erase(iterator position) {
			pointer p_pos = &(*position);
			if (position + 1 == end())
				pop_back();
			else
			{
				// invalid position or range [first,last) causes undefined behavior
				for (size_type i = p_pos - _ptr_start; i < _size; i++) {
					_alloc.destroy(_ptr_start + i);
					_ptr_start[i] = _ptr_start[i + 1];
				}
				_alloc.destroy(_ptr_start + _size);
				_size--;
			}
			return iterator(p_pos);

		}

		iterator		erase(iterator first, iterator last) {
			// pointer p_pos = &(*first);
			if (last + 1 == end()) {
				while (first != last--)
					pop_back();
			}
			else {
				size_t n = last - first;
				for (size_t i = &(*first) - _ptr_start; i < _size - n; i++) {
					_ptr_start[i] = _ptr_start[i+n];
				}
				_size -= n;
			}
			return first;
		}

		void			swap(vector& x) {
			std::swap(_ptr_start, x._ptr_start);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_alloc, x._alloc);
		}

		void			clear() {
			while (_size)
				pop_back();
		}

		// Allocator
		allocator_type	get_allocator() const {
			return _alloc;
		}

};
  
// relational operators (==, !=, <, <=, >, >=)

// non-member function overloads
template <typename T, typename Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
	x.swap(y);
}



}
#endif
