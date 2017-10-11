#include "StdAfx.h"
#include "BTree.h"


BTree::BTree(void)
	:_minmumDegree(3),_root(NULL)
{
}


BTree::~BTree(void)
{
	DeleteNode(_root);
}

void BTree::DeleteNode(BTreeNode* node)
{
	if(node==NULL)
	{
		return;
	}
	if(node->Leaf)
	{
		delete node;
	}
	else
	{
		for(int i=1;i<=node->KeyCount+1;++i)
		{
			DeleteNode(node->Content[i]);
		}
		delete node;
	}
}
/**
 * 搜索键
 * @param node 结点
 * @param key 键
 * @return 搜索到返回相应结点，否则返回NULL
 */
BTreeNode* BTree::Search(BTreeNode* node,int key)
{
	int i=0;

	while(i<node->KeyCount&&key>node->Key[i])
	{
		i+=1;
	}
	if(i<=node->KeyCount&&key==node->Key[i])
	{
		return node->Content[i];
	}
	else if(node->Leaf)
	{
		return NULL;
	}
	else
	{
		return Search(node->Content[i],key);
	}
}
/**
 * 创建B树
 * @param minmumDegree 最小度数，确定每个除根结点外的结点键的最小和最大数
 */
void BTree::Create(int minmumDegree)
{
	_minmumDegree=minmumDegree;
	BTreeNode* node=new BTreeNode(3);
	node->Leaf=true;
	node->KeyCount=0;
	_root=node;
}
/**
 * 分割结点
 * @param parentNode 要分割的父结点
 * @param index 分割结点在父结点中的序号，方法结束后该序号的键变为结点的中间键
 * @return 
 */
void BTree::SplitChild(BTreeNode* parentNode,int index)
{
	//要分割的结点，位置仍为index
	BTreeNode* splitNode=parentNode->Content[index];
	//分割点后准备添加的新结点，位置为index+1
	BTreeNode* newNode=new BTreeNode(_minmumDegree);
	newNode->Leaf=splitNode->Leaf;
	//奇数两边各一半，偶数的新结点少一个
	newNode->KeyCount=_minmumDegree-1;
	//将分割结点的后半段键复制到新结点
 	for(int i=1;i<=_minmumDegree-1;++i)
	{
		newNode->Key[i]=splitNode->Key[i+_minmumDegree];
	}
	//如果不是叶子也需要把分割结点中的内容复制到新结点
	if(!splitNode->Leaf)
	{
		for(int i=1;i<=newNode->KeyCount;++i)
		{
			newNode->Content[i]=splitNode->Content[i+_minmumDegree];
		}
	}
	//剩下的数量
	splitNode->KeyCount=_minmumDegree-1;
	//内容[index]更新为原结点的前半部分，即所有小于中间键部分
	//内容[index+1]更新为原结点的后半部分，表示所有大于中间键的部分
	//原[index+1]依次后移
	for(int i=parentNode->KeyCount+1;i>=index+1;--i)
	{
		parentNode->Content[i+1]=parentNode->Content[i];
	}
	parentNode->Content[index+1]=newNode;

	//键[index]更新为原结点中间键
	//原[index]依次后移
	for(int i=parentNode->KeyCount;i>=index;--i)
	{
		parentNode->Key[i+1]=parentNode->Key[i];
	}
	parentNode->Key[index]=splitNode->Key[splitNode->KeyCount+1];

	parentNode->KeyCount+=+1;
}
/**
 * 在一个不满的结点中增加内容
 * @param node 结点
 * @param key 键
 */
void BTree::InsertNonFull(BTreeNode* node,int key)
{
	int index=node->KeyCount;
	//如果是叶结点则把键插入到该结点中
	if(node->Leaf)
	{
		while(index>=1&&key<node->Key[index])
		{
			node->Key[index+1]=node->Key[index];
			index-=1;
		}
		node->Key[index+1]=key;
		node->KeyCount+=1;
	}
	//否则插入到子结点中
	else
	{
		while(index>=1&&key<node->Key[index])
		{
			index-=1;
		}
		index+=1;
		//如果子结点满了需要分裂
		if(node->Content[index]->KeyCount==_minmumDegree*2-1)
		{
			SplitChild(node,index);
			if(key>node->Key[index])
			{
				index+=1;
			}
		}
		//添加到子结点中
		InsertNonFull(node->Content[index],key);
	}
}
/**
 * 插入键
 * @param key 键
 */
void BTree::Insert(int key)
{
	if(_root->KeyCount==_minmumDegree*2-1)
	{
		BTreeNode* newNode=new BTreeNode(_minmumDegree);
		newNode->Leaf=false;
		//这里只是对新结点放置了一个内容，并没有放置键，所以这里赋值0
		newNode->KeyCount=0;
		newNode->Content[1]=_root;
		_root=newNode;
		SplitChild(newNode,1);
		InsertNonFull(newNode,key);
	}
	else
		InsertNonFull(_root,key);
	
}
/**
 * 删除键
 * @param node 结点
 * @param key 键
 */
