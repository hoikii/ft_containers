#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

/* Cond가 true일 때만 멤버타입 type가 정의된다.
 *
 * SFINAE(Substitution Failure Is Not An Error): 치환 실패는 에러가 아님
 * 
 * 템플릿 선언이 template <typename T, typename = typename std::enable_if<Cond>::type> 인 경우,
 * Cond가 true라면 template <typename T, typename U = void> 로 치환되어 이하의 템플릿 함수가 오버로딩 후보군에 들어간다.
 * Cond가 false라면 enable_if<>::type 은 존재하지 않으므로 치환에 실패하지만, 이것이 컴파일 오류로 해석되지는 않고 오버로딩 후보군에서 제외될 뿐.
 * enable_if<>의 두번째 인자를 템플릿함수의 return type 또는 argument type 로 활용하는 것도 가능.
 */

template <bool Cond, typename T = void>
struct enable_if { };

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};


}

#endif
