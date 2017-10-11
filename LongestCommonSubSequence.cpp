#include "StdAfx.h"
#include "LongestCommonSubSequence.h"
#include <iostream>
using namespace std;


LongestCommonSubSequence::LongestCommonSubSequence(void)
{
}


LongestCommonSubSequence::~LongestCommonSubSequence(void)
{
}

void LongestCommonSubSequence::LCSLength(char x[],int m,char y[],int n)
{
	//例如：X={A,B,C,B,D,A,B}
	//      Y={B,D,C,A,B,A}
	//      X[i]表示长度为i的前缀，i=0~m
	//      Y[i]表示长度为i的前缀，i=0~n

	//c[i+1][j+1] X[i]和Y[j]的最长公共子序列
	int **c=new int*[m+1];
	for(int i=0;i<=m;++i)
	{
		c[i]=new int[n+1];
		//初始化 X[i]和Y[0]的最长公共子序列
		c[i][0]=0;
	
	}
	for(int j=0;j<=n;++j)
	{
		//初始化 X[0]和Y[j]的最长公共子序列
		c[0][j]=0;
	}
	//i表示第一个序列前缀的长度
	for(int i=0;i<m;++i)
	{
		//j表示第二个序列前缀的长度
		for(int j=0;j<n;++j)
		{
			//如果X[i]=Y[j]，取X[i-1]和Y[j-1]的最长公共子序列的长度增加1
			if(x[i]==y[j])
			{
 				c[i+1][j+1]=c[i][j]+1;
			}
			else
			{
				//否则，取X[i-1]和Y[j]  X[i]和Y[j-1]两者的最长公共子序列的长度最大值
				c[i+1][j+1]=max(c[i][j+1],c[i+1][j]);
			}
		}
	}

	//输出
	Print(c,x,m,n);
	cout<<endl;
	cout<<"  ";
	for(int i=0;i<=n;++i)
	{
		if(i==0)
		{
			cout<<"  ";
		}
		else
		{
			cout<<y[i-1]<<" ";
		}
		
	}
	cout<<endl;

	for(int i=0;i<=m;++i)
	{
		if(i==0)
		{
			cout<<"  ";
		}
		else
		{
			cout<<x[i-1]<<" ";
		}
	
		for(int j=0;j<=n;++j)
		{
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
		delete[] c[i];
	}
	delete[] c;
}
void LongestCommonSubSequence::Print(int** c,char x[],int i,int j)
{
	if(i==2&&j==4)
	{
		cout<<" ";
	}
	if(i==0||j==0)
	{
		return;
	}
	if(c[i-1][j]==c[i][j])
	{
		Print(c,x,i-1,j);
	}
	else 
	{
		Print(c,x,i-1,j-1);
		cout<<x[i-1]<<" ";
	}
}