void BTree::Delete(BTreeNode* node,int key)
{
	if(node->KeyCount==0)
	{
		return;
	}
	//确定结点中等于或第一个大于当前键的序号
	int index=1;
	while(index<=node->KeyCount&&node->Key[index]<key)
	{
		index+=1;
	}
	//结点中找到键
	if(node->Key[index]==key)
	{
		//如果叶结点直接删除,叶结点没有Content
		if(node->Leaf)
		{
			for(int i=index+1;i<=node->KeyCount;++i)
			{
				node->Key[i-1]=node->Key[i];
			}
			node->KeyCount-=1;
		}
		//如果不是叶结点则需要用子结点中的键顶替删除的键
		else
		{
			//前驱结点
			BTreeNode* preNode=node->Content[index];
			//后续结点
			BTreeNode* nextNode=node->Content[index+1];

			//判断上述两个结点在删除一个键后仍能满足关键字最小数量
			//如果可以则用子结点中的键上移顶替删除键
			//在针对子结点进行删除
			//这里也恰巧满足每一个递归删除的结点应保证至少有_minmumDegree个键
			if(preNode->KeyCount>=_minmumDegree)
			{
				node->Key[index]=preNode->Key[preNode->KeyCount];
				Delete(preNode,preNode->Key[preNode->KeyCount]);
			}
			else if(nextNode->KeyCount>=_minmumDegree)
			{
				node->Key[index]=nextNode->Key[1];
				Delete(nextNode,nextNode->Key[1]);
			}
			//如果两个结点在顶替后都无法满足最小数量
			//则把删除键下移，前驱结点+删除键+后续结点组成一个结点，并删除后续结点
			else
			{
				//放置删除键
				preNode->Key[preNode->KeyCount+1]=key;
				preNode->KeyCount+=1;
				//放置后续结点
				for(int i=1;i<=nextNode->KeyCount;++i)
				{
					preNode->Key[preNode->KeyCount+i]=nextNode->Key[i];
				}
				for(int i=1;i<=nextNode->KeyCount+1;++i)
				{
					preNode->Content[preNode->KeyCount+1+i]-nextNode->Content[i];
				}
				preNode->KeyCount+=nextNode->KeyCount;
				//在删除结点中移除删除键并移除后续结点
				for(int i=index+1;i<=node->KeyCount;++i)
				{
					node->Key[i-1]=node->Key[i];
					node->Content[i]=node->Content[i+1];
				}
				node->KeyCount-=1;
				delete nextNode;
				Delete(preNode,key);
			}
		}
	}
	//如果在结点中未找到键
	else
	{

		//c表示即将要进行递归的结点，必须保证结点的键至少有_minmumDegree个，
		//因为父结点中的键可能会下降，所以如果此时只是有键的最小值_minmumDegree-1个，一旦发生下移则破坏B树的性质
		//如果不满足上述条件需要在旁边两个结点中寻找扩充者
		if(node->Content[index]->KeyCount<_minmumDegree)
		{
			//当前结点
			BTreeNode* c=node->Content[index];
			//前驱结点
			BTreeNode* y=index-1>=1&&index-1<=node->KeyCount+1?node->Content[index-1]:NULL;
			//后续结点
			BTreeNode* z=index+1>=1&&index+1<=node->KeyCount+1?node->Content[index+1]:NULL;

			//判断前驱和后续结点在去掉一个结点后是否还能满足键的最小数量
			if(y!=NULL&&y->KeyCount>=_minmumDegree)
			{
				//在第一个位置删除键
				for(int i=c->KeyCount;i>=1;--i)
				{
					c->Key[i+1]=c->Key[i];
				}
				for(int i=c->KeyCount+1;i>=1;--i)
				{
					c->Content[i+1]=c->Content[i];
				}
				c->Key[1]=node->Key[index];
				c->Content[1]=y->Content[y->KeyCount+1];
				c->KeyCount+=1;
				//删除键放置前驱的最后一个键
				node->Key[index]=y->Key[y->KeyCount];
				y->KeyCount-=1;
			
			}
			else if(z!=NULL&&z->KeyCount>=_minmumDegree)
			{
				//在最后一个位置放置删除键
				c->Key[c->KeyCount+1]=node->Key[index];
				c->Content[c->KeyCount+2]=z->Content[1];
				c->KeyCount+=1;
				//删除键放置后续的第一个键
				node->Key[index]=z->Key[1];
				for(int i=1;i<z->KeyCount;++i)
				{
					z->Key[i]=z->Key[i+1];
				}
				for(int i=1;i<=z->KeyCount;++i)
				{
					z->Content[i]=z->Content[i+1];
				}
				z->KeyCount-=1;
			}
			//如果旁边结点都不能满足，则将父结点的键下移，当前结点+父结点的键+后续结点组成为一个结点
			//随后缩小父结点和删除后续结点
			else
			{
				//放置父结点的键
				c->Key[c->KeyCount+1]=node->Key[index];
				c->KeyCount+=1;
				//放置后续结点
				for(int i=1;i<=z->KeyCount;++i)
				{
					c->Key[i+c->KeyCount]=z->Key[i];
				}
				for(int i=1;i<=z->KeyCount+1;++i)
				{
					c->Content[i+c->KeyCount]=z->Content[i];
				}
				c->KeyCount+=z->KeyCount;
				delete z;
				//当父结点的结点数小于键的最小数量，说明父结点是根节点
				//但是只有当父结点数为1时才可以去掉父结点
				if(node->KeyCount==1)
				{
					delete node;
					_root=c;
				}
				//对于父结点中扔有键的情况则需要删除下移的键
				else
				{
					for(int i=index+1;i<=node->KeyCount;++i)
					{
						node->Key[i-1]=node->Key[i];
					}
					for(int i=index+1;i<=node->KeyCount+1;++i)
					{
						node->Content[i-1]=node->Content[i];
					}
					node->KeyCount-=1;
				}
			}
			Delete(c,key);
		}
		else
		{
			Delete(node->Content[index],key);
		}

	}
}