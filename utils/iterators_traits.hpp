#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

namespace ft {

// We don't need custom tags.
// Use defined in std namespace, so that <algorithm> or other STL functions can identify iterator's category properly.
/*
struct random_access_iterator_tag {};
struct bidirectional_iterator_tag {};
struct forward_iterator_tag {};
struct input_iterator_tag {};
struct output_iterator_tag {};
*/

template <typename Iterator>
class iterator_traits {
	public:
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
};

template <typename T>
class iterator_traits<T*> {
	public:
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
};

template <typename T>
class iterator_traits<const T*> {
	public:
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
};

}

#endif
