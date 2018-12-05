#pragma once
template <class T>
struct LinkNode {
	T data;
	LinkNode *link;
	LinkNode(LinkNode *ptr = nullptr):link(ptr){}
	LinkNode(T &item, LinkNode* ptr = nullptr):data(item), link(ptr){}
};

template <class T>
class Stack
{
	
public:
	Stack():top(nullptr){}
	Stack(const Stack<T> &S) : top(nullptr) {
		LinkNode<T> *p = S.top;
		while (p != nullptr) {
			top = new LinkNode<T>(p->data, top);
			p = p->link;
		}
	}
	~Stack() {
		makeEmpty();
	}
	// 判断是否为空栈
	bool isEmpty() const {
		return top == nullptr ? true : false;
	}
	// 栈的大小
	int getSize() const {
		int sz = 0;
		LinkNode<T> *p = top;
		while (p != nullptr) {
			++sz;
			p = p->link;
		}
		return sz;
	}
	// 压入栈顶
	void push(T &item) {
		top = new LinkNode<T>(item, top);
	}
	// 弹出栈顶
	bool pop(T &x) {
		if (isEmpty()) return false;
		x = top->data;
		LinkNode<T> *del = top;
		top = del->link;
		delete del;
		return true;
	}
	// 取栈顶元素
	bool getTop(T & x) const {
		if (isEmpty()) return false;
		x = top->data;
		return true;
	}
	// 清空栈
	void makeEmpty() {
		LinkNode<T> *del;
		while (top != nullptr) {
			del = top;
			top = del->link;
			delete del;
		}
	}
	Stack & operator=(const Stack & S) {
		makeEmpty();
		LinkNode<T> *p = S.top;
		while (p != nullptr) {
			top = new LinkNode<T>(p->data, top);
			p = p->link;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& os, Stack<T>& S);
private:
	LinkNode<T> *top;//指向栈顶的指针
};

template <class T>
ostream& operator<<(ostream& os, Stack<T>& S) {
	os << "栈中元素个数=" << S.getSize() << endl;
	LinkNode<T> *p = S.top;
	int i = 0;
	while (p != nullptr) {
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}