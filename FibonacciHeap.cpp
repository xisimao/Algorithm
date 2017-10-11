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
 * 创建堆
 * @param 最小结点
 */
void FibonacciHeap::BuildList(HeapNode<int>* min)
{
	min->Left=min;
	min->Right=min;
}
/**
 * 在指定借点钱插入结点
 * @param bro 指定结点
 * @param node 新结点
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
 * 添加孩子结点
 * @param parent 父结点
 * @param child 子结点
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
 * 删除结点，这里保留结点的子结点关联，因为在移除结点时，有时需要删除，有时需要移动到其他结点
 * 对于后一种情况需要保留子结点
 * @param 要删除的结点
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
 * 根据链表中的结点获得整个链表
 * @param node 结点
 * @param count 链表的长度
 * @return 结点数组
 */
HeapNode<int>** FibonacciHeap::GetList(HeapNode<int>* node,int& count)
{
	if(node==NULL)
	{
		count=0;
		return NULL;
	}
	//得到数量
	count=1;
	HeapNode<int>* temp=node->Right;
	while(node!=temp)
	{
		count+=1;
		temp=temp->Right;
	}
	//得到链表
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
 * 连接两个堆
 * @param heap1 堆1
 * @param heap2 堆2 
 */
void FibonacciHeap::Union(FibonacciHeap heap1,FibonacciHeap heap2)
{
	//连接两个链表
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
	//找到最小值
	if(heap1._min==NULL||(heap2._min!=NULL&&heap2._min->Key<heap1._min->Key))
	{
		_min=heap2._min;
	}

	_count=heap1._count+heap2._count;
}
/**
 * 获得最小值
 * @return 最小值结点，如果堆为空则返回NULL
 */
HeapNode<int>* FibonacciHeap::Minimum()
{
	return _min;
}
/**
 * 弹出最小值结点
 * @return 最小值结点，如果堆为空则返回NULL
 */
HeapNode<int>* FibonacciHeap::ExtractMin()
{
	HeapNode<int>* minNode=_min;
	if(minNode!=NULL)
	{
		//将结点的子结点添加到根链表中
		int count=0;
		HeapNode<int>** list=GetList(minNode->Child,count);
		for(int i=0;i<count;++i)
		{
			AddBefore(_min,list[i]);
		}
		delete[] list;
		minNode->Child=NULL;
		//因为remove会删除z的兄弟关联，所以这里先取到右边的结点
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
 * 合并结点
 */
void FibonacciHeap::Consolidate()
{
    if(_min==NULL)
	{
		return;
	}
	//这里需要增加1，因为当从1开始到deep所有度数均满员的情况下，一旦发生删除，则可能会向最大deep的结点中增加子结点
	//此时deep为deep+1，如果这里不+1，则在临时数组中无法找到任何根结点
	int maxDegree=log((double)_count)/log(2.0)+1;
	//用来记录根链表中具有指定度数（0-最大度数）的结点
	HeapNode<int>** rootNodes=new HeapNode<int>*[maxDegree+1];
	for(int i=0;i<=maxDegree;++i)
	{
		rootNodes[i]=NULL;
	}

	HeapNode<int>* node=_min;
	int count=0;
	//保存即将循环搜索的根结点
	HeapNode<int>** tempRootNodes=GetList(node,count);
	for(int i=0;i<count;++i)
	{
		node=tempRootNodes[i];
		int degree=node->Degree;
		while(degree<=maxDegree&&rootNodes[degree]!=NULL)
		{
			//将当前循环的结点添加到具有指定度数的结点下
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
	//确定最小值结点
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
 * 缩小键
 * @param x 要缩小的结点
 * @param k 缩小到的值
 */
void FibonacciHeap::DecreaseKey(HeapNode<int>* node,int key)
{
	if(key>node->Key)
	{
		return;
	}
	node->Key=key;
	HeapNode<int>* parent=node->Parent;
	//如果违反最小堆性质
	if(parent!=NULL&&node->Key<parent->Key)
	{
		Cut(node);
		CascadingCut(parent);
	}
	//在cut x后，x在根链表中所以需要确定最小值
	if(node->Key<_min->Key)
	{
		_min=node;
	}
}
/**
 * 将结点剪切到根链表中
 * @param x 剪切的结点
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
 * 联级切断
 * @param y 结点
 */
void FibonacciHeap::CascadingCut(HeapNode<int>* node)
{
	HeapNode<int>* parent=node->Parent;
	if(parent!=NULL)
	{
		//如果已经删除了一个孩子，则需要把结点添加到根节点中
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
 * 删除结点
 * @param x 要删除的结点
 */
void FibonacciHeap::Delete(HeapNode<int>* node)
{
	DecreaseKey(node,INT_MIN);
	ExtractMin();
}
/**
 * 搜索结点
 * @param key 值
 * @return 结点，如果未找到返回NULL
 */
HeapNode<int>* FibonacciHeap::Search(int key)
{
	return Search(_min,key);
}
/**
 * 递归搜索结点
 * @param node 结点
 * @param key 值
 * @return 结点，如果未找到返回NULL
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