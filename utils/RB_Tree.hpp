#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "tree_interface.hpp"

/* Red-Black Tree는 삽입, 삭제를 하는 동안 다음 규칙을 준수하도록 구조를 수정하여 균형을 유지한다.
 * 1. 모든 노드는 red 또는 black이다.
 * 2. 루트 노드는 black이다.
 * 3. 리프 노드는 black이다.  (구현할 땐 모든 노드의 끝에 검은색 null leaf가 붙어있는걸로 간주)
 * 4. red의 자식은 black이다. (즉, red는 연달아 나올 수 없다)
 * 5. 임의의 한 노드로부터 하위의 리프까지 도달하는 모든 경로에는 같은 개수의 블랙노드가 있다.
 * 
 * 4와 5에 의해, root로부터 가장 먼 단말까지의 거리는 가장 가까운 곳까지의 거리의 2배를 넘지 않는다.
 * 즉, 개략적으로 균형이 잡혀 있다.
 */

namespace ft {

template <typename ValueType, typename Compare, typename Alloc>
class RB_Tree : public TreeInterface<ValueType, Compare, Alloc> {
	public:
		using TreeInterface<ValueType,Compare,Alloc>::_comp;
		using TreeInterface<ValueType,Compare,Alloc>::_alloc;
		using TreeInterface<ValueType,Compare,Alloc>::_end;
		using TreeInterface<ValueType,Compare,Alloc>::_root;
		using TreeInterface<ValueType,Compare,Alloc>::_size;
		typedef nodeBase<ValueType>		node;

		RB_Tree(Compare comp, Alloc alloc) : TreeInterface<ValueType,Compare,Alloc>(comp, alloc) { }

		RB_Tree(const RB_Tree& other) : TreeInterface<ValueType,Compare,Alloc>(other) { }

		virtual ~RB_Tree() { }

	private:
		RB_Tree() { }
		RB_Tree& operator=(const RB_Tree& rhs);

		// 탐색은 일반 BST와 동일
		virtual node* _find(node* cur, ValueType value) {
			while (cur != NULL) {
				if (_comp(value, cur->value))		// 찾으려는 key가 현재 node의 key보다 작다면
					cur = cur->left;
				else if (_comp(cur->value, value))	// 찾으려는 key가 현재 node의 key 보다 크다면
					cur = cur->right;
				else
					return cur;
			}
			return cur;
		}

		/* node 생성자에서 color=0 (RED)로 초기화됨. 이후 _rb_fix_insertion()에서 변환을 수행 */
		virtual node* _insert(node* cur, ValueType value) {
			while (1) {
				if (_comp(value, cur->value)) {			// 추가하려는 key가 현재 node의 key보다 작다면
					if (cur->left == NULL) {
						//cur->left = new node(value, cur);
						cur->left = _alloc.allocate(1);
						_alloc.construct(cur->left, node(value, cur));
						_size++;
						_rb_fix_insertion(cur->left);
						return cur->left;
					}
					else
						cur = cur->left;
				}
				else if (_comp(cur->value, value)) {	// 추가하려는 key가 현재 node의 key보다 크다면
					if ( cur->right == NULL) {
						//cur->right = new node(value, cur);
						cur->right = _alloc.allocate(1);
						_alloc.construct(cur->right, node(value, cur));
						_size++;
						_rb_fix_insertion(cur->right);
						return cur->right;
					}
					else
						cur = cur->right;
				}
				else
					return cur;
			}
		}

		node* _grandparent(node* n) {
			if (n && n != _root && n->parent && n->parent != _root)
				return n->parent->parent;
			return NULL;
		}

		node* _uncle(node* n) {
			node* g = _grandparent(n);
			if (g == NULL)
				return NULL;
			if (n->parent == g->left)
				return g->right;
			else
				return g->left;
		}

		node* _sibling(node* n) {
			if (n == n->parent->left)
				return n->parent->right;
			return n->parent->left;
		}

