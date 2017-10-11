#pragma once
#include <limits>
#include <math.h>

/**
 * �鲢����
 */
template <typename T>
class MergeSort
{
public:
	/**
	 * �ϲ�
	 * @param data ��������
	 * @param start ��ʼ�����
	 * @param middle �м�����
	 * @param end ���������
	 */
	void Merge(T data[],int start,int middle,int end)
	{
		int length1=middle-start+1;
		int length2=end-middle;
		int* temp1=new int[length1+1];
		int* temp2=new int[length2+1];
		//�����ݿ�������ʱ������
		for(int i=0;i<length1;++i)
		{
			temp1[i]=data[start+i];
		}
		for(int i=0;i<length2;++i)
		{
			temp2[i]=data[middle+i+1];
		}

		//�����ڱ�
		temp1[length1]=INT_MAX;
		temp2[length2]=INT_MAX;

		//�����ݷ��û�������
		int index1=0;
		int index2=0;
		for(int i=start;i<=end;++i)
		{
			if(temp1[index1]<=temp2[index2])
			{
				data[i]=temp1[index1];
				index1=index1+1;
			}
			else
			{
				data[i]=temp2[index2];
				index2=index2+1;
			}
		}
		delete[] temp1;
		delete[] temp2;
	}
	/**
	 * �鲢����
	 * @param data ��������
	 * @param start ��ʼ���
	 * @param end �������
	 */
	void Sort(T data[],int start,int end)
	{
		if(start<end)
		{
			int middle=floor((start+end)/2.0);
			Sort(data,start,middle);
			Sort(data,middle+1,end);
			Merge(data,start,middle,end);
		}
	}

};

