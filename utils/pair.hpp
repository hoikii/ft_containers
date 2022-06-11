#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

template <typename T1, typename T2>
struct pair {
	typedef T1	first_type;
	typedef T2	second_type;

	first_type first;
	second_type second;

	// Default Ctor
	pair() : first(), second() {}

	// Copy Ctor
	template<typename U, typename V>
	pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) { }

	// Initialization Ctor
	pair(const first_type& a, const second_type& b) : first(a), second(b) { }

	// Assign
	pair& operator=(const pair& pr) {
		first = pr.first;
		second = pr.second;
		return *this;
	}
};

// Relational operators
template <typename T1, typename T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <typename T1, typename T2>
bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(lhs == rhs);
}

template <typename T1, typename T2>
bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	if (lhs.first < rhs.first)
		return true;
	if (rhs.first < lhs.first)
		return false;
	if (lhs.second < rhs.second)
		return true;
	return false;
}

template <typename T1, typename T2>
bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(rhs < lhs);
}

template <typename T1, typename T2>
bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return (rhs < lhs);
}

template <typename T1, typename T2>
bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(lhs < rhs);
}


// make_pair - returns new pair object
template <typename T1, typename T2>
pair<T1,T2> make_pair(T1 x, T2 y) {
	return pair<T1,T2>(x, y);
}


}
#endif
