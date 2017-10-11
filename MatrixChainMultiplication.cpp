#include "StdAfx.h"
#include "MatrixChainMultiplication.h"
#include "Print.h"

MatrixChainMultiplication::MatrixChainMultiplication(void)
{
}


MatrixChainMultiplication::~MatrixChainMultiplication(void)
{
}
//data用于存储矩阵的行和列，第n个矩阵的行为p[n-1]，列为p[n]
//data[0]表示第一个矩阵的行，所以数组长度会比矩阵数多1
void MatrixChainMultiplication::Order(int data[],int dataLength)
{
	//当前矩阵的数量
	int count=dataLength-1;
	//从第c个矩阵到第r个矩阵的乘法次数最小值
	//矩阵列表示从第c个矩阵开始
	//矩阵行表示到第r个矩阵结束
	int **minValues=new int*[count];
	//s表示上述矩阵的最佳分割点即分成从c到s和s到r
	int **locations=new int*[count];

	//对角线下部没有使用，因为对于对角线下部，例如：r=3到c=1表示从第3个矩阵到第1个矩阵与逻辑不符
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
	//表示矩阵链的数量，最少计算两个矩阵相乘
	for(int chainLength=2;chainLength<=count;++chainLength)
	{
		//表示当前矩阵链的起始序号
		for(int startIndex=0;startIndex<=count-chainLength;++startIndex)
		{
			//表示当前链的终止序号
			int endIndex=startIndex+chainLength-1;
			//表示当前链的最小值
			minValues[startIndex][endIndex]=INT_MAX;
			//表示当前分段的序号
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