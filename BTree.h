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
	//最小度数，每个结点最少有t-1个关键字，最多有2t-1个关键字，根节点至少有一个关键字，
	int _minmumDegree;
};

