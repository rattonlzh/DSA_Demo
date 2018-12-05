//Graph.h
#pragma once

#include <iostream>
#include"Queue.h"
#include <queue>
using namespace std;
const int DefaultVertices = 30;

//基类
template <class T, class E>
class Graph {
	template<class T, class E>
	friend void DFS(Graph<T, E>& G, const T &v);
	template<class T, class E>
	friend void BFS(Graph<T, E>& G, const T &v);
public:
	const static E maxWeight = 99;
	Graph(int sz = DefaultVertices) {}
	~Graph() {}
	bool GraphEmpty()const {
		if (numEdges == 0)return true;
		else return false;
	}
	bool GraphFull()const {
		if (this->numVertices == maxVertices ||
			numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		else return false;
	}
	int NumberOfVertices() { return this->numVertices; }
	int NumberOfEdges() { return numEdges; }
	virtual T getValue(int i) = 0;
	virtual E getWeight(int v1, int v2) = 0;
	virtual int getFirstNeighbor(int v) = 0;
	virtual int getNextNeighbor(int v, int w) = 0;
	virtual bool insertVertex(const T& vertex) = 0;
	virtual bool insertEdge(int v1, int v2, E cost) = 0;
	virtual bool removeVertex(int v) = 0;
	virtual bool removeEdge(int v1, int v2) = 0;
protected:
	int maxVertices;//最大顶点数
	int numEdges;//当前边数
	int numVertices;//当前顶点数
	virtual int getVertexPos(T vertex) = 0;//给出顶点的位置
};
//派生类 邻阶矩阵
template <class T, class E>
class Graphmtx :public Graph<T, E> {
	template <class U, class V>
	friend istream& operator >> (istream& in, Graphmtx<U, V>& G);//输入
	template <class U, class V>
	friend ostream& operator <<(ostream& out, Graphmtx<U, V>& G);//输出
public:
	Graphmtx() {}
	Graphmtx(int sz = DefaultVertices);
	~Graphmtx() { delete[]VerticesList; delete[]Edge; }
	T getValue(int i) { return i >= 0 && i <= this->numVertices ? VerticesList[i] : NULL; }
	E getWeight(int v1, int v2)
	{
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	void outMatrix() {
		for (int i = 0; i < this->numVertices; ++i) {
			for (int j = 0; j < this->numVertices; j++)
			{
				if (Edge[i][j] == this->maxWeight)cout << Edge[i][j] << "  ";
				else cout << Edge[i][j] << "   ";
			}
			cout << endl;
		}
	}
private:
	T *VerticesList;
	E **Edge;
	int getVertexPos(T vertex) {

		for (int i = 0; i < this->numVertices; ++i) {
			if (VerticesList[i] == vertex)return i;
		}

		return -1;
	}
};
//边节点
template <class T, class E>
struct Edge {
	int dest;//边的另一顶点
	E cost;//边上的权值
	Edge<T, E> *link;//下一边链指针
	Edge() {}
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {}
	bool operator !=(Edge<T, E> &R)const {
		return(dest != R.dest) ? true : false;
	}
};
//顶点
template <class T, class E>
struct Vertex
{
	T data;//顶点名
	Edge<T, E> *adj;
};
//派生类 邻接表
template <class T, class E>
class Graphlnk :public Graph<T, E> {
	template <class U, class V>
	friend istream& operator >> (istream& in, Graphlnk<U, V>& G);//输入
	template <class U, class V>
	friend ostream& operator <<(ostream& out, Graphlnk<U, V>& G);//输出
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	T getValue(int i) {
		return (i >= 0 && i < this->numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E weight);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	void outTable() {
		for (int i = 0; i < this->numVertices; ++i) {
			cout << i << "  " << NodeTable[i].data << "  ";
			Edge<T, E> *p;
			p = NodeTable[i].adj;
			while (p != NULL) {
				cout << p->dest << "  ";
				p = p->link;
			}
			cout << endl;
		}
	}
private:
	Vertex<T, E> *NodeTable;
	int getVertexPos(T vertex) {
		for (int i = 0; i < this->numVertices; ++i) {
			if (NodeTable[i].data == vertex)return i;
		}
		return -1;
	}
};

template<class T, class E>
inline Graphmtx<T, E>::Graphmtx(int sz) {
	int i, j;
	this->maxVertices = sz;
	this->numVertices = 0;
	this->numEdges = 0;
	VerticesList = new T[this->maxVertices];
	Edge = (E **)new E *[this->maxVertices];
	for (i = 0; i < this->maxVertices; i++) {
		Edge[i] = new E[this->maxVertices];
	}
	for (i = 0; i < this->maxVertices; i++) {
		for (j = 0; j < this->maxVertices; j++) {
			Edge[i][j] = (i == j) ? 0 : this->maxWeight;
		}
	}
}

template<class T, class E>
inline int Graphmtx<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		for (int col = 0; col < this->numVertices; col++) {
			if (Edge[v][col] > 0 && Edge[v][col] < this->maxWeight)return col;
		}
	}
	return -1;
}

template<class T, class E>
inline int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1 && w != -1) {
		for (int col = w + 1; col < this->numVertices; col++) {
			if (Edge[v][col] > 0 && Edge[v][col] < this->maxWeight)return col;
		}
	}
	return -1;
}

