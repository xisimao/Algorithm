#pragma once
#include <limits>
#include <math.h>

/**
 * 归并排序
 */
template <typename T>
class MergeSort
{
public:
	/**
	 * 合并
	 * @param data 数据数组
	 * @param start 开始的序号
	 * @param middle 中间的序号
	 * @param end 结束的序号
	 */
	void Merge(T data[],int start,int middle,int end)
	{
		int length1=middle-start+1;
		int length2=end-middle;
		int* temp1=new int[length1+1];
		int* temp2=new int[length2+1];
		//将数据拷贝到临时数组中
		for(int i=0;i<length1;++i)
		{
			temp1[i]=data[start+i];
		}
		for(int i=0;i<length2;++i)
		{
			temp2[i]=data[middle+i+1];
		}

		//放置哨兵
		temp1[length1]=INT_MAX;
		temp2[length2]=INT_MAX;

		//将数据放置回数组中
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
	 * 归并排序
	 * @param data 数据数组
	 * @param start 开始序号
	 * @param end 结束序号
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

