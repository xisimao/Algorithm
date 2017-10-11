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
 * ������
 * @param node ���
 * @param key ��
 * @return ������������Ӧ��㣬���򷵻�NULL
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
 * ����B��
 * @param minmumDegree ��С������ȷ��ÿ�����������Ľ�������С�������
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
 * �ָ���
 * @param parentNode Ҫ�ָ�ĸ����
 * @param index �ָ����ڸ�����е���ţ��������������ŵļ���Ϊ�����м��
 * @return 
 */
void BTree::SplitChild(BTreeNode* parentNode,int index)
{
	//Ҫ�ָ�Ľ�㣬λ����Ϊindex
	BTreeNode* splitNode=parentNode->Content[index];
	//�ָ���׼����ӵ��½�㣬λ��Ϊindex+1
	BTreeNode* newNode=new BTreeNode(_minmumDegree);
	newNode->Leaf=splitNode->Leaf;
	//�������߸�һ�룬ż�����½����һ��
	newNode->KeyCount=_minmumDegree-1;
	//���ָ���ĺ��μ����Ƶ��½��
 	for(int i=1;i<=_minmumDegree-1;++i)
	{
		newNode->Key[i]=splitNode->Key[i+_minmumDegree];
	}
	//�������Ҷ��Ҳ��Ҫ�ѷָ����е����ݸ��Ƶ��½��
	if(!splitNode->Leaf)
	{
		for(int i=1;i<=newNode->KeyCount;++i)
		{
			newNode->Content[i]=splitNode->Content[i+_minmumDegree];
		}
	}
	//ʣ�µ�����
	splitNode->KeyCount=_minmumDegree-1;
	//����[index]����Ϊԭ����ǰ�벿�֣�������С���м������
	//����[index+1]����Ϊԭ���ĺ�벿�֣���ʾ���д����м���Ĳ���
	//ԭ[index+1]���κ���
	for(int i=parentNode->KeyCount+1;i>=index+1;--i)
	{
		parentNode->Content[i+1]=parentNode->Content[i];
	}
	parentNode->Content[index+1]=newNode;

	//��[index]����Ϊԭ����м��
	//ԭ[index]���κ���
	for(int i=parentNode->KeyCount;i>=index;--i)
	{
		parentNode->Key[i+1]=parentNode->Key[i];
	}
	parentNode->Key[index]=splitNode->Key[splitNode->KeyCount+1];

	parentNode->KeyCount+=+1;
}
/**
 * ��һ�������Ľ������������
 * @param node ���
 * @param key ��
 */
void BTree::InsertNonFull(BTreeNode* node,int key)
{
	int index=node->KeyCount;
	//�����Ҷ�����Ѽ����뵽�ý����
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
	//������뵽�ӽ����
	else
	{
		while(index>=1&&key<node->Key[index])
		{
			index-=1;
		}
		index+=1;
		//����ӽ��������Ҫ����
		if(node->Content[index]->KeyCount==_minmumDegree*2-1)
		{
			SplitChild(node,index);
			if(key>node->Key[index])
			{
				index+=1;
			}
		}
		//��ӵ��ӽ����
		InsertNonFull(node->Content[index],key);
	}
}
/**
 * �����
 * @param key ��
 */
