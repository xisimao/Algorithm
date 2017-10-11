#pragma once
#include "LinkedList.h"
/**
 * 插入排序
 */
template <typename T>
class InsertionSort
{
public:
	/**
	 * 链表插入排序
	 * @param list 链表
	 */
	void Sort(LinkedList<T>* list)
	{
		LinkedListNode<T>* key=list->GetFirst()->Next;
		while(key!=NULL)
		{
			LinkedListNode<T>* pre=key->Pre;
			while(pre!=NULL&&pre->Key>key->Key)
			{
				pre=pre->Pre;
			}
			LinkedListNode<T>* next=key->Next;
			if(key->Pre!=pre)
			{
				list->Remove(key);
				list->AddAfter(pre,key);
			}
			key=next;
		}
	}
	/**
	 * 插入排序
	 * @param data 数据数组
	 * @param start 起始序号
	 * @param end 结束序号
	 */
	void Sort(T data[],int start,int end)
	{
		Sort(data+start,end-start+1);
	}
	/**
	 * 插入排序
	 * @param data 数组数据
	 * @param length 数组长度
	 */
	void Sort(T data[],int length)
	{
		for(int i=1;i<length;++i)
		{
			T key=data[i];
			int j=i-1;
			while(j>=0&&data[j]>key)
			{
				data[j+1]=data[j];
				j--;
			}
			data[j+1]=key;
		}
	}
	/**
	 * 指针的插入排序
	 * @param data 指针数组
	 * @param length 数组长度
	 */
	void SortP(T data[],int length)
	{
		for(int i=1;i<length;++i)
		{
			T key=data[i];
			int j=i-1;
			while(j>=0&&(*data[j])>(*key))
			{
				data[j+1]=data[j];
				j--;
			}
			data[j+1]=key;
		}
	}
	/**
	 * 根据指定方法插入排序
	 * @param data 数据数组
	 * @param length 数组长度
	 * @param compare 比较函数
	 * @return 
	 */
	void Sort(T data[],int length,int (*compare)(T,T))
	{
		for(int i=1;i<length;++i)
		{
			T key=data[i];
			int j=i-1;
			while(j>=0&&compare(data[j],key)>0)
			{
				data[j+1]=data[j];
				j--;
			}
			data[j+1]=key;
		}
	}
	 
};

