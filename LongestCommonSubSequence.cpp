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
	//���磺X={A,B,C,B,D,A,B}
	//      Y={B,D,C,A,B,A}
	//      X[i]��ʾ����Ϊi��ǰ׺��i=0~m
	//      Y[i]��ʾ����Ϊi��ǰ׺��i=0~n

	//c[i+1][j+1] X[i]��Y[j]�������������
	int **c=new int*[m+1];
	for(int i=0;i<=m;++i)
	{
		c[i]=new int[n+1];
		//��ʼ�� X[i]��Y[0]�������������
		c[i][0]=0;
	
	}
	for(int j=0;j<=n;++j)
	{
		//��ʼ�� X[0]��Y[j]�������������
		c[0][j]=0;
	}
	//i��ʾ��һ������ǰ׺�ĳ���
	for(int i=0;i<m;++i)
	{
		//j��ʾ�ڶ�������ǰ׺�ĳ���
		for(int j=0;j<n;++j)
		{
			//���X[i]=Y[j]��ȡX[i-1]��Y[j-1]������������еĳ�������1
			if(x[i]==y[j])
			{
 				c[i+1][j+1]=c[i][j]+1;
			}
			else
			{
				//����ȡX[i-1]��Y[j]  X[i]��Y[j-1]���ߵ�����������еĳ������ֵ
				c[i+1][j+1]=max(c[i][j+1],c[i+1][j]);
			}
		}
	}

	//���
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

