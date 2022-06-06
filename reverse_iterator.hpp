#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterators_traits.hpp"

namespace ft {

/* original iterator의 사본을 base iterator에 저장하고, reverse_iterator가 증가/감소할 때마다 base iterator를 감소/증가시킨다. */
template <typename Iterator>
class reverse_iterator {
	public:
		typedef Iterator										iterator_type;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

	private:
		iterator_type	_base_iterator;
	
	public:
		reverse_iterator() { iterator_type(); }

		reverse_iterator(iterator_type it) { _base_iterator = it; }

		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) {
			_base_iterator = rev_it._base_iterator;
		}

		~reverse_iterator() {}

		iterator_type		base() const { return _base_iterator; }
		reference			operator*() const { return *(_base_iterator - 1); }
		pointer				operator->() const { return &(operator*()); }
		reference			operator[](difference_type n) const { return base()[-n-1]; }
		
		reverse_iterator	operator+(difference_type n) const {
			return reverse_iterator(_base_iterator - n);
		}
		reverse_iterator	operator-(difference_type n) const {
			return reverse_iterator(_base_iterator + n);
		}
		reverse_iterator&	operator++() {
			--_base_iterator;
			return *this;
		}
		reverse_iterator	operator++(int) {
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}
		reverse_iterator&	operator--() {
			++_base_iterator;
			return *this;
		}
		reverse_iterator	operator--(int) {
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}
		reverse_iterator&	operator+=(difference_type n) {
			_base_iterator -= n;
			return *this;
		}
		reverse_iterator&	operator-=(difference_type n) {
			_base_iterator += n;
			return *this;
		}
};

//non-member
//relational
//+
//-

}

#endif