template<class T, class E>
inline bool Graphmtx<T, E>::insertVertex(const T& vertx) {
	if (this->numVertices == this->maxVertices) return false;
	VerticesList[this->numVertices++] = vertx;
	return true;
}

template<class T, class E>
inline bool Graphmtx<T, E>::removeVertex(int v) {
	if (v < 0 || v >= this->numVertices)return false;
	if (this->numVertices == 1)return false;
	int i, j;
	VerticesList[v] = VerticesList[this->numVertices - 1];
	for (i = 0; i < this->numVertices; i++)
		if (Edge[i][v] > 0 && Edge[i][v] < this->maxWeight)this->numEdges--;
	for (i = 0; i < this->numVertices; i++)
		Edge[i][v] = Edge[i][this->numVertices - 1];
	this->numVertices--;
	for (j = 0; j < this->numVertices; j++)
		Edge[v][j] = Edge[this->numVertices][j];
	return true;
}

template<class T, class E>
inline bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
	if (v1 > -1 && v1<this->numVertices&&v2>-1 && v2 < this->numVertices&&Edge[v1][v2] == this->maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = cost;
		this->numEdges++;
		return true;
	}
	else return false;
}

template<class T, class E>
inline bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
	if (v1 > -1 && v1<this->numVertices&&v2>-1 && v2 < this->numVertices&&Edge[v1][v2]>0
		&& Edge[v1][v2] < this->maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = this->maxWeight;
		this->numEdges--;
		return true;
	}
	else return false;
}
//邻阶矩阵 输入
template<class U, class V>
inline istream & operator >> (istream & in, Graphmtx<U, V>& G)
{
	int i, j, k, n, m;
	U e1, e2;
	V weight;
	cout << "请输入顶点数和边数：";
	in >> n >> m;//输入顶点数和边数
	for (i = 0; i < n; ++i) {
		in >> e1; G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "边两端信息有误，请重新输入" << endl;
		else {
			G.insertEdge(j, k, weight); i++;
		}
	}
	return in;
}
//邻阶矩阵 输出
template<class U, class V>
inline ostream & operator << (ostream & out, Graphmtx<U, V>& G)
{
	int i, j, n, m;
	U e1, e2;
	V w;
	n = G.NumberOfVertices(); m = G.NumberOfEdges();
	cout << "边数:" << n << endl;
	out << "顶点数" << m << endl;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			w = G.getWeight(i, j);

			if (w > 0 && w < G.maxWeight) {
				e1 = G.getValue(i); e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return out;
}
//邻阶表 输入
template<class U, class V>
inline istream & operator>>(istream & in, Graphlnk<U, V>& G)
{
	int i, j, k, n, m;
	U e1, e2;
	V weight;
	cout << "请输入顶点数和边数：";
	in >> n >> m;//输入顶点数和边数
	for (i = 0; i < n; ++i) {
		in >> e1; G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "边两端信息有误，请重新输入" << endl;
		else {
			G.insertEdge(j, k, weight); i++;
		}
	}
	return in;
}
//邻阶表 输出
template<class U, class V>
inline ostream & operator<<(ostream & out, Graphlnk<U, V>& G)
{
	int i, j, n, m;
	U e1, e2;
	V w;
	n = G.NumberOfVertices(); m = G.NumberOfEdges();
	cout << "边数:" << n << endl;
	out << "顶点数" << m << endl;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			w = G.getWeight(i, j);

			if (w > 0 && w < G.maxWeight) {
				e1 = G.getValue(i); e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return out;
}

template<class T, class E>
inline Graphlnk<T, E>::Graphlnk(int sz)
{
	this->maxVertices = sz; this->numVertices = 0; this->numEdges = 0;
	NodeTable = new Vertex<T, E>[this->maxVertices];
	if (NodeTable == NULL) { cerr << "储存分配错误！" << endl; exit(0); }
	for (int i = 0; i < this->maxVertices; i++)NodeTable[i].adj = NULL;
}

template<class T, class E>
inline Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i < this->numVertices; i++) {
		Edge<T, E> *p = NodeTable[i].adj;
		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p; p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}

template<class T, class E>
inline int Graphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v != -1) {
		Edge<T, E> *p = NodeTable[v].adj;
		if (p != NULL)return p->dest;
	}
	return -1;
}