		void _rotate_left(node* n) {
			node* c = n->right;
			node* p = n->parent;

			if (c->left != NULL)
				c->left->parent = n;

			n->right = c->left;
			p = c;
			c->left = n;
			c->parent = p;

			if (p == _end)
				_root = c;
			else {
				if (p->left == n)
					p->left = c;
				else
					p->right = c;
			}
		}

		void _rotate_right(node* n) {
			node* c = n->left;
			node* p = n->parent;

			if (c->right != NULL)
				c->right->parent = n;

			n->left = c->right;
			p = c;
			c->right = n;
			c->parent = p;

			if (p == _end)
				_root = c;
			else {
				if (p->right == n)
					p->right = c;
				else
					p->left = c;
			}
		}

		void _rb_fix_insertion(node* n) {						
			node* p = n->parent;
			if (n == _root)	{					// 1. N이 root라면 - N을 black으로 바꾼다.
				n->color = BLACK;
				return;
			}
			else if (p->color == BLACK)	// 2. N의 부모 P가 black이라면 - 문제없음
				return;
			else {
				node* u = _uncle(n);
				if (!u)
					return;
				if (u->color == RED) {		// 3. P와 삼촌노드 U가 둘 다 red라면 - P,U를 black으로, 할아버지노드 G를 red로 바꾼다.
					p->color = BLACK;
					u->color = BLACK;
					p->parent->color = RED;
					_rb_fix_insertion(p->parent);	// G에 대해 1,2,3을 다시 적용
				}
				else {
					node* g = _grandparent(n);	// 4. P는 red, U는 black이고, G-P-N 이 꺾인 형태 (G의 left가 P, P의 right가 N)또는 (G의 right가 P, P의 left가 N)
					if ((n == p->right) && p == g->left) {
						_rotate_left(p);
						n = n->left;
					} else if ((n == p->left) && (p == g->right)) {
						_rotate_right(p);
						n = n->right;			//	P를 기준으로 왼쪽 또는 오른쪽 회전하면 case5 상태가 된다
					}
					// 5. P는 red, U는 black (G는 black)  G의 left가 P, P의 left가 N 이라면 G를 기준으로 오른쪽회전한다.
					if (n == p->left)	
						_rotate_right(g);		// 회전 후에는  P
					else						//           /  \    형태가 되는데,
						_rotate_left(g);		//          N    G   P 와 G 의 색상을 바꿔주면 N-P에 대해서 규칙4를 만족한다.
					p->color = BLACK;	//		규칙5 역시 유지되는데, 바뀌기 전 P를 포함하는 모든 경로는 G를 지나고,
					g->color = RED;				//		바뀐 후 G를 지나는 경로는 모두 P를 지나기 때문이다.

				}

			}	
		}

		/* del의 부모와 child를 서로 연결.
		 * del 이 root node라면 child를 새로운 root로 지정
		*/
		void _link_parent_child(node* del, node* child) {
			if (del == _root)
				_end->right = _root = child;
			else
			{
				if (del == del->parent->left)
					del->parent->left = child;
				else
					del->parent->right = child;
			}
			if (child != NULL)
				child -> parent = del->parent;
		}

