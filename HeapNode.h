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
	 * �ӽ�������
	 */
	int Degree;
	/**
	 * �Ƿ��Ѿ�ɾ����һ�����
	 */
	bool IsDeleteOneChild;
};

