#include "StdAfx.h"
#include "FibonacciHeap.h"


FibonacciHeap::FibonacciHeap(void)
	:_min(NULL),_count(0)
{
}


FibonacciHeap::~FibonacciHeap(void)
{
}
/**
 * ������
 * @param ��С���
 */
void FibonacciHeap::BuildList(HeapNode<int>* min)
{
	min->Left=min;
	min->Right=min;
}
/**
 * ��ָ�����Ǯ������
 * @param bro ָ�����
 * @param node �½��
 */
void FibonacciHeap::AddBefore(HeapNode<int>* bro,HeapNode<int>* node)
{
	if(_min==NULL)
	{
		return;
	}
	HeapNode<int>* left=bro->Left;
	bro->Left=node;
	left->Right=node;

	node->Left=left;
	node->Right=_min;

	node->Parent=bro->Parent;

	if(node->Parent!=NULL)
	{
		node->Parent->Degree+=1;
	}
}
/**
 * ��Ӻ��ӽ��
 * @param parent �����
 * @param child �ӽ��
 */
void FibonacciHeap::AddChild(HeapNode<int>* parent,HeapNode<int>* child)
{
	if(parent==NULL||child==NULL)
	{
		return;
	}
	Remove(child);
	if(parent->Child==NULL)
	{
		parent->Child=child;
		child->Left=child;
		child->Right=child;
	}
	else
	{
		parent->Child->Left->Right=child;
		child->Left=parent->Child->Left;

		child->Right=parent->Child;
		parent->Child->Left=child;

	}
	child->Parent=parent;
	parent->Degree+=1;
	child->IsDeleteOneChild=false;
}


/**
 * ɾ����㣬���ﱣ�������ӽ���������Ϊ���Ƴ����ʱ����ʱ��Ҫɾ������ʱ��Ҫ�ƶ����������
 * ���ں�һ�������Ҫ�����ӽ��
 * @param Ҫɾ���Ľ��
 */
void FibonacciHeap::Remove(HeapNode<int>* node)
{
	if(node==NULL)
	{
		return;
	}
	node->Left->Right=node->Right;
	node->Right->Left=node->Left;
	if(node->Parent!=NULL)
	{
		if(node->Parent->Child==node)
		{
			node->Parent->Child=node==node->Left?NULL:node->Left;
		}
		node->Parent->Degree-=1;
		node->Parent=NULL;
	}
	node->Left=NULL;
	node->Right=NULL;

}



/**
 * ���������еĽ������������
 * @param node ���
 * @param count ����ĳ���
 * @return �������
 */
HeapNode<int>** FibonacciHeap::GetList(HeapNode<int>* node,int& count)
{
	if(node==NULL)
	{
		count=0;
		return NULL;
	}
	//�õ�����
	count=1;
	HeapNode<int>* temp=node->Right;
	while(node!=temp)
	{
		count+=1;
		temp=temp->Right;
	}
	//�õ�����
	HeapNode<int>** list=new HeapNode<int>*[count];
	int index=0;
	temp=node;
	do 
	{
		list[index++]=temp;
		temp=temp->Right;
	} while (temp!=node);
	return list;
}
void FibonacciHeap::Insert(HeapNode<int>* node)
{
	if(_min==NULL)
	{
		BuildList(node);
		_min=node;
	}
	else
	{
		AddBefore(_min,node);
		if(node->Key<_min->Key)
		{
			_min=node;
		}
	}
	_count+=1;
}

HeapNode<int>* FibonacciHeap::Insert(int key)
{
	HeapNode<int>* node=new HeapNode<int>();
	node->Key=key;
	Insert(node);
	return node;
}
/**
 * ����������
 * @param heap1 ��1
 * @param heap2 ��2 
 */
void FibonacciHeap::Union(FibonacciHeap heap1,FibonacciHeap heap2)
{
	//������������
	if(heap1._min!=NULL&&heap2._min!=NULL)
	{
		HeapNode<int>* tail1=heap1._min->Left;
		HeapNode<int>* tail2=heap2._min->Left;
		heap1._min->Left=tail2;
		tail2->Right=heap1._min;
		heap2._min->Left=tail1;
		tail1->Right=heap2._min;
	}

	_min=heap1._min;
	//�ҵ���Сֵ
	if(heap1._min==NULL||(heap2._min!=NULL&&heap2._min->Key<heap1._min->Key))
	{
		_min=heap2._min;
	}

	_count=heap1._count+heap2._count;
}
/**
 * �����Сֵ
 * @return ��Сֵ��㣬�����Ϊ���򷵻�NULL
 */
HeapNode<int>* FibonacciHeap::Minimum()
{
	return _min;
}
/**
 * ������Сֵ���
 * @return ��Сֵ��㣬�����Ϊ���򷵻�NULL
 */
