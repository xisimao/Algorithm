#pragma once
#include "InsertionSort.h"

template<typename T>
class BuckedSort
{
public:
	BuckedSort(void)
	{
	}
	~BuckedSort(void)
	{
	}

	void BuckedSort::Sort(T data[],int length,int (*GetIndex)(int))
	{
		LinkedList<T>* tempLink[10]={0};
		for(int i=0;i<10;++i)
		{
			tempLink[i]=new LinkedList<T>();
		}
		for(int i=0;i<20;++i)
		{
			tempLink[GetIndex(data[i])]->AddLast(data[i]);

		}
		InsertionSort<T> is;
		for(int i=0;i<10;++i)
		{	
			is.Sort(tempLink[i]);
		}
		int index=-1;
		for(int i=0;i<10;++i)
		{
			LinkedListNode<T>* node=tempLink[i]->GetFirst();
			while(node!=NULL)
			{
				data[++index]=node->Key;
				node=node->Next;
			}
		}
	}
};
