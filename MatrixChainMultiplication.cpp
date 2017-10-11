#include "StdAfx.h"
#include "MatrixChainMultiplication.h"
#include "Print.h"

MatrixChainMultiplication::MatrixChainMultiplication(void)
{
}


MatrixChainMultiplication::~MatrixChainMultiplication(void)
{
}
//data���ڴ洢������к��У���n���������Ϊp[n-1]����Ϊp[n]
//data[0]��ʾ��һ��������У��������鳤�Ȼ�Ⱦ�������1
void MatrixChainMultiplication::Order(int data[],int dataLength)
{
	//��ǰ���������
	int count=dataLength-1;
	//�ӵ�c�����󵽵�r������ĳ˷�������Сֵ
	//�����б�ʾ�ӵ�c������ʼ
	//�����б�ʾ����r���������
	int **minValues=new int*[count];
	//s��ʾ�����������ѷָ�㼴�ֳɴ�c��s��s��r
	int **locations=new int*[count];

	//�Խ����²�û��ʹ�ã���Ϊ���ڶԽ����²������磺r=3��c=1��ʾ�ӵ�3�����󵽵�1���������߼�����
	for(int i=0;i<count;++i)
	{
		minValues[i]=new int[count];
		locations[i]=new int[count];
		for(int j=i;j<count;++j)
		{
			minValues[i][j]=0;
			locations[i][j]=0;
		}
	}
	//��ʾ�����������������ټ��������������
	for(int chainLength=2;chainLength<=count;++chainLength)
	{
		//��ʾ��ǰ����������ʼ���
		for(int startIndex=0;startIndex<=count-chainLength;++startIndex)
		{
			//��ʾ��ǰ������ֹ���
			int endIndex=startIndex+chainLength-1;
			//��ʾ��ǰ������Сֵ
			minValues[startIndex][endIndex]=INT_MAX;
			//��ʾ��ǰ�ֶε����
			for(int location=startIndex;location<=endIndex-1;++location)
			{
				int value=minValues[startIndex][location]+minValues[location+1][endIndex]+data[startIndex]*data[location+1]*data[endIndex+1];
				if(value<minValues[startIndex][endIndex])
				{
					minValues[startIndex][endIndex]=value;
					locations[startIndex][endIndex]=location;
				}
			}
		}
	}
	cout<<minValues[0][count-1]<<endl;
	cout<<locations[0][count-1]<<endl;
	for(int i=0;i<count;++i)
	{
		delete[] minValues[i];
		delete[] locations[i];
	}
	delete[] minValues;
	delete[] locations;
}

void MatrixChainMultiplication::MemoizedMatrixChain(int data[],int dataLength)
{
	int count=dataLength-1;
	int **minValues=new int*[count];
	for(int i=0;i<count;++i)
	{
		minValues[i]=new int[count];
		for(int j=i;j<count;++j)
		{
			minValues[i][j]=INT_MAX;
		}
	}
	int value= LookUpChain(minValues,data,0,count-1);
	cout<<value<<endl;
		for(int i=0;i<count;++i)
	{
		delete[] minValues[i];
	}
	delete[] minValues;
}
int MatrixChainMultiplication::LookUpChain(int** minValues,int data[],int start,int end)
{
	if(minValues[start][end]<INT_MAX)
	{
		return minValues[start][end];
	}
	if(start==end)
	{
		minValues[start][end]=0;
	}
	else
	{
		for(int i=start;i<=end-1;++i)
		{
			int value=LookUpChain(minValues	,data,start,i)+
					  LookUpChain(minValues	,data,i+1,end)+
					  data[start]*data[i+1]*data[end+1];
			if(value<minValues[start][end])
			{
				minValues[start][end]=value;
			}
		}
	}
	return minValues[start][end];
}