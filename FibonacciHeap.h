#pragma once
#include "HeapNode.h"
#include <limits>
#include <algorithm>
/**
 * 斐波那契堆
 */
class FibonacciHeap
{
public:
	FibonacciHeap(void);
	~FibonacciHeap(void);
	HeapNode<int>* Insert(int);
	/**
	* 添加键
	* 在根链表中添加
	* @param key 键
	*/
	void Insert(HeapNode<int>*);
	void Delete(HeapNode<int>*);
	HeapNode<int>* Minimum();
	HeapNode<int>* ExtractMin();
	void Union(FibonacciHeap,FibonacciHeap);
	/**
	 * 搜索结点
	 * @param key 值
	 * @return 结点，如果未找到返回NULL
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
	 * 最小值结点
	 */
	HeapNode<int>* _min;
	/**
	 * 堆中结点总数
	 */
	int _count;
};