		/* cur를 기점으로 key를 탐색, 해당 노드를 삭제 */
		virtual void _erase(node* cur, ValueType value) {
			node* del = _find(cur, value);
			if (!del)	// 삭제할 노드가 존재하지 않음
				return;

			// 삭제할 노드의 자식이 2개라면, successor의 값을 현재위치에 넣고, 실제 삭제는 successor node에서 수행한다.
			// successor는 left child가 없으므로 최대 1개의 자식노드를 갖는 노드를 삭제하는 문제로 치환할 수 있다.
			if (del->left && del->right) {
				node* successor = _find_min(del->right);	// 오른쪽 서브트리에서 최소값 찾기
				del->value = successor->value;
				del = successor;
			}


			// 삭제할 노드의 부모와 자식을 연결
			node* child = (del->left) ? del->left : del->right;
			_link_parent_child(del, child);
			/*        P                P
			        /   \             /  \
			       D     S      =>   N    S
			       \    / \         /\   / \
			        N  SL  SR           SL  SR
			       /\
			*/
			if (del->color == RED) {		// 삭제할 노드가 RED일 땐 그냥 삭제. 부모 P와 자식 N이 모두 black일 것이므로 
				_alloc.destroy(del);
				_alloc.deallocate(del, 1);
				_size--;
				return;
			}
			if (child && child->color == RED) {	// 삭제할 노드 D가 BLACK, N이 RED인 경우. 둘의 color를 바꾸고 (이제 RED가 된) D를 지우면 모든 규칙을 만족한다.
				child->color = BLACK;
				_alloc.destroy(del);
				_alloc.deallocate(del, 1);
				_size--;
				return;
			}
			_alloc.destroy(del);
			_alloc.deallocate(del, 1);
			_size--;
			_rb_fix_erase(child);
		}
		void _rb_fix_erase(node* n) {
			// D, N이 모두 BLACK 인 경우, D를 삭제함으로써 N 이하의 모든 경로의 black node의 수가 -1이 되었다.
			// case 1: N이 null leaf거나 새로운 root인 경우
			if (n == NULL || n == _root)
				return;
			// N이 non-null leaf 이고 root도 아니면 반드시 non-null leaf인 Sibling이 존재한다.
			node* s = _sibling(n);
			node* p = n->parent;
			// case 2. S가 RED인 경우 (P는 black)
			if (s->color == RED) {         // case 2. S가 RED인 경우 (P는 black)
				p->color = RED;            // S와 P의 색을 바꾸고, P를 기준으로 왼쪽회전       S
				s->color = BLACK;          /*                                             /   \           */
				if (n == p->left)          //                                            P    SR
					_rotate_left(p);       /*                                           / \               */
				else                       //                                          N   SL
					_rotate_right(p);      // 이후 case 4,5,6으로 진행
			}                              // 이 변환에 의해 N의 새로운 sibling은 BLACK이 된다.
			// case 3. P, S, S의 자식들이 모두 BLACK인 경우
			// S를 RED로 칠하면 S 이하의 모든 경로의 black node의 수가 -1이 된다.
			// 이제 P를 기준으로 rebalancing을 재수행한다.
			s = _sibling(n);
			if (p->color == BLACK && s->color == BLACK
				&& (s->left == NULL || s->left->color == BLACK)
				&& (s->right == NULL || s->right->color == BLACK))
			{
				s->color = RED;
				_rb_fix_erase(p);
				return;
			}
			// case 4. S와 자식들이 모두 black이고 P가 red라면
			// S를 red로 , P를 black으로 칠한다.
			// S 하위의 black node 수는 변화없지만 n 하위의 black node를 +1 해준다.
			if (p->color == RED && s->color == BLACK
				&& (s->left == NULL || s->left->color == BLACK)
				&& (s->right == NULL || s->right->color == BLACK))
			{
				s->color = RED;
				p->color = BLACK;
				return;
			}
			// case 5. S는 black, SL, SR이 각각 red,black인 경우                  P  
			// S를 오른쪽회전한 뒤 SL과 S의 색을 바꾸면                           N   SL S SR
			// 모든 경로의 black node는 변화 없고 case 6으로 변환된다.
			// (case 2에 의해 s는 반드시 black이다)
			//s = _sibling(n);
			if ( s->color == BLACK) {
				if (s->right->color == BLACK && s->left->color == RED) {
					s->color = RED;
					s->left->color = BLACK;
					if (n == p->left)
						_rotate_right(s);
					else if (n == p->right)
						_rotate_left(s);
				}
			}
			// case 6. S는 black, SR은 red
			// P를 왼쪽회전한 뒤 P와 S의 색을 바꾸고, SR을 black으로 칠한다.
			s = _sibling(n);
			s->color = p->color;
			p->color = BLACK;
			if (n == p->left) {
				_rotate_left(p);
				s->right->color = BLACK;
			} else {
				_rotate_right(p);
				s->left->color = BLACK;
			}
		}

		node* _find_min(node* cur) {
			while (cur->left)
				cur = cur->left;
			return cur;
		}


};




}
#endif
