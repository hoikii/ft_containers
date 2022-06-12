#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

/* 컨테이너 어댑터 - 다른 컨테이너의 기능을 제한하는 포장지의 역할.
 * 다른 컨테이너는 Sequence Container여야 하며 back(), push_back(), pop_back()을 필수로 포함해야 한다.
 * std::vector, std::deque, std::list가 이에 해당하며 std::stack은 기본적으로 std::deque를 사용한다.
*/

namespace ft {

template <typename T, typename Container = ft::vector<T> >
class stack {
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
		// Allocator 변경은 c++11부터 지원
	
	private:
		container_type _ctnr;
	
	public:
		stack(const container_type& ctnr = container_type()) : _ctnr(ctnr) { }
		stack(const stack& other) : _ctnr(other._ctnr) { }
		~stack() { }
		stack& operator=(const stack& rhs) {
			_ctnr = rhs._ctnr;
			return *this;
		}
		
		bool			 	empty() const				{ return _ctnr.empty(); }
		size_type			size() const				{ return _ctnr.size(); }
		value_type			top()						{ return _ctnr.back(); }
		const value_type&	top() const					{ return _ctnr.back(); }
		void 				push(const value_type& val)	{ _ctnr.push_back(val); }
		void				pop()						{ _ctnr.pop_back(); }
};

// relational operators
template <typename T, typename Cont>
bool operator==(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
	return lhs == rhs;
}

template <typename T, typename Cont>
bool operator!=(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
	return lhs != rhs;
}

template <typename T, typename Cont>
bool operator<(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
	return lhs < rhs;
}

template <typename T, typename Cont>
bool operator<=(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
	return lhs <= rhs;
}

template <typename T, typename Cont>
bool operator>(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
	return lhs > rhs;
}

template <typename T, typename Cont>
bool operator>=(const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
	return lhs >= rhs;
}



}
#endif
