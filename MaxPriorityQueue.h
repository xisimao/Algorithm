#pragma once
#include "Heap.h"

//利用堆实现的优先队列
template<typename T>
class MaxPriorityQueue
{
public:
	MaxPriorityQueue()
		:_heapSize(0)
	{
		_data=new T[100];
	}
	~MaxPriorityQueue()
	{}

	void MaxPriorityQueue::Insert(int value)
	{
		_heapSize++;
		int index=_heapSize-1;

		_data[index]=value;

		int parentIndex=_heap.Parent(index);
		while(index>0&&_data[_heap.Parent(index)]<_data[index])
		{
			_heap.Swap(_data,_heap.Parent(index),index);
			index=_heap.Parent(index);
		}
	}

	int MaxPriorityQueue::Maximum()
	{
		return _data[0];
	}
	int MaxPriorityQueue::ExtractMax()
	{
		int max=_data[0];
		_data[0]=_data[--_heapSize];
		_heap.MaxHeapIfy(_data,0,_heapSize);
		return max;
	}

private:
	int* _data;
	int _heapSize;
	Heap<int> _heap;
};

