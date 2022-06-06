#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterators_traits.hpp"

namespace ft {

template <typename T>
class random_access_iterator {
	public:
		/* Iterator Traits */
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
	
	private:
		pointer	_p;
	
	public:
		random_access_iterator() : _p(NULL) {}
		random_access_iterator(pointer ptr) : _p(ptr) {}
		~random_access_iterator() {}
		random_access_iterator(const random_access_iterator &other) : _p(other._p) {}
		random_access_iterator &operator=(const random_access_iterator &rhs) {
			_p = rhs._p;
			return *this;
		}

		reference operator*() const {
			return *_p;
		}

		pointer operator->() const {
			return _p;
		}

		random_access_iterator &operator++() {
			_p++;
			return *this;
		}

		random_access_iterator operator++(int) {
			random_access_iterator tmp(*this);
			++_p;
			return tmp;
		}

		random_access_iterator &operator--() {
			_p--;
			return *this;
		}

		random_access_iterator operator--(int) {
			random_access_iterator tmp(*this);
			--_p;
			return tmp;
		}

		random_access_iterator &operator+=(difference_type n) {
			_p += n;
			return *this;
		}

		random_access_iterator &operator-=(difference_type n) {
			_p -= n;
			return *this;
		}

		bool operator==(const random_access_iterator &rhs) const {
			return (_p == rhs._p);
		}

		bool operator!=(const random_access_iterator &rhs) const {
			return (_p != rhs._p);
		}

		bool operator>(const random_access_iterator &rhs) const {
			return (_p > rhs._p);
		}

		bool operator<(const random_access_iterator &rhs) const {
			return (_p < rhs._p);
		}

		bool operator>=(const random_access_iterator &rhs) const {
			return (_p >= rhs._p);
		}
		
		bool operator<=(const random_access_iterator &rhs) const {
			return (_p <= rhs._p);
		}

		reference operator[](difference_type n) const {
			return *(*this + n);
		}

		// +, - between aniterator and an integer value
		random_access_iterator operator+(difference_type n) const {
			return _p + n;
		}

		random_access_iterator operator-(difference_type n) const {
			return _p - n;
		}

		difference_type operator-(random_access_iterator &rhs) const {
			return _p - rhs._p;
		}
};

// 덧셈의 교환법칙(정수+반복자) 성립 위해서 non-member operator overload 필요
template <typename T>
ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n, ft::random_access_iterator<T> &it) {
	return it + n;
}

}

#endif