template<class T, class E>
inline int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
	if (v != -1) {
		Edge<T, E> *p = NodeTable[v].adj;
		while (p != NULL && p->dest != w) p = p->link;
		if (p != NULL && p->link != NULL)return p->link->dest;
	}
	return -1;
}

template<class T, class E>
inline E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1) {
		Edge<T, E> *p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)p = p->link;
		if (p != NULL)return p->cost;
	}
	return 0;
}

template<class T, class E>
inline bool Graphlnk<T, E>::insertVertex(const T & vertex)
{
	if (this->numVertices == this->maxVertices)return false;
	NodeTable[this->numVertices].data = vertex;
	this->numVertices++; return true;
}

template<class T, class E>
inline bool Graphlnk<T, E>::removeVertex(int v)
{
	if (this->numVertices == 1 || v < 0 || v >= this->numVertices)return false;
	Edge<T, E> *p, *s, *t;
	int  k;
	while (NodeTable[v].adj != NULL) {
		p = NodeTable[v].adj; k = p->dest;
		s = NodeTable[k].adj; t = NULL;
		while (s != NULL && s->dest != v) {
			t = s; s = s->link;
		}
		if (s != NULL) {
			if (t == NULL)NodeTable[k].adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p; this->numEdges--;
	}
	this->numVertices--;
	NodeTable[v].data = NodeTable[this->numVertices].data;
	p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
	while (p != NULL) {
		s = NodeTable[p->dest].adj;
		while (s != NULL) {
			if (s->dest == this->numVertices) { s->dest = v; break; }
			else s = s->link;
		}
	}
	return true;
}

template<class T, class E>
inline bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
	if (v1 >= 0 && v1 < this->numVertices&&v2 >= 0 && v2 < this->numVertices) {
		Edge<T, E> *q, *p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL) return false;
		p = new Edge<T, E>; q = new Edge<T, E>;
		p->dest = v2; p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1; q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		this->numEdges++; return true;
	}
	return 0;
}

template<class T, class E>
inline bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 != -1 && v2 != -1) {
		Edge<T, E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
		while (p != NULL && p->dest != v2) {
			q = p; p = p->link;
		}
		if (p != NULL) {
			if (p == s)NodeTable[v1].adj = p->link;
			else q->link = p->link;
			delete p;
		}
		else return false;
		p = NodeTable[v2].adj; q = NULL; s = p;
		while (p->dest != v1) { q = p; p = p->link; }
		if (p == s)NodeTable[v2].adj = p->link;
		else q->link = p->link;
		delete p;
		return true;
	}
	return false;
}
//DFS遍历
template<class T, class E>
void DFS(Graph<T, E>& G, const T &v) {
	int i, loc, n = G.NumberOfVertices();
	bool *visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	loc = G.getVertexPos(v);
	DFS(G, loc, visited);
	delete[]visited;
}

template<class T, class E>
void DFS(Graph<T, E>& G, int v, bool visited[]) {
	int w = G.getFirstNeighbor(v);
	cout << G.getValue(v) << ' ';
	visited[v] = true;
	
	while (w != -1) {
		if (visited[w] == false)DFS(G, w, visited);
		w = G.getNextNeighbor(v, w);
	}
}
//BFS遍历
template<class T, class E>
void BFS(Graph<T, E>& G, const T &v) {
	int i, w, n = G.NumberOfVertices();
	bool *visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	int loc = G.getVertexPos(v);
	cout << G.getValue(loc) << ' ';
	visited[loc] = true;
	Queue<int> Q; Q.EnQueue(loc);
	while (!Q.isEmpty()) {
		Q.DeQueue(loc);
		w = G.getFirstNeighbor(loc);

		while (w != -1) {
			if (visited[w] == false) {
				cout << G.getValue(w) << ' ';
				visited[w] = true;
				Q.EnQueue(w);
			}
			w = G.getNextNeighbor(loc, w);
		}

	}
	delete[]visited;
}
