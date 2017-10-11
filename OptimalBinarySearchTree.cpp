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
//p��ʾ����������Ƶ��
//q��ʾ�ӽ�������Ƶ��
//n��ʾ���������
void OptimalBinarySearchTree::OpatimalBST(float p[],float q[],int n)
{
	//expect[i][j]��ʾ�����[i]�������[j]��ϵ���С����������1<=i<=n��1<=j<=n������Ҫn��n��
	//��j=iʱ����ʾֻ��һ������������ڵ㣬��ʱ��������ֻ�����ӽ��
	//��j=i-1ʱ��ʾ�ӽ��[i-1]��ֵ����i=1ʱ��j=0��������Ҫ�����[0]�У���j=nʱ��i=n+1��������Ҫ�����[n+1]��
	//��Ȼ�ܹ���Ҫn+1��n+1�У����Ƕ���i�Ǵ�1��n+1����j�Ǵ�0��n
	float** expect=new float*[n+2];
	//sum[i][j]��ʾ�ӵ�i������㵽��j�������ĸ���֮��
	float** sum=new float*[n+2];

	//root[i][j]��ʾ��Ѹ���㣬����ֻ��ʾ����㣬����ֻ��Ҫn�к�n��
	//��������δ��i��j����ƫ�ƣ�������Ҫ�����һ�к�һ�У���[0]�к�[0]�в�ʹ��
	int** root=new int*[n+1];

	//[0]�в�ʹ��
	for(int i=1;i<=n+1;++i)
	{
		expect[i]=new float[n+1];
		sum[i]=new float[n+1];
		//��ʼ���ӽ��������͸��ʺ�
		expect[i][i-1]=q[i-1];
		sum[i][i-1]=q[i-1];
	}

	for(int i=1;i<=n;++i)
	{
		root[i]=new int[n+1];
	}
	//ѡȡ����������
	for(int count=1;count<=n;++count)
	{
		//��ʼ��������
		for(int startIndex=1;startIndex<=n-count+1;++startIndex)
		{
			//������������
			int endIndex=startIndex+count-1;
			expect[startIndex][endIndex]=10;
			//���һ�����������ʺ������˸����͸�����Ҳ���ӽ��
			sum[startIndex][endIndex]=sum[startIndex][endIndex-1]+p[endIndex]+q[endIndex];
			//�ָ���Σ��ҵ���С����
			for(int r=startIndex;r<=endIndex;++r)
			{
				//���ָ�����ಿ�ֻ�����һ����ȣ�������expect[i][j]=expect[i][r-1]+expect[r+1][j]+sum[i][r-1]+sum[r+1][j]+p[r]
				//����sum[i][j]=sum[i][r-1]+p[r]+sum[r+1][j]
				//������expect[i][j]=expect[i][r-1]+expect[r+1][j]+sum[i][j]
				float temp=expect[startIndex][r-1]+expect[r+1][endIndex]+sum[startIndex][endIndex];
				if(temp<expect[startIndex][endIndex])
				{
					expect[startIndex][endIndex]=temp;
					root[startIndex][endIndex]=r;
				}
			}
		}
	}
	//���
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