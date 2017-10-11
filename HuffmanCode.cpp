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
	//构建最小优先队列
	MinPriorityQueue<TreeNode<int>> hpq;
	for (int i=0;i<n;++i)
	{
		hpq.Insert(list[i]);
	}

	for(int i=0;i<n-1;++i)
	{
		//每次取出两个结点，为了持久化储蓄从而让函数外获得数据，必须为其创建空间并复制
		TreeNode<int>* left=new TreeNode<int>(hpq.ExtractMin());
		TreeNode<int>* right=new TreeNode<int>(hpq.ExtractMin());
		//z在此阶段并不需要持久化记录，如果是结点则会在下次循环中弹出并为其创建控件，如果是根则会复制到函数外
		//在函数外需要对根的左右子树进行删除工作
		TreeNode<int> z;
		z.Left=left;
		z.Right=right;
		z.Key=left->Key+right->Key;
		hpq.Insert(z);
	}
	//每次循环弹出两个插入一个，所以在n-1次循环后，堆中只剩根结点,返回后堆中为空
	return hpq.ExtractMin();
}


