 
#pragma once

 
template<class T>
struct LinkNode {
	T data;
	LinkNode * link;
	LinkNode(LinkNode<T> *ptr = nullptr) :link(ptr) { }
	LinkNode(const T& item, LinkNode <T> *ptr = nullptr) :data(item), link(ptr) {}
};


 
template <class T>
class List{
protected:
	LinkNode<T> * first;
public:
	List() { first = new LinkNode<T>; }
	List(const T& x) { first = new LinkNode<T>(x); }
	List(List<T>& L);
	List(List<T>&& L);
	~List();
	void makeEmpty();
	int Length()const;
	LinkNode<T> * getHead()const { return first; }
	int Search(const T& x)const;
	int Locate(int i)const;
	LinkNode<T> * SearchNode(const T& x)const;
	LinkNode<T> * LocateNode(int i)const;
	bool getData(int i, T& x)const;
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty()const { return first->link == nullptr ? true : false; }
	bool IsFull()const { return first->link != nullptr ? true : false; }//非空就视为已满
	bool Remove(T & x);
	void inputRear(T& flag);
	void inputFront(T& flag);
	void input();
	void output()const;
	void reverse();
	List<T>& operator=(List<T>& L);
	List<T>& operator=(List<T>&& L);
};



template<class T>
List<T>::List(List<T> &L) {
	T value;
	LinkNode<T> *srcptr = L.getHead();
	LinkNode<T> *desptr = first = new LinkNode<T>;
	while (src->link != nullptr) {
		value = srcptr->link->data;
		desptr->link = new LinkNode<T>(value);
		desptr = desptr->link;
		srcptr = src->link;
	}
}

template<class T>
List<T>::List(List<T> &&L) {
	T value;
	first = L.first;
	L.first = nullptr;
}

template<class T>
List<T>::~List() {
	LinkNode<T> *del;
	while (first != nullptr) {
		del = first;
		first = first->link;
		delete del;
	}
}

template<class T>
void List<T>::makeEmpty() {
	LinkNode<T> *del;
	while (first->link != nullptr) {
		del = first->link;
		first->link = del->link;
		delete del;
	}
}

template<class T>
int List<T>::Length()const {
	int count = 0;
	LinkNode<T> *ptr = first;
	while (ptr->link != nullptr) {
		++count;
		ptr = ptr->link;
	}
	return count;
}

 
template<class T>
int List<T>::Search(const T& x)const {
	int cnt = -1;
	LinkNode<T> * p = first->link;
	while (p != nullptr) {
		++cnt;
		if (x == p->data) return  cnt;
		p = p->link;
	}
	return -1;
}

 
template<class T>
int List<T>::Locate(int i)const {
	if (i <= 0) return -1;
	LinkNode<T> *p = first;
	int n = i;
	while (n--) {
		p = p->link;
		if (p == nullptr) return -1;
	}
	return i - 1;
}

 
template<class T>
inline LinkNode<T>* List<T>::SearchNode(const T & x) const
{
	LinkNode<T> * p = first->link;
	while (p != nullptr) {
		if (x == p->data) return p;
		p = p->link;
	}
	return nullptr;
}

 
template<class T>
inline LinkNode<T>* List<T>::LocateNode(int i) const
{
	LinkNode<T> *p = first;
	if (i <= 0) return nullptr;
	while (i--) {
		p = p->link;
		if (p == nullptr) return nullptr;
	}
	return p;
}


template<class T>
bool List<T>::getData(int i, T& x)const {
	if (i <= 0) return false;
	LinkNode<T> *p = first;
	while (i--) {
		p = p->link;
		if (p == nullptr) return false;
	}
	x = p->data;
	return true;
}

template<class T>
void List<T>::setData(int i, T& x) {
	if (i <= 0) return;
	LinkNode<T> *p = first;
	while (i--) {
		p = p->link;
		if (p == nullptr) return;
	}
	p->data = x;
}

template<class T>
bool List<T>::Insert(int i, T& x) {
	if (i < 0) return false;
	LinkNode<T> *p = first;
	while (i--) {
		p = p->link;
		if (p == nullptr) return false;
	}
	LinkNode<T> *q = new LinkNode<T>(x, p->link);
	p->link = q;
	return true;
}

template<class T>
inline bool List<T>::Remove(int i, T& x) {
	if (--i < 0) return false;
	LinkNode<T> *p = first;
	while (i--) {
		p = p->link;
		if (p == nullptr || p->link == nullptr) return false;
	}
	LinkNode<T> *del = p->link;
	p->link = del->link;
	x = del->data;
	delete del;
	return true;
}

template<class T>
bool List<T>::Remove(T &x) {
	LinkNode<T> *p, *del;
	p = first;
	bool flag = false;
	while (p->link != nullptr) {
		if (p->link->data == x) {
			del = p->link;
			p->link = del->link;
			delete del;
			flag = true;
		}
		else p = p->link;
	}
	return flag;
}


template<class T>
void List<T>::inputRear(T& flag)
{
	LinkNode<T> *last = first;
	T val;
	makeEmpty();
	cin >> val;
	while (val != flag) {
		last->link = new LinkNode<T>(val);
		last = last->link;
		cin >> val;
	}
}

template<class T>
void List<T>::inputFront(T& flag) {
	T val;
	cin >> val;
	while (val != flag) {
		first->link = new LinkNode<T>(val, first->link);
		cin >> val;
	}
}

template<class T>
void List<T>::input() {
	T flag;
	cout << "请输入结束标记:";
	cin >> flag;
	cout << "开始输入：";
	inputRear(flag);
}

template<class T>
void List<T>::output()const {
	LinkNode<T> *p = first->link;
	int cnt = 0;
	while (p != nullptr) {
		cout << "#" << ++cnt << '\t' << p->data << endl;
		p = p->link;
	}
}

template<class T>
inline void List<T>::reverse()
{
	LinkNode<T> *des, *p, *tmp;
	des = new LinkNode<T>();
	 
	p = first->link;
	while (p != nullptr) {
		tmp = p->link;
		p->link = des->link;
		des->link = p;
		p = tmp;
	}
	delete first;
	first = des;
}


template<class T>
List<T>& List<T>::operator=(List<T>& L) {
	makeEmpty();
	LinkNode<T> *p = first, *q = L.first->link;
	T value;
	while (q != nullptr) {
		value = q->data;
		p->link = new LinkNode(value);
		p = p->link;
		q = q->link;
	}
	return *this;
}

template<class T>
List<T>& List<T>::operator=(List<T>&& L) {
	makeEmpty();
	delete first;
	first = L.first;
	L.first = nullptr;
}

 

