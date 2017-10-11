#pragma once
#include "BTreeNode.h"
class BTree
{
public:
	BTree(void);
	~BTree(void);
	BTreeNode* Search(BTreeNode*,int);
	void Create(int);
	void SplitChild(BTreeNode*,int);
	void InsertNonFull(BTreeNode*,int);
	void Insert(int k);
	void Delete(BTreeNode*,int);
	void DeleteNode(BTreeNode*);
	BTreeNode* _root;
private:
	//��С������ÿ�����������t-1���ؼ��֣������2t-1���ؼ��֣����ڵ�������һ���ؼ��֣�
	int _minmumDegree;
};

