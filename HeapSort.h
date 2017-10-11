#pragma once
#include "Heap.h"

//堆排序
template<typename T>
class HeapSort
{
public:
	HeapSort(void)
	{}
	~HeapSort(void)
	{}

	void Sort(T data[],int length)
	{
		_heap.BuildMaxHeap(data,length);
		//每次取堆顶数据，然后不断缩小堆的尺寸，然后在维护堆
		for(int i=length-1;i>0;--i)
		{
			_heap.Swap(data,i,0);
			_heap.MaxHeapIfy(data,0,length-(length-i));
		}
	}

private:
	Heap<T> _heap;
};

