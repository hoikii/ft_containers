#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class vector {
	private:
	public:
		value_type;
		allocator_type;
		reference;
		const_reference;
		pointer;
		const_pointer;
		iterator;
		const_iterator;
		reverse_iterator;
		const_reverse_iterator;
		difference_type;
		size_type;
		
		// Ctor
		// Dtor
		// operator=

		// Iterators
		iterator		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;
		iterator		rbegin();
		const_iterator	rbegin() const;
		iterator		rend();
		const_iterator	rend() const;

		// capacity
		size_type		size() const;
		size_type		max_size() const;
		void			resize(size_type n, value_type val = value_type());
		size_type		capacity() const;
		bool			empty() const;
		void			reserve(size_type n);

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




};

#endif
