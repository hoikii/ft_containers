c++의 STL은 Standard Template Library의 약자로, 아래와 같은 구성요소로 이루어져있다.
1. container - 자료구조가 구현된 객체
2. iterator - 컨테이너의 개별 원소에 접근하고 사용할 수 있게 하는 객체
3. algorythm - sort, find 등 편의를 위한 도구들

## vector, map, stack (+ RB Tree를 사용하는 set) 과, 그에 필요한 iterator를 직접 구현한다.

* template을 사용한 일반화 프로그래밍을 집중적으로 연습
* 메모리 할당, 해제를 위해 std::allocator를 사용한다. (allocator는 메모리 관리 모델을 추상화한 클래스)
* vector<T>의 range constructor나 range assign을 올바르게 작동하게 하기 위해서 enable_if와 is_integral의 구현이 필요하다. 이 과정에서 SFINAE의 개념을 익힌다.
* 두 vector의 비교연산자는 lexicographical_compare를 사용한다.
* map이나 set은 지정한 자료형 T가 아닌 T를 포함하는 node를 element로 만들어야 한다. 이를 위해 allocator<T>를 rebind 해야 한다.
* 비교를 위해 simple BST와 Red-Black Tree를 따로 구현했다. 둘이 공통적으로 쓰는 기본 구조는 tree_interface 에서 구현하고,
Binary_Search_Tree 와 RB_Tree는 이를 상속받아와서 insert, erase등 차이가 있는 부분만 재정의하도록 했다.
* 삽입, 삭제 과정에서 언제 iterator가 무효화되는지 이해한다.



* * *
iterator는 컨테이너의 내부 요소에 접근하는 용도로 쓰이는 pointer와 비슷한 객체로,
참조연산, 다음/이전 요소로 넘어가는 ++, -- 같은 연산자 로버로드가 필요함.
반복자는 데이터에서 알고리즘을 분리해주기 때문에, 컨테이너 내부에 데이터가 어떤 방식으로 구성되어 있는지 몰라도 각 원소 또는 range에 알고리즘을 적용할 수 있다.
제공하는 기능 수준에 따라 input/output iterator, forward iterator, bidirectional iterator, random access iterator 로 나뉜다.
vector는 random access iterator를, map, list, set은 bidirectional iterator를 지원한다.
| forward  | biderectional | random_access |
|----------|---------------|---------------|
|    *     |      *        |       *       |
|    ->    |      ->       |       ->      |
|          |               |       []      |
|    ++    |      ++       |       ++      |
|          |      --       |       --      |
|          |               |       +       |
|          |               |       -       |
|          |               |       +=      |
|          |               |       -=      |
|    ==    |      ==       |       ==      |
|    !=    |      !=       |       !=      |
|          |               |       <       |
|          |               |       >       |
|          |               |       <=      |
|          |               |       >=      |



각 컨테이너들은 클래스 선언 안에 'iterator'라는 이름을 가진 타입을 제공해야 한다. 이로써 사용자는 반복자를 일관된 형태로 사용할 수 있다.

각 반복자들은
>value_type  
pointer  
reference  
difference_type  
iterator_category  

를 포함하는 iterator_traits를 제공하며, std::distance<IT> 같은 애들은 iterator_category에 따라 두 반복자 사이의 거리를 구하는 방법을 달리 한다.
(random_access_iterator라면 operator-를, 아니면 operator++를 사용하는 식으로)

