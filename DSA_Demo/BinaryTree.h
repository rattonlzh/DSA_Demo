#pragma once

template<class T>
struct BinTreeNode {
	T data;
	BinTreeNode<T> *lChild, *rChild;
	BinTreeNode() :lChild(nullptr), rChild(nullptr) {}
	BinTreeNode(T &item, BinTreeNode<T> *l = nullptr,
		BinTreeNode<T> *r = nullptr) :data(item), lChild(l), rChild(r) {}
};


template<class T>
class BinaryTree
{
protected:
	BinTreeNode<T> *root;												//二叉树的根指针
	T RefValue;//数据输入停止标志
	void CreateBinTree(istream & in, BinTreeNode<T> *& subTree);		//从文件读入建树
	bool Insert(BinTreeNode<T> *& subTree, const T& x);					//插入
	void destroy(BinTreeNode<T> *& subTree);							//删除
	bool Find(BinTreeNode<T> * subTree, const T& x)const;				//查找
	BinTreeNode<T> * Copy(BinTreeNode<T> *orignode);					//复制
	int Height(BinTreeNode<T> * subTree);								//返回树高度
	int Size(BinTreeNode<T> * subTree);									//返回节点数
	BinTreeNode<T> * Parent(BinTreeNode<T> *subTree,					//返回父节点
		BinTreeNode<T> * current);										
	BinTreeNode<T> * Find(BinTreeNode<T> *subTree, const T & x) const;	//搜寻x

	void preOrder(BinTreeNode<T> & subTree,								//前序遍历
		void(*visit)(BinTreeNode<T> *p));
	void inOrder(BinTreeNode<T> & subTree,								//中序遍历
		void(*visit)(BinTreeNode<T> *p));
	void postOrder(BinTreeNode<T> & subTree,							//后序遍历
		void(*visit)(BinTreeNode<T> *p));
	void Traverse(BinTreeNode<T> * subTree, ostream& out);				//前序遍历输出
	
	friend istream& operator>>(istream& in, BinaryTree<T>& Tree) {		//重载操作：输入
		CreateBinTree(in, Tree.root);
		return in;
	}
	
	friend ostream& operator<<(ostream& out, BinaryTree<T>& Tree) {		//重载操作：输出
		out << "二叉树的前序遍历\n";
		Tree.Traverse(Tree.root, out);
		return out;
	}
public:
	BinaryTree() :root(nullptr) {}
	BinaryTree(T value) : RefValue(value), root(nullptr) {}
	BinaryTree(BinaryTree<T>& s);
	~BinaryTree() { destroy(root); }

	bool isEmpty() { return  root == nullptr ? true : false; }			//判断二叉树空否  
	BinTreeNode<T> *Parent(BinTreeNode<T> * current) {					//返回父节点
		return (root == nullptr || root == current) ? nullptr 
			: Parent(root, current);
	}
	
	BinTreeNode<T> *LeftChild(BinTreeNode<T> * current) {				//返回左节点
		return (current != nullptr) ? current->lChild 
			: nullptr;
	}
	BinTreeNode<T> *RightChild(BinTreeNode<T> * current) {				//返回右结点
		return (current != nullptr) ? current->rChild : nullptr;
	}

	int Height() { return Height(root); }								//返回树高度
	int Size() { return Size(root); }									//返回节点数
	BinTreeNode<T> * getRoot() const { return root; }					//取根
	void preOrder(void(*visit)(BinTreeNode<T> *p)) {					//前序遍历
		preOrder(root, visit);
	}
	void inOrder(void(*visit)(BinTreeNode<T> *p)) {						//中序遍历
		inOrder(root, visit); 
	}
	void postOrder(void(*visit)(BinTreeNode<T> *p)) {					//后序遍历
		postOrder(root, visit); 
	}
	void levelOrder(void(*visit)(BinTreeNode<T> *p));					//层次遍历
    bool Insert(const T& item);											//插入新元素
	BinTreeNode<T> *Find(T& item)const;									//搜索


};




template<class T>
inline bool BinaryTree<T>::Insert(BinTreeNode<T>*& subTree, const T & x)
{
	if (subTree == nullptr) return false;
	if (subTree->lChild == nullptr) {
		subTree->lChild = new BinTreeNode<T>(x);
		if (subTree->lChild == nullptr) return false;
		return true;
	}
	if (subTree->rChild == nullptr) {
		subTree->rChild = new BinTreeNode<T>(x);
		if (subTree->rChild == nullptr) return false;
		return true;
	}
	Insert(subTree->lChild, x);
}

