#pragma once
#include <stdlib.h> 


//堆
template <typename T>
class Heap
{
public:
	Heap(void)
	{
	}
	~Heap(void)
	{
	}
public:
	//维护最大堆性质
	//从上到下递归向上移动结点，保证某条路下的结点都能满足特性
	void MaxHeapIfy(T data[],int index,int heapSize)
	{
		int left=Left(index);
		int right=Right(index);
		int largest=index;
		//这里必须有堆的尺寸判断，因为如果用数组长度，会造成之后排序好后，又把最后的部分顶上来
		if(left<heapSize&&data[left]>data[index])
		{
			largest=left;
		}
		if(right<heapSize&&data[right]>data[largest])
		{
			largest=right;
		}

		if(largest!=index)
		{
			Swap(data,index,largest);
			//这里的largest其实是交换过的小数序号
			MaxHeapIfy(data,largest,heapSize);
		}
	}
	//构建最大堆
	//从下到上根据每一个结点维护堆性质，这样就能保证整个堆都是满足特性的
	void BuildMaxHeap(T data[],int length)
	{
		for(int i=length/2-1;i>=0;--i)
		{
			MaxHeapIfy(data,i,length);
		}
	}

	//维护最小堆性质
	void MinHeapIfy(T data[],int index,int heapSize)
	{
		int left=Left(index);
		int right=Right(index);
		int smallest=index;
		if(left<heapSize&&data[left]<data[index])
		{
			smallest=left;
		}
		if(right<heapSize&&data[right]<data[smallest])
		{
			smallest=right;
		}
		if(smallest!=index)
		{
			Swap(data,index,smallest);
			MinHeapIfy(data,smallest,heapSize);
		}
	}
	//构建最小堆
	void BuildMinHeap(T data[],int length)
	{
		for(int i=length/2-1;i>=0;--i)
		{
			MinHeapIfy(data,i,length);
		}
	}
	int inline Parent(int index)
	{
		return (index-1)/2;
	}
	void inline Swap(T data[],int index1,int index2)
	{
		T temp=data[index1];
		data[index1]=data[index2];
		data[index2]=temp;
	}
private:
	int inline Left(int index)
	{
		return index*2+1;
	}

	int inline Right(int index)
	{
		return index*2+2;
	}

	

};

