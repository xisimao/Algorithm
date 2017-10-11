#pragma once
#include "Heap.h"

//������
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
		//ÿ��ȡ�Ѷ����ݣ�Ȼ�󲻶���С�ѵĳߴ磬Ȼ����ά����
		for(int i=length-1;i>0;--i)
		{
			_heap.Swap(data,i,0);
			_heap.MaxHeapIfy(data,0,length-(length-i));
		}
	}

private:
	Heap<T> _heap;
};

