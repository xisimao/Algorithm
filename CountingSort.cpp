#include "StdAfx.h"
#include "CountingSort.h"


CountingSort::CountingSort(void)
{
}


CountingSort::~CountingSort(void)
{
}

//max��ʾ�����е����������Ϊֻ��ȷ��������������ܱ�֤�������������������㹻��
void CountingSort::Sort(int data[],int result[],int length,int max)
{
	//��ʼ����������
	int *countArray=new int[max+1];
	for(int i=0;i<=max;++i)
	{
		countArray[i]=0;
	}

	//�ü������鱣��������ÿ������������
	//��Ϊ�������е�������������������Ҫ���������е��������
	for(int i=0;i<length;++i)
	{
		countArray[data[i]]+=1;
	}

	//�ۼ�ÿһ���������������������Ӧ����Ӧ�ô�ŵ��������
	for(int i=1;i<=max;++i)
	{
		countArray[i]+=countArray[i-1];
	}

	//�����ݸ��ݼ��������е����Է��뵽���������
	for(int i=length-1;i>=0;--i)
	{
		result[countArray[data[i]]-1]=data[i];
		//�������Ҫ������ǰ�����ķ�������
		--countArray[data[i]];
	}

	delete[] countArray;
}

