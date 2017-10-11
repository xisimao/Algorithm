#pragma once
#include "Heap.h"
template<typename T>
class MinPriorityQueue
{
public:
	MinPriorityQueue()
		:_heapSize(0)
	{
		_data=new T[100];
	}
	~MinPriorityQueue(void)
	{
		delete[] _data;
	}

	T MinPriorityQueue::Minimum()
	{
		return _data[0];
	}

	T MinPriorityQueue::ExtractMin()
	{
		T min=_data[0];
		_data[0]=_data[--_heapSize];
		_heap.MinHeapIfy(_data,0,_heapSize);
		return min;
	}

	void MinPriorityQueue::Insert(T value)
	{
		_heapSize++;
		int index=_heapSize-1;
		_data[index]=value;
		while(index>0&&_data[_heap.Parent(index)]>_data[index])
		{
			_heap.Swap(_data,_heap.Parent(index),index);
			index=_heap.Parent(index);
		}
	}
private:
	T* _data;
	int _heapSize;
	Heap<T> _heap;

};