HeapNode<int>* FibonacciHeap::ExtractMin()
{
	HeapNode<int>* minNode=_min;
	if(minNode!=NULL)
	{
		//�������ӽ����ӵ���������
		int count=0;
		HeapNode<int>** list=GetList(minNode->Child,count);
		for(int i=0;i<count;++i)
		{
			AddBefore(_min,list[i]);
		}
		delete[] list;
		minNode->Child=NULL;
		//��Ϊremove��ɾ��z���ֵܹ���������������ȡ���ұߵĽ��
		HeapNode<int>* temp=minNode->Right;
		Remove(minNode);
		if(minNode==temp)
		{
			_min=NULL;
		}
		else
		{
			_min=temp;
			Consolidate();
		}
		_count-=1;
	}
	return minNode;
}

/**
 * �ϲ����
 */
void FibonacciHeap::Consolidate()
{
    if(_min==NULL)
	{
		return;
	}
	//������Ҫ����1����Ϊ����1��ʼ��deep���ж�������Ա������£�һ������ɾ��������ܻ������deep�Ľ���������ӽ��
	//��ʱdeepΪdeep+1��������ﲻ+1��������ʱ�������޷��ҵ��κθ����
	int maxDegree=log((double)_count)/log(2.0)+1;
	//������¼�������о���ָ��������0-���������Ľ��
	HeapNode<int>** rootNodes=new HeapNode<int>*[maxDegree+1];
	for(int i=0;i<=maxDegree;++i)
	{
		rootNodes[i]=NULL;
	}

	HeapNode<int>* node=_min;
	int count=0;
	//���漴��ѭ�������ĸ����
	HeapNode<int>** tempRootNodes=GetList(node,count);
	for(int i=0;i<count;++i)
	{
		node=tempRootNodes[i];
		int degree=node->Degree;
		while(degree<=maxDegree&&rootNodes[degree]!=NULL)
		{
			//����ǰѭ���Ľ����ӵ�����ָ�������Ľ����
			HeapNode<int>* y=rootNodes[degree];
			if(node->Key>y->Key)
			{
				HeapNode<int>* temp=node;
				node=y;
				y=temp;
			}
			AddChild(node,y);
		
			rootNodes[degree]=NULL;
			degree=degree+1;
		}
		rootNodes[degree]=node;
	}
	delete[] tempRootNodes;
	//ȷ����Сֵ���
	_min=NULL;
	for(int i=0;i<=maxDegree;++i)
	{
		if(rootNodes[i]!=NULL)
		{
			if(_min==NULL)
			{
				_min=rootNodes[i];
			}
			else
			{
				if(rootNodes[i]->Key<_min->Key)
				{
					_min=rootNodes[i];
				}
			}
		}
	}
}
/**
 * ��С��
 * @param x Ҫ��С�Ľ��
 * @param k ��С����ֵ
 */
void FibonacciHeap::DecreaseKey(HeapNode<int>* node,int key)
{
	if(key>node->Key)
	{
		return;
	}
	node->Key=key;
	HeapNode<int>* parent=node->Parent;
	//���Υ����С������
	if(parent!=NULL&&node->Key<parent->Key)
	{
		Cut(node);
		CascadingCut(parent);
	}
	//��cut x��x�ڸ�������������Ҫȷ����Сֵ
	if(node->Key<_min->Key)
	{
		_min=node;
	}
}
/**
 * �������е���������
 * @param x ���еĽ��
 */
void FibonacciHeap::Cut(HeapNode<int>* node)
{
	if(node==NULL)
	{
		return;
	}
	Remove(node);
	AddBefore(_min,node);
	node->IsDeleteOneChild=false;
}
/**
 * �����ж�
 * @param y ���
 */
void FibonacciHeap::CascadingCut(HeapNode<int>* node)
{
	HeapNode<int>* parent=node->Parent;
	if(parent!=NULL)
	{
		//����Ѿ�ɾ����һ�����ӣ�����Ҫ�ѽ����ӵ����ڵ���
		if(node->IsDeleteOneChild)
		{
			Cut(node);
			CascadingCut(parent);
		}
		else
		{
			node->IsDeleteOneChild=true;
		}
	}
}
/**
 * ɾ�����
 * @param x Ҫɾ���Ľ��
 */
void FibonacciHeap::Delete(HeapNode<int>* node)
{
	DecreaseKey(node,INT_MIN);
	ExtractMin();
}
/**
 * �������
 * @param key ֵ
 * @return ��㣬���δ�ҵ�����NULL
 */
HeapNode<int>* FibonacciHeap::Search(int key)
{
	return Search(_min,key);
}
/**
 * �ݹ��������
 * @param node ���
 * @param key ֵ
 * @return ��㣬���δ�ҵ�����NULL
 */
HeapNode<int>* FibonacciHeap::Search(HeapNode<int>* node,int key)
{
	if(node==NULL)
	{
		return NULL;
	}
	HeapNode<int>* temp=node;
	do 
	{
		if(temp->Key==key)
		{
			return temp;
		}
		HeapNode<int>* temp2=Search(temp->Child,key);
		if(temp2!=NULL)
		{
			return temp2;
		}
		temp=temp->Right;
	} while (temp!=node);
	return NULL;
}