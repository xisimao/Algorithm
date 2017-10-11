#include "StdAfx.h"
#include "HuffmanCode.h"
#include <iostream>
using namespace std;

HuffmanCode::HuffmanCode(void)
{
}


HuffmanCode::~HuffmanCode(void)
{
}

TreeNode<int> HuffmanCode::Build(TreeNode<int> list[],int n)
{
	//������С���ȶ���
	MinPriorityQueue<TreeNode<int>> hpq;
	for (int i=0;i<n;++i)
	{
		hpq.Insert(list[i]);
	}

	for(int i=0;i<n-1;++i)
	{
		//ÿ��ȡ��������㣬Ϊ�˳־û�����Ӷ��ú����������ݣ�����Ϊ�䴴���ռ䲢����
		TreeNode<int>* left=new TreeNode<int>(hpq.ExtractMin());
		TreeNode<int>* right=new TreeNode<int>(hpq.ExtractMin());
		//z�ڴ˽׶β�����Ҫ�־û���¼������ǽ��������´�ѭ���е�����Ϊ�䴴���ؼ�������Ǹ���Ḵ�Ƶ�������
		//�ں�������Ҫ�Ը���������������ɾ������
		TreeNode<int> z;
		z.Left=left;
		z.Right=right;
		z.Key=left->Key+right->Key;
		hpq.Insert(z);
	}
	//ÿ��ѭ��������������һ����������n-1��ѭ���󣬶���ֻʣ�����,���غ����Ϊ��
	return hpq.ExtractMin();
}


