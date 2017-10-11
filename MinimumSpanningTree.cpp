#include "StdAfx.h"
#include "MinimumSpanningTree.h"


MinimumSpanningTree::MinimumSpanningTree(void)
{
}


MinimumSpanningTree::~MinimumSpanningTree(void)
{
}


void MinimumSpanningTree::MakeSet(Vertex* x)
{
	x->Pre=x;
	x->Rank=0;
}

void MinimumSpanningTree::Link(Vertex* x,Vertex* y)
{
	if(x->Rank>y->Rank)
	{
		y->Pre=x;
	}
	else 
	{
		x->Pre=y;
		if(x->Rank==y->Rank)
		{
			y->Rank=y->Rank+1;
		}
	}
}

Vertex* MinimumSpanningTree::FindSet(Vertex* x)
{
	if(x!=x->Pre)
	{
		x->Pre=FindSet(x->Pre);
	}
	return x->Pre;
}

void MinimumSpanningTree::Union(Vertex* x,Vertex* y)
{
	Link(FindSet(x),FindSet(y));
}
//在所有连接森林中两颗不同树的边里面，找到权重最小的边
void MinimumSpanningTree::Kruskal(Graph& g,Edge* list[])
{
	//将所有结点视为一棵树
	for(int i=0;i<g._verCount;++i)
	{
		MakeSet(g._verteies[i]);
	}
	//找到权重最小的边连接两棵树
	InsertionSort<Edge*> is;
	//按边的权重升序排序
	is.SortP(g._edges,g._edgeCount);
	int index=0;
	for (int i=0;i<g._edgeCount;++i)
	{
		//保证这条边的两个结点并不是一棵树，否则会形成回路
		if(FindSet(g._edges[i]->Start)!=FindSet(g._edges[i]->End))
		{
			list[index++]=g._edges[i];
			//连接边的两个结点的根节点
			Union(g._edges[i]->Start,g._edges[i]->End);
		}
	}
}
//从树任意的根节点开始一直长大到覆盖所有结点为止
void MinimumSpanningTree::Prim(Graph& g,Vertex* v)
{
	//Key 表示所有不在当前树中的结点能够连接到树中结点的最小变权重
	//初始化各结点
	for(int i=0;i<g._verCount;++i)
	{
		g._verteies[i]->Key=INT_MAX;
		g._verteies[i]->Pre=NULL;
	}
	//设置开始结点
	v->Key=0;
	//堆中保存尚未连接到树中的结点
	FibonacciHeap heap;
	for(int i=0;i<g._verCount;++i)
	{
		HeapNode<int>* node=new HeapNode<int>;
		node->Key=g._verteies[i]->Key;
		node->Tag=g._verteies[i]->Index;
		g._verteies[i]->Tag=node;
		g._verteies[i]->IsInHeap=true;
		heap.Insert(node);
	}
	//每次取出可以连接到树中的最小权重的结点
	HeapNode<int>* temp=heap.ExtractMin();
	while(temp!=NULL)
	{
		//找到所有可以与u结点连接的结点v
		//如果v尚未连接到树中并且w(u,v)小于当前v的key，则更新
		Vertex* u=g._verteies[temp->Tag];
		u->IsInHeap=false;
		for(int i=0;i<g._verCount;++i)
		{
			Vertex* v=g._verteies[i];
			if(g._adj[temp->Tag][i]!=INT_MAX&&v->IsInHeap&&g._adj[temp->Tag][i]<v->Key)
			{
				v->Pre=u;
				v->Key=g._adj[temp->Tag][i];
				//这里需要更新堆中的键
				heap.DecreaseKey((HeapNode<int>*)v->Tag,v->Key);
			}
		}
		temp=heap.ExtractMin();
	}
}