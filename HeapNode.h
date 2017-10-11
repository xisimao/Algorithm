#pragma once
template<typename T>
class HeapNode
{
public:
	HeapNode()
		:Parent(NULL),Child(NULL),Left(NULL),Right(NULL),IsDeleteOneChild(false),Degree(0)
	{

	}
	~HeapNode()
	{

	}
	T Key;
	HeapNode* Parent;
	HeapNode* Child;
	HeapNode* Left;
	HeapNode* Right;
	int Tag;
	/**
	 * 子结点的数量
	 */
	int Degree;
	/**
	 * 是否已经删除了一个结点
	 */
	bool IsDeleteOneChild;
};

