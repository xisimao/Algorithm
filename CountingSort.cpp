#include "StdAfx.h"
#include "CountingSort.h"


CountingSort::CountingSort(void)
{
}


CountingSort::~CountingSort(void)
{
}

//max表示排序中的最大数，因为只有确定了最大数，才能保证用来保存索引的数组足够长
void CountingSort::Sort(int data[],int result[],int length,int max)
{
	//初始化计数数组
	int *countArray=new int[max+1];
	for(int i=0;i<=max;++i)
	{
		countArray[i]=0;
	}

	//用计数数组保存数据中每个整数的数量
	//因为用数据中的整数做索引，所以需要传入数据中的最大整数
	for(int i=0;i<length;++i)
	{
		countArray[data[i]]+=1;
	}

	//累加每一个计数，这样结果就是相应整数应该存放的最大索引
	for(int i=1;i<=max;++i)
	{
		countArray[i]+=countArray[i-1];
	}

	//将数据根据技术数组中的所以放入到结果数组中
	for(int i=length-1;i>=0;--i)
	{
		result[countArray[data[i]]-1]=data[i];
		//放入后需要调整当前整数的放入索引
		--countArray[data[i]];
	}

	delete[] countArray;
}

