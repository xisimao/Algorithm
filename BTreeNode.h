#pragma once
class BTreeNode
{
public:
	BTreeNode(int minmumDegree)
	{
		Key=new int[minmumDegree*2];
		for(int i=1;i<minmumDegree*2;++i)
		{
			Key[i]=0;
		}
		Content=new BTreeNode*[minmumDegree*2+1];
		for(int i=1;i<minmumDegree*2+1;++i)
		{
			Content[i]=NULL;
		}
	}
	~BTreeNode(void)
	{
		delete[] Key;
		delete[] Content;
	}
	//键
	int* Key;
	//键的数量
	int KeyCount;
	//是否为叶结点
	bool Leaf;
	//内容，其中c[i]的所有键<key[i]<c[i+1]的所有键
	BTreeNode** Content;
};

