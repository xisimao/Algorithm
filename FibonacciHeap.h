#pragma once
#include "HeapNode.h"
#include <limits>
#include <algorithm>
/**
 * 쳲�������
 */
class FibonacciHeap
{
public:
	FibonacciHeap(void);
	~FibonacciHeap(void);
	HeapNode<int>* Insert(int);
	/**
	* ��Ӽ�
	* �ڸ����������
	* @param key ��
	*/
	void Insert(HeapNode<int>*);
	void Delete(HeapNode<int>*);
	HeapNode<int>* Minimum();
	HeapNode<int>* ExtractMin();
	void Union(FibonacciHeap,FibonacciHeap);
	/**
	 * �������
	 * @param key ֵ
	 * @return ��㣬���δ�ҵ�����NULL
	 */
	HeapNode<int>* Search(int);
	HeapNode<int>* Search(HeapNode<int>*,int);
	void DecreaseKey(HeapNode<int>*,int);
private:
	void BuildList(HeapNode<int>*);
	void AddBefore(HeapNode<int>*,HeapNode<int>*);
	void AddChild(HeapNode<int>*,HeapNode<int>*);
	void Remove(HeapNode<int>*);
	HeapNode<int>** GetList(HeapNode<int>*,int&);

	void Consolidate();
	void Cut(HeapNode<int>*);
	void CascadingCut(HeapNode<int>*);
	/**
	 * ��Сֵ���
	 */
	HeapNode<int>* _min;
	/**
	 * ���н������
	 */
	int _count;
};

