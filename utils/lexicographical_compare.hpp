#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {

template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1) {

		if (first2 == last2)
			return false;
		if (*first1 < *first2)
			return true;
		if (*first1 > *first2)
			return false;
		first1++;
		first2++;
	}
	return (first2 != last2);
}

template <typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2, Compare comp)
{
	while (first1 != last1) {

		if (first2 == last2)
			return false;
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2 > *first1))
			return false;
		first1++;
		first2++;
	}
	return (first2 != last2);
}

}
#endif
