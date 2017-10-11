#pragma once
#include "LinkedList.h"
/**
 * ��������
 */
template <typename T>
class InsertionSort
{
public:
	/**
	 * �����������
	 * @param list ����
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
	 * ��������
	 * @param data ��������
	 * @param start ��ʼ���
	 * @param end �������
	 */
	void Sort(T data[],int start,int end)
	{
		Sort(data+start,end-start+1);
	}
	/**
	 * ��������
	 * @param data ��������
	 * @param length ���鳤��
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
	 * ָ��Ĳ�������
	 * @param data ָ������
	 * @param length ���鳤��
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
	 * ����ָ��������������
	 * @param data ��������
	 * @param length ���鳤��
	 * @param compare �ȽϺ���
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

