#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <algorithm>

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
		T				*m_array;
		size_type		m_size;
		size_type		m_capacity;
		allocator_type	m_alloc;


	public:
		// Ctor

		// default
		vector(const allocator_type& alloc = allocator_type()) : m_array(NULL), m_size(0), m_capacity(0), m_alloc(alloc) {}

		// fill
		vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
			m_alloc = alloc;
			m_size = n;
			m_capacity = n;
//			m_array = new T[n];
			m_array = m_alloc.allocate(n);
			for (size_t i = 0; i < n; i++)
				m_array[i] = val;
		}
/*
		vec(20, 0); 의 경우 fill이 아닌 range가 선택될 수 있기 때문에 enable_if 구현이 필요하다.
		// range
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {}
*/

		// Dtor
		~vector() {
			if (m_capacity)
				// delete[] m_array;
				m_alloc.deallocate(m_array, m_capacity);
		}
		// Copy Ctor
		vector(const vector& other) {
//			m_array = new T[other.m_capacity];
			m_array = m_alloc.allocate(other.m_capacity);
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
						tmp.m_array[i] = m_array[i];
					else
						tmp.m_array[i] = val;
				swap(tmp);
				return;
			}
			else
			{
				for (size_t i = m_size; i < m_capacity; i++)
					m_array[i] = val;
				m_size = n;
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
				tmp.m_size = m_size;
				for (size_t i = 0; i < m_size; i++)
					tmp.m_array[i] = m_array[i];
				swap(tmp);
			}
		}

		// element access
		reference		operator[] (size_type n) { return m_array[n]; }

		const_reference	operator[] (size_type n) const { return m_array[n]; }

		reference		at(size_type n) {
			if (n >= m_size)
				throw std::out_of_range("ft_vector");
			return m_array[n];
		}

		const_reference	at(size_type n) const {
			if (n >= m_size)
				throw std::out_of_range("ft_vector");
			return m_array[n];
		}

		reference		front() { return m_array[0]; }

		const_reference	front() const { return m_array[0]; }

		reference		back() { return m_array[m_size - 1]; }

		const_reference	back() const { return m_array[m_size - 1]; }

		// modifiers
#if 0
		template <typename InputIterator>
		void			assign(InputIterator first, InputIterator last);	// range
		void 			assign(size_type n, const value_type& val);			// fill
#endif
#if 1

		void			push_back(const value_type& val) {
			if (m_size >= m_capacity)
				reserve((m_capacity == 0) ? 1 : m_capacity * 2);
			m_array[m_size++] = val;
		}

		void			pop_back() {
			if (m_size) {
				m_alloc.destroy(m_array + m_size - 1);
//				m_array[--m_size].value_type::~value_type();
				m_size--;
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
			std::swap(m_array, x.m_array);
			std::swap(m_size, x.m_size);
			std::swap(m_capacity, x.m_capacity);
			std::swap(m_alloc, x.m_alloc);
		}

		void			clear() {
			while (m_size)
				pop_back();
		}

		// Allocator
		allocator_type	get_allocator() const {
			return m_alloc;
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
