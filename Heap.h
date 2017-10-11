#pragma once
#include <stdlib.h> 


//��
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
	//ά����������
	//���ϵ��µݹ������ƶ���㣬��֤ĳ��·�µĽ�㶼����������
	void MaxHeapIfy(T data[],int index,int heapSize)
	{
		int left=Left(index);
		int right=Right(index);
		int largest=index;
		//��������жѵĳߴ��жϣ���Ϊ��������鳤�ȣ������֮������ú��ְ����Ĳ��ֶ�����
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
			//�����largest��ʵ�ǽ�������С�����
			MaxHeapIfy(data,largest,heapSize);
		}
	}
	//��������
	//���µ��ϸ���ÿһ�����ά�������ʣ��������ܱ�֤�����Ѷ����������Ե�
	void BuildMaxHeap(T data[],int length)
	{
		for(int i=length/2-1;i>=0;--i)
		{
			MaxHeapIfy(data,i,length);
		}
	}

	//ά����С������
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
	//������С��
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

