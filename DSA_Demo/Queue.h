

//Queue.h
#pragma once
const int maxSize = 50;
template <class T>
struct LinkNode
{
	T data;
	LinkNode<T> *link;
	LinkNode(const T &item, LinkNode<T> *p = nullptr) : link(p), data(item) {}
	LinkNode(LinkNode<T> *p = nullptr) : link(p) {}
};


template <class T>
class Queue
{
public:
	Queue() : Front(nullptr), rear(nullptr) {}
	~Queue()
	{
		makeEmpty();
	}

	bool isEmpty()
	{
		return Front == nullptr ? true : false;
	}

	bool getFront(T &x)
	{
		if (isEmpty())
			return false;
		x = Front->data;
		return true;
	}

	bool EnQueue(const T &x)
	{
		if (Front == nullptr) rear = Front = new LinkNode<T>(x);
		if (Front == nullptr) return false;//分配结点失败
		else
		{
			rear->link = new LinkNode<T>(x);
			if (rear->link == nullptr) return false;//分配结点失败
			rear = rear->link;
		}
		return true;
	}

	bool DeQueue(T &x)
	{
		if (isEmpty()) return false;
		LinkNode<T> * p = Front;
		x = Front->data;
		Front = Front->link;
		delete p;
		return true;
	}

	void makeEmpty()
	{
		LinkNode<T> *p;
		while (Front != nullptr)
		{
			p = Front;
			Front = Front->link;
			delete p;
		}
	}

protected:
	LinkNode<T> *Front;
	LinkNode<T> *rear;
};







