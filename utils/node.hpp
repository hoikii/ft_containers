#ifndef NODE_HPP
# define NODE_HPP

namespace ft {

enum RB_Color {
	RED = 0,
	BLACK
};

template <typename ValueType>
struct nodeBase {
	ValueType value;
	nodeBase* left;
	nodeBase* right;
	nodeBase* parent;
	bool color;

	nodeBase() : value(), left(NULL), right(NULL), parent(NULL) { }
	nodeBase(const ValueType value, nodeBase* parent = NULL)
		: value(value), left(NULL), right(NULL), parent(parent), color(RED) { }
	~nodeBase() { left = right = parent = NULL; }
	nodeBase(const nodeBase& other) : value(other.value), left(other.left), right(other.right), parent(other.parent), color(other.color) { }

	nodeBase* next() {
		if (this->parent == NULL)
			return max(this->right);
		nodeBase* next;
		if (this->right)
		{
			next = this->right;
			while (next->left)
				next = next->left;
		}
		else
		{
			next = this;
			while (next->parent && next->parent->right == next)
				next = next->parent;
			if (next->parent)
				next = next->parent;
		}
		return next;
	}

	nodeBase* prev() {
		if (this->parent == NULL)
			return max(this->right);
		nodeBase* prev;
		if (this->left)
		{
			prev = this->left;
			while (prev->right)
				prev = prev->right;
		}
		else
		{
			prev = this;
			while (prev->parent && prev->parent->left == prev)
				prev = prev->parent;
			prev =prev->parent;
		}
		return prev;
	}

	nodeBase* max(nodeBase* cur) {
		while (cur && cur->right)
			cur = cur->right;
		return cur;
	}

	private:
	nodeBase& operator=(const nodeBase& rhs) { (void)rhs; }
};




}
#endif
