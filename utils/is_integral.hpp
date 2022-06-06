#ifndef is_integral_HPP
# define is_integral_HPP

# include <uchar.h>

/* is_integral<T>는 자료형 T가 정수형인지 여부를 판별하는 bool value를 멤버상수로 갖는다.
 * operator bool() 은 객체 자신이 bool 로 암시적 형변환될 때 쓰임.
 * if (is_integral<int>::value)   또는 if (is_integral<int>() )
 * https://stackoverflow.com/questions/4600295/what-is-the-meaning-of-operator-bool-const
 */

/* const, volatile qualifier가 들어와도 정확한 작동을 보장하기 위해 remove_cv도 추가.
 * is_integral<T>는 is_integral_helper<T without cv> 를 상속받고,
 * T without cv 의 타입에 따라 true_type{} 또는 false_type{}으로 인스턴스화한다.
 */

namespace ft {

struct true_type {
	static const bool value = true;
	operator bool() const { return value;}
};

struct false_type {
	static const bool value = false;
	operator bool() { return value;}
};


template <typename T>
struct remove_cv 					{ typedef T	type;};

template <typename T>
struct remove_cv<const T>			{ typedef T	type;};

template <typename T>
struct remove_cv<volatile T>		{ typedef T	type;};

template <typename T>
struct remove_cv<const volatile T>	{ typedef T	type;};


template <typename T>
struct is_integral_helper : public false_type { };

template <>
struct is_integral_helper<bool> : public true_type { };

template <>
struct is_integral_helper<char> : public true_type { };

/* char16_t, char32_t는 c++11에서 추가되었기 때문에 -std=c++98 옵션으로 컴파일 불가
 * uchar.h에 각각 unsigned short int, unsigned int로 define 되어있기 때문에 굳이 필요 없을 듯 */
#if 0
template <>
struct is_integral_helper<char16_t> : public true_type { };

template <>
struct is_integral_helper<char32_t> : public true_type { };
#endif

template <>
struct is_integral_helper<wchar_t> : public true_type { };

template <>
struct is_integral_helper<signed char> : public true_type { };

template <>
struct is_integral_helper<short int> : public true_type { };

template <>
struct is_integral_helper<int> : public true_type { };

template <>
struct is_integral_helper<long int> : public true_type { };

template <>
struct is_integral_helper<long long int> : public true_type { };

template <>
struct is_integral_helper<unsigned char> : public true_type { };

template <>
struct is_integral_helper<unsigned short int> : public true_type { };

template <>
struct is_integral_helper<unsigned int> : public true_type { };

template <>
struct is_integral_helper<unsigned long int> : public true_type { };

template <>
struct is_integral_helper<unsigned long long int> : public true_type { };


template <typename T>
struct is_integral : public is_integral_helper< typename remove_cv<T>::type > { };


}
#endif
