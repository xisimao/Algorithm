#include "StdAfx.h"
#include "OptimalBinarySearchTree.h"
#include <iostream>
#include <iomanip>
using namespace std;


OptimalBinarySearchTree::OptimalBinarySearchTree(void)
{
}


OptimalBinarySearchTree::~OptimalBinarySearchTree(void)
{
}
//p表示父结点的搜索频率
//q表示子结点的搜索频率
//n表示父结点总数
void OptimalBinarySearchTree::OpatimalBST(float p[],float q[],int n)
{
	//expect[i][j]表示父结点[i]到父结点[j]组合的最小期望，其中1<=i<=n，1<=j<=n，共需要n行n列
	//当j=i时，表示只用一个父结点做根节点，这时这个父结点只包括子结点
	//当j=i-1时表示子结点[i-1]的值，当i=1时，j=0，所以需要额外的[0]列，当j=n时，i=n+1，所以需要额外的[n+1]行
	//虽然总共需要n+1行n+1列，但是对于i是从1到n+1，而j是从0到n
	float** expect=new float*[n+2];
	//sum[i][j]表示从第i个父结点到第j个父结点的概率之和
	float** sum=new float*[n+2];

	//root[i][j]表示最佳根结点，由于只表示父结点，所以只需要n行和n列
	//由于这里未对i和j进行偏移，所以需要额外的一行和一列，而[0]列和[0]行不使用
	int** root=new int*[n+1];

	//[0]行不使用
	for(int i=1;i<=n+1;++i)
	{
		expect[i]=new float[n+1];
		sum[i]=new float[n+1];
		//初始化子结点的期望和概率和
		expect[i][i-1]=q[i-1];
		sum[i][i-1]=q[i-1];
	}

	for(int i=1;i<=n;++i)
	{
		root[i]=new int[n+1];
	}
	//选取父结点的数量
	for(int count=1;count<=n;++count)
	{
		//起始父结点序号
		for(int startIndex=1;startIndex<=n-count+1;++startIndex)
		{
			//结束父结点序号
			int endIndex=startIndex+count-1;
			expect[startIndex][endIndex]=10;
			//添加一个父结点则概率和增加了父结点和父结点右侧的子结点
			sum[startIndex][endIndex]=sum[startIndex][endIndex-1]+p[endIndex]+q[endIndex];
			//分割结点段，找到最小期望
			for(int r=startIndex;r<=endIndex;++r)
			{
				//当分割后，两侧部分会增加一个深度，所以有expect[i][j]=expect[i][r-1]+expect[r+1][j]+sum[i][r-1]+sum[r+1][j]+p[r]
				//其中sum[i][j]=sum[i][r-1]+p[r]+sum[r+1][j]
				//所以有expect[i][j]=expect[i][r-1]+expect[r+1][j]+sum[i][j]
				float temp=expect[startIndex][r-1]+expect[r+1][endIndex]+sum[startIndex][endIndex];
				if(temp<expect[startIndex][endIndex])
				{
					expect[startIndex][endIndex]=temp;
					root[startIndex][endIndex]=r;
				}
			}
		}
	}
	//输出
	for(int i=1;i<=n+1;++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j>=i-1)
			{
				cout<<left<<setw(6)<<expect[i][j]<<" ";
			}
		}
		cout<<endl;
	}
	cout<<endl;

	for(int i=1;i<=n+1;++i)
	{
		for(int j=0;j<=n;++j)
		{
			if(j>=i-1)
			{
				cout<<left<<setw(6)<<sum[i][j]<<" ";
			}
			
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			if(j>=i)
			{
				cout<<left<<setw(6)<<root[i][j]<<" ";
			}
		}
		cout<<endl;
	}
	for(int i=1;i<=n+1;++i)
	{
		delete[] expect[i];
		delete[] sum[i];
		
	}
	for(int i=1;i<=n;++i)
	{
		delete[] root[i];
	}
	delete[] expect;
	delete[] sum;
	delete[] root;
}