#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>

namespace ft {

template <typename T, typename Alloc = std::allocator<T>>
class vector {
	public:
		typedef T					value_type;
		typedef Alloc				allocator_type;
		typedef T&					reference;
		typedef const T&			const_reference;
		typedef T*					pointer;
		typedef const T*			const_pointer;
#if 0
		iterator;
		const_iterator;
		reverse_iterator;
		const_reverse_iterator;
#endif
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;

	private:
		T			*m_array;
		size_type	m_size;
		size_type	m_capacity;

	public:
		// Ctor
		vector(const allocator_type& alloc = allocator_type()) : m_size(0), m_capacity(0) {}							// default
		vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {		// fill

			m_array = new T[n];
			m_size = n;
			m_capacity = n;
			for (size_t i = 0; i < n; i++)
				m_array[i] = val;
		}
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {}				// range
		// Dtor
		~vector() {
			if (m_capacity)
				delete[] m_array;
		}
		// Copy Ctor
		vector(const vector& other) {
			m_array = new T[other.m_capacity];
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			for (size_t i = 0; i < m_size; i++)
				m_array[i] = other.m_array[i];
		}
		// operator=
		vector& operator=(const vector& rhs) {
			// TODO: copy-and-swap
			return *this;
		}

#if 0
		// Iterators
		iterator		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;
		iterator		rbegin();
		const_iterator	rbegin() const;
		iterator		rend();
		const_iterator	rend() const;
#endif

		// capacity
		size_type		size() const { return m_size; }
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
			if (n > m_capacity)
			{
				vector tmp(n);
				for (size_t i = 0; i < n; i++)
					if (i < m_size)
						tmp[i] = m_array;
					else
						tmp[i] = val;
				swap(*this, tmp);
				return;
			}
			else
			{
				for (size_t i = m_size; i < m_capacity; i++)
					m_array[i] = val;
				size = n;
			}
		}
		size_type		capacity() const { return m_capacity; }
		bool			empty() const { return m_size == 0; }
		/* capacity will be at least n.
		 * if n is greater than current capacity, automatic reallocation will accur.
		 * otherwise, do nothing.
		 * This function has no effect on the vector size and cannot alter its elements.
		 */
		void			reserve(size_type n) {
			if ( n > m_capacity) {
				vector tmp(n);
				for (size_t i = 0; i < m_size; i++)
					tmp.m_array[i] = m_array[i];
				swap(*this, tmp);
			}
		}

#if 0
		// element access
		reference		operator[] (size_type n);
		const_reference	operator[] (size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// modifiers
		template <typename InputIterator>
		void			assign(InputIterator first, InputIterator last);	// range
		void 			assign(size_type n, const value_type& val);			// fill
		void			push_back(const value_type& val);
		void			pop_back();
		iterator		insert(iterator position, const value_type& val);					// single element
		void			insert(iterator position, size_type n, const value_type& val);		// fill
		template <typename InputIterator>
		void			isert(iterator position, InputIterator first, InputIterator last);	//range
		iterator		erase(iterator position);
		iterator		erase(iterator first, iterator last);
		void			swap(vector& x);
		void			clear();

		// Allocator
		allocator_type	get_allocator() const;

		// relational operators (==, !=, <, <=, >, >=)

		// swap
		template <typename T, Typename Alloc>
		void			swap(vector<T, Alloc>& x, vector<T, Alloc>& y);
#endif



};

}
#endif
