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
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
		{
			// FIXME: 인자가 bidi-iterator 이하인 경우를 위해 std::distance로 대체
			difference_type n = last - first;
			_alloc = alloc;
			_size = n;
			_capacity = n;
			_ptr_start = _alloc.allocate(n);
			for (difference_type i = 0; i < n; i++)
				_ptr_start[i] = *(first++);
		}


		// Dtor
		~vector() {
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
#if 0
		template <typename InputIterator>
		void			assign(InputIterator first, InputIterator last);	// range
		void 			assign(size_type n, const value_type& val);			// fill
#endif
#if 1

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
#endif
#if 0
		iterator		insert(iterator position, const value_type& val);					// single element
		void			insert(iterator position, size_type n, const value_type& val);		// fill
		template <typename InputIterator>
		void			isert(iterator position, InputIterator first, InputIterator last);	//range
		iterator		erase(iterator position);
		iterator		erase(iterator first, iterator last);
#endif
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
