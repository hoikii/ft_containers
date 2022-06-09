#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>

#ifdef STD
	#include <iterator>
	#include <type_traits>
	namespace ft = std;
#else
	#include "vector.hpp"
	#include "utils/reverse_iterator.hpp"
	#include "utils/is_integral.hpp"
#endif

void prn_vec(ft::vector<int> &v) {
	std::cout << "(" << v.size() << "/" << v.capacity() << ") ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	std::cout << "\n\n";
}


int main() {
#ifdef STD
	std::cout << "Test for STD\n";
#else
	std::cout << "Test for FT\n";
#endif

	std::cout << "빈 벡터 선언: ";
	ft::vector<int> v;
	std::cout << "size, capacity = (" << v.size() << " / " << v.capacity() << ")\n";
	std::cout << "max_size of v<int>: " << v.max_size() << "\n\n";

	std::cout << "fill\n";
	ft::vector<int> v2(5, 42);
	prn_vec(v2);

	std::cout << "copy constructor\n";
	ft::vector<int> v3(v2);
	prn_vec(v3);

	std::cout << "assign\n";
	v = v3;
	prn_vec(v);


	std::cout << "10회 push_back()\n";
	for (size_t i = 1; i <= 10; i++)
		v.push_back(i);
	prn_vec(v);

	std::cout << "현재size보다 작은 값으로 resize - resize(3)\n";
	v.resize(3);
	prn_vec(v);
	std::cout << "현재size보다 큰 값으로 resize 하면서 초기화 - resize(5, 21)\n";
	v.resize(5,21);
	prn_vec(v);
	std::cout << "현재capacity보다 큰 값으로 resize - resize(30)\n";
	v.resize(30);
	prn_vec(v);
	std::cout << "현재capacity보다 큰 값으로 reserve - reserve(50)\n";
	v.reserve(50);
	prn_vec(v);
	std::cout << "현재capacity보다 작은 값으로 reserve - reserve(3)\n";
	v.reserve(3);
	prn_vec(v);
	std::cout << "20회 pop_back()\n";
	for (int i = 0; i < 20; i++)
		v.pop_back();
	prn_vec(v);
	std::cout << "clear (size는 0이 되지만 capacity는 그대로)\n";
	v.clear();
	prn_vec(v);

	std::cout << "===== swap test =====\n";
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	std::cout << "--- before ---\n";
	prn_vec(v);
	prn_vec(v2);
	std::cout << "--- after v1.swap(v2) ---\n";
	v.swap(v2);
	prn_vec(v);
	prn_vec(v2);
	std::cout << "--- non-member swap ---\n";
	ft::swap(v, v2);
	prn_vec(v);
	prn_vec(v2);

	std::cout << "at() 으로 assign\n";
	for (int i = 0; i < 10; i++)
		v.at(i) = 9 - i;
	prn_vec(v);

	std::cout << "at()은 boundary check를 하고 out_of_range를 throw한다\n";
	try {
		v.at(100) = 20;
	} catch (std::out_of_range &e) { std::cout << "out_of_range error: " << e.what() << "\n"; }

	std::cout << "\n\niterator로 순회\n";
	ft::vector<int>::iterator it = v.begin();
	ft::vector<int>::iterator ite = v.end();
	for (; it != ite; it++)
		std::cout << *it << " ";
	std::cout << '\n';
	it = v.begin();
	std::cout << "\n *(v.begin() + 3)     = " << *(v.begin() + 3);
	std::cout << "\n *(3 + v.begin())     = " << *(3 + v.begin());
	std::cout << "\n *(v.end() - 3)       = " << *(ite - 3);
	std::cout << "\n v.end() - v.begin()  = " << v.end() - v.begin() << std::endl;

	std::cout << "get_allocator = ";
	std::cout << typeid(v.get_allocator()).name() << "\n\n";
	

	std::cout << "iterator_traits of vector<int>::iterator\n";
	typedef ft::vector<int>::iterator itType;
	std::cout << "typename of iterator: " << typeid(itType).name() << std::endl;
	std::cout << "valuetype of iterator: " << typeid(ft::iterator_traits<itType>::value_type).name() << std::endl;
	std::cout << "pointer of iterator: " << typeid(ft::iterator_traits<itType>::pointer).name() << std::endl;
	std::cout << "reference of iterator: " << typeid(ft::iterator_traits<itType>::reference).name() << std::endl;
	std::cout << "differencetype of iterator: " << typeid(ft::iterator_traits<itType>::difference_type).name() << std::endl;
	std::cout << "category of iterator: " << typeid(ft::iterator_traits<itType>::iterator_category).name() << std::endl;


{
	std::cout << "test for reverse iterator\n";
	for (int i =0; i<10; i++)
		v[i] = i;
	prn_vec(v);
	ft::vector<int>::reverse_iterator rev_begin = v.rbegin();
	ft::vector<int>::reverse_iterator rev_end = v.rend();
	std::cout << "*rbegin()	= " << *rev_begin << "\n";
	std::cout << "*(rend()-2)	= " << *(rev_end-2) << "\n";
	std::cout << "size		= " << v.size() << "\n";
	std::cout << "end  -  begin	= " << v.end() - v.begin() << "\n";
	std::cout << "rend - rbegin	= " << v.rend() - v.rbegin() << "\n";
	while (rev_begin != rev_end)
		std::cout << ' ' << *rev_begin++;
	std::cout << "\n\n";
}

	// std::is_integral 은 -std=c++98옵션으로 테스트 불가
	std::cout << "===== is_integral test =====\n";
	std::cout << "int: " << std::boolalpha << ft::is_integral<int>() << "\n";
	std::cout << "float: " << ft::is_integral<float>::value << "\n";
	std::cout << "const int: " << ft::is_integral<const int>::value << "\n\n";


{
	std::cout << " === initialize by iterator ===\n";
	ft::vector<int> v2(v.begin() + 3, v.end() - 4);
	prn_vec(v2);
}

{
	std::cout << " === initialize by std::list<>::iterator ===\n";
	std::list<int> tmp(5, 42);
	ft::vector<int> v2(tmp.begin(), tmp.end());
	prn_vec(v2);
}

{
	std::cout << "=== assign(fill) ===\n";
	ft::vector<int> tmp(10, 0);
	tmp.assign(3, 42);
	prn_vec(tmp);
}

{
	std::cout << "=== assign(range) by std::list<>::iterator ===\n";
	ft::vector<int> tmp(10, 0);
	std::list<int> lst(15, 42);
	tmp.assign(lst.begin(), lst.end());
	prn_vec(tmp);
}
	std::cout << "=== erase ===\n";
	//ft::vector<int>::iterator it = v.erase(v.end() - 3);
	it = v.erase(v.end() - 3);
	std::cout << "return value points to " << *it << " ";
	prn_vec(v);

	std::cout << "=== erase range ===\n";
	v.erase(v.begin()+3, v.begin()+5);
	prn_vec(v);

	std::cout << "=== insert(fill) ===\n";
	v.insert(v.begin() + 3, 3, 42);
	prn_vec(v);

{
	std::cout << "=== insert(range) by std::list<>::iterator ===\n";
	ft::vector<int> tmp;
	std::list<int> lst(15, 42);
	tmp.insert(tmp.begin(), lst.begin(), lst.end());
	prn_vec(tmp);
}

	std::cout << "=== compare two vectors ===\n";
	{
		ft::vector<int> foo(3, 100);
		ft::vector<int> bar(2, 200);
		std::cout << (foo < bar) << "\n";
	}
	{
		int a1[] = {1,2,3,4,5};
		int a2[] = {1,2,3,4,5};
		ft::vector<int> v1(a1, a1 + 5);
		ft::vector<int> v2(a2, a2 + 6);
		std::cout << (v1==v2) << "\n";
		std::cout << (v1!=v2) << "\n";
		std::cout << (v1<v2) << "\n";
		std::cout << (v1<=v2) << "\n";
		std::cout << (v1>v2) << "\n";
		std::cout << (v1>=v2) << "\n";
	}
	{
		int a1[] = {1,2,3,4,5};
		int a2[] = {1,2,3,4,6};
		ft::vector<int> v1(a1, a1 + 5);
		ft::vector<int> v2(a2, a2 + 6);
		std::cout << (v1==v2) << "\n";
		std::cout << (v1!=v2) << "\n";
		std::cout << (v1<v2) << "\n";
		std::cout << (v1<=v2) << "\n";
		std::cout << (v1>v2) << "\n";
		std::cout << (v1>=v2) << "\n";
	}
	{
		int a1[] = {1,2,3,4,5};
		int a2[] = {1,2,3,4,5,6};
		ft::vector<int> v1(a1, a1 + 5);
		ft::vector<int> v2(a2, a2 + 6);
		std::cout << (v1==v2) << "\n";
		std::cout << (v1!=v2) << "\n";
		std::cout << (v1<v2) << "\n";
		std::cout << (v1<=v2) << "\n";
		std::cout << (v1>v2) << "\n";
		std::cout << (v1>=v2) << "\n";
	}
	{
		int a1[] = {1,2,3,4,5};
		int a2[] = {1,2,3,4};
		ft::vector<int> v1(a1, a1 + 5);
		ft::vector<int> v2(a2, a2 + 4);
		std::cout << (v1==v2) << "\n";
		std::cout << (v1!=v2) << "\n";
		std::cout << (v1<v2) << "\n";
		std::cout << (v1<=v2) << "\n";
		std::cout << (v1>v2) << "\n";
		std::cout << (v1>=v2) << "\n";
	}
}
