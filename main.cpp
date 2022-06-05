#include <iostream>
#include <iterator>
#include <typeinfo>
#ifdef STD
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif


int main() {
#ifdef STD
	std::cout << "Test for STD\n";
#else
	std::cout << "Test for FT\n";
#endif

	ft::vector<int> vector_int;
	std::cout << "max_size of v<int>: " << vector_int.max_size() << std::endl;
	std::cout << "size, capacity = " << vector_int.size() << ", " << vector_int.capacity() << std::endl;

	for (size_t i = 1; i < 10; i++)
		vector_int.push_back(i);
	vector_int.resize(5);
	vector_int.resize(8,100);
	vector_int.resize(12);
	std::cout << "size, capacity = " << vector_int.size() << ", " << vector_int.capacity() << std::endl;
	for (size_t i = 1; i < vector_int.size(); i++)
		std::cout << vector_int[i] << " ";
	std::cout << "\n";
	vector_int.clear();
	std::cout << "size, capacity = " << vector_int.size() << ", " << vector_int.capacity() << std::endl;



	ft::vector<int> v(10,3);
	std::cout << "siz=" << v.size() << std::endl;
	std::cout << typeid(v.get_allocator()).name() << std::endl;
	for (size_t i = 1; i < v.size(); i++)
		std::cout << v[i] << " ";




	return 0;
#if 0
	typedef std::vector<int>::iterator itType;
	itType it;

	std::cout << "typename of iterator: " << typeid(itType).name() << std::endl;
	std::cout << "category of iterator: " << typeid(itType::iterator_category).name() << std::endl;
	std::cout << "valuetype of iterator: " << typeid(itType::value_type).name() << std::endl;
	std::cout << "typename of data that iterator points to: " << typeid(*it).name() << std::endl;


	typedef RandomAccessIterator<int> citType;
	citType cit;

	std::cout << "\n\n";
	std::cout << "typename of iterator: " << typeid(citType).name() << std::endl;
//	std::cout << "category of iterator: " << typeid(citType::iterator_category).name() << std::endl;
	std::cout << "valuetype of iterator: " << typeid(citType::value_type).name() << std::endl;
//	std::cout << "typename of data that iterator points to: " << typeid(*cit).name() << std::endl;
#endif
}