void BTree::Insert(int key)
{
	if(_root->KeyCount==_minmumDegree*2-1)
	{
		BTreeNode* newNode=new BTreeNode(_minmumDegree);
		newNode->Leaf=false;
		//����ֻ�Ƕ��½�������һ�����ݣ���û�з��ü����������︳ֵ0
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
 * ɾ����
 * @param node ���
 * @param key ��
 */
void BTree::Delete(BTreeNode* node,int key)
{
	if(node->KeyCount==0)
	{
		return;
	}
	//ȷ������е��ڻ��һ�����ڵ�ǰ�������
	int index=1;
	while(index<=node->KeyCount&&node->Key[index]<key)
	{
		index+=1;
	}
	//������ҵ���
	if(node->Key[index]==key)
	{
		//���Ҷ���ֱ��ɾ��,Ҷ���û��Content
		if(node->Leaf)
		{
			for(int i=index+1;i<=node->KeyCount;++i)
			{
				node->Key[i-1]=node->Key[i];
			}
			node->KeyCount-=1;
		}
		//�������Ҷ�������Ҫ���ӽ���еļ�����ɾ���ļ�
		else
		{
			//ǰ�����
			BTreeNode* preNode=node->Content[index];
			//�������
			BTreeNode* nextNode=node->Content[index+1];

			//�ж��������������ɾ��һ��������������ؼ�����С����
			//������������ӽ���еļ����ƶ���ɾ����
			//������ӽ�����ɾ��
			//����Ҳǡ������ÿһ���ݹ�ɾ���Ľ��Ӧ��֤������_minmumDegree����
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
			//�����������ڶ�����޷�������С����
			//���ɾ�������ƣ�ǰ�����+ɾ����+����������һ����㣬��ɾ���������
			else
			{
				//����ɾ����
				preNode->Key[preNode->KeyCount+1]=key;
				preNode->KeyCount+=1;
				//���ú������
				for(int i=1;i<=nextNode->KeyCount;++i)
				{
					preNode->Key[preNode->KeyCount+i]=nextNode->Key[i];
				}
				for(int i=1;i<=nextNode->KeyCount+1;++i)
				{
					preNode->Content[preNode->KeyCount+1+i]-nextNode->Content[i];
				}
				preNode->KeyCount+=nextNode->KeyCount;
				//��ɾ��������Ƴ�ɾ�������Ƴ��������
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
	//����ڽ����δ�ҵ���
	else
	{

		//c��ʾ����Ҫ���еݹ�Ľ�㣬���뱣֤���ļ�������_minmumDegree����
		//��Ϊ������еļ����ܻ��½������������ʱֻ���м�����Сֵ_minmumDegree-1����һ�������������ƻ�B��������
		//�������������������Ҫ���Ա����������Ѱ��������
		if(node->Content[index]->KeyCount<_minmumDegree)
		{
			//��ǰ���
			BTreeNode* c=node->Content[index];
			//ǰ�����
			BTreeNode* y=index-1>=1&&index-1<=node->KeyCount+1?node->Content[index-1]:NULL;
			//�������
			BTreeNode* z=index+1>=1&&index+1<=node->KeyCount+1?node->Content[index+1]:NULL;

			//�ж�ǰ���ͺ��������ȥ��һ�������Ƿ������������С����
			if(y!=NULL&&y->KeyCount>=_minmumDegree)
			{
				//�ڵ�һ��λ��ɾ����
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
				//ɾ��������ǰ�������һ����
				node->Key[index]=y->Key[y->KeyCount];
				y->KeyCount-=1;
			
			}
			else if(z!=NULL&&z->KeyCount>=_minmumDegree)
			{
				//�����һ��λ�÷���ɾ����
				c->Key[c->KeyCount+1]=node->Key[index];
				c->Content[c->KeyCount+2]=z->Content[1];
				c->KeyCount+=1;
				//ɾ�������ú����ĵ�һ����
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
			//����Ա߽�㶼�������㣬�򽫸����ļ����ƣ���ǰ���+�����ļ�+����������Ϊһ�����
			//�����С������ɾ���������
			else
			{
				//���ø����ļ�
				c->Key[c->KeyCount+1]=node->Key[index];
				c->KeyCount+=1;
				//���ú������
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
				//�������Ľ����С�ڼ�����С������˵��������Ǹ��ڵ�
				//����ֻ�е��������Ϊ1ʱ�ſ���ȥ�������
				if(node->KeyCount==1)
				{
					delete node;
					_root=c;
				}
				//���ڸ���������м����������Ҫɾ�����Ƶļ�
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