template<class T>
inline void BinaryTree<T>::destroy(BinTreeNode<T>*& subTree)
{
	if (subTree->lChild != nullptr) destroy(subTree->lChild);
	if (subTree->rChild != nullptr) destroy(subTree->rChild);
	delete subTree;
}



template<class T>
inline BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current)
{
	if (subTree == nullptr) return nullptr;
	if (subTree->lChild == current || subTree->rChild == current)
		return current;
	BinTreeNode<T>* p;
	if (p = Parent(subTree->lChild, current) != nullptr) return p;
	else return Parent(subTree->rChild, current);
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::Find(BinTreeNode<T>* subTree, const T & x) const
{
	if (subTree == nullptr) return nullptr;
	if (subTree->data == x) return subTree;
	BinTreeNode<T>* p;
	if (p = Find(subTree->lChild, x) != nullptr) return p;
	else return Find(subTree->rChild, x);
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T>* orignode)
{
	
	if (orignode == nullptr) return nullptr;
	BinTreeNode<T>*p = new BinTreeNode<T>;
	p->data = orignode->data;
	p->lChild = Copy(orignode->lChild);
	p->rChild = Copy(orignode->rChild);
	return p;
}

template<class T>
inline int BinaryTree<T>::Height(BinTreeNode<T>* subTree)
{
	if (subTree == nullptr) return 0;
	else {
		int i = Height(subTree->lChild);
		int j = Height(subTree->rChild);
		return (i < j) ? j + 1 : i + 1;
	}
}

template<class T>
inline int BinaryTree<T>::Size(BinTreeNode<T>* subTree)
{
	if (subTree == nullptr) return 0;
	else return 1 + Size(subTree->lChild) + Size(subTree->rChild);
}

template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T>*p))
{
	if (subTree != nullptr) {
		visit(subTree);
		preOrder(subTree->lChild, visit);
		postOrder(subTree->rChild, visit);
	}
}

template<class T>
inline void BinaryTree<T>::inOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T>*p))
{
	if (subTree != nullptr) {
		inOrder(subTree->lChild, visit);
		visit(subTree);
		inOrder(subTree->rChild, visit);
	}
}

template<class T>
inline void BinaryTree<T>::postOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T>*p))
{
	if (subTree != nullptr) {
		postOrder(subTree->lChild, visit);
		postOrder(subTree->rChild, visit);
		visit(subTree);
	}
}

template<class T>
inline void BinaryTree<T>::Traverse(BinTreeNode<T>* subTree, ostream & out)
{
	if (subTree != nullptr) {
		out << subTree->data << ' ';
		Traverse(subTree->lChild, out);
		Traverse(subTree->rChild, out);
	}
}

template<class T>
inline BinaryTree<T>::BinaryTree(BinaryTree<T>& s)
{
	root = Copy(s.root);
}

template<class T>
inline void BinaryTree<T>::levelOrder(void(*visit)(BinTreeNode<T>*p))
{
	Queue<BinTreeNode<T>*> Q;
	BinTreeNode<T>* p;
	p = root;
	if (p != nullptr) Q.EnQueue(p);
	while (!Q.isEmpty()) {
		Q.DeQueue(p);
		visit(p);
		if (p->lChild != nullptr) Q.EnQueue(p->lChild);
		if (p->rChild != nullptr) Q.EnQueue(p->rChild);
	}

}

template<class T>
inline bool BinaryTree<T>::Insert(const T & item)
{
	Insert(root, item);
}

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::Find(T & item) const
{
	Find(root, item);
}	


//void BinaryTree<char>::CreateBinTree(istream& in, BinTreeNode<char>*& BT) {
//	Stack<BinTreeNode<char>*> S;
//	delete BT;
//	BinTreeNode<T> *p, *t;
//	int k;
//	T ch;
//	in >> ch;
//	while (ch != RefValue) {
//		switch (ch) {
//		case '(':
//			S.Push(p);
//			k = 1;
//			break;
//		case ')':
//			S.Pop(t);
//			break;
//		case ',':
//			k = 2;
//			break;
//		default:
//			p = new BinTreeNode<T>(ch);
//			if (BT == nullptr) BT = p;
//			else if (k == 1) {
//				S.getTop(t);
//				t->lChild = p;
//			}
//			else {
//				S.getTop(t);
//				t->rChild = p;
//			}
//
//		}
//	}
//}