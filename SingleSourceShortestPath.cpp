#include "StdAfx.h"
#include "SingleSourceShortestPath.h"


SingleSourceShortestPath::SingleSourceShortestPath(void)
{
}


SingleSourceShortestPath::~SingleSourceShortestPath(void)
{
}

void SingleSourceShortestPath::Init(Graph& g,Vertex* s)
{
	for(int i=0;i<g._verCount;++i)
	{
		g._verteies[i]->WeightEstimate=INT_MAX;
		g._verteies[i]->Pre=NULL;
	}
	s->WeightEstimate=0;
}

void SingleSourceShortestPath::Relax(Graph& g,Vertex* u,Vertex *v)
{
	if(u->WeightEstimate!=INT_MAX&&v->WeightEstimate>u->WeightEstimate+g._adj[u->Index][v->Index])
	{
		v->WeightEstimate=u->WeightEstimate+g._adj[u->Index][v->Index];
		v->Pre=u;
	}
}
bool SingleSourceShortestPath::BellmanFord(Graph& g,Vertex* s)
{
	Init(g,s);
	//在对每条边进行第1遍松弛的时候，生成了从s出发，层次至多为1的那些树枝
	//也就是说，找到了与s至多有1条边相联的那些顶点的最短路径
	//对每条边进行第2遍松弛的时候，生成了第2层次的树枝，就是说找到了经过2条边相连的那些顶点的最短路径
	//因为最短路径最多只包含|v|-1 条边，所以，只需要循环|v|-1 次
	for(int i=0;i<g._verCount-1;++i)
	{
		for(int j=0;j<g._edgeCount;++j)
		{
			Relax(g,g._edges[j]->Start,g._edges[j]->End);
		}
	}
	//检查是否有环路
	for(int i=0;i<g._edgeCount;++i)
	{
		if(g._edges[i]->End->WeightEstimate>g._edges[i]->Start->WeightEstimate+g._adj[g._edges[i]->Start->Index][g._edges[i]->End->Index])
		{
			//表明存在一个从源结点可以到达的权重为负值的环路
			return false;
		}

	}
	return true;
}

void SingleSourceShortestPath::DagShortestPaths(Graph& g,Vertex* s)
{
	ElementaryGraphAlgorithms el;
	//如果有向无环图包含从结点u到结点v的一条路径，则u在拓扑排序的次序中位于结点v的前面
	el.TopologicalSort(g);
	Init(g,s);
	//对于以邻接链表法表示的图，这个时间为线性级
	//对于Relax只执行了|E|次
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(g._adj[i][j]!=INT_MAX)
			{
				Relax(g,g._verteies[i],g._verteies[j]);
			}
		}
	}
}

void SingleSourceShortestPath::Dijkstra(Graph& g,Vertex* s)
{
	Init(g,s);
	//堆中保存尚未连接到最短路径中的结点
	FibonacciHeap heap;
	for(int i=0;i<g._verCount;++i)
	{
		HeapNode<int>* node=new HeapNode<int>;
		node->Key=g._verteies[i]->WeightEstimate;
		node->Tag=g._verteies[i]->Index;
		g._verteies[i]->Tag=node;
		g._verteies[i]->IsInHeap=true;
		heap.Insert(node);
	}
	//选择最短路径估计最小的结点u，对齐发出的边进行松弛，随后u被认为已经连接到最短路径中
	HeapNode<int>* temp=heap.ExtractMin();
	g._verteies[temp->Tag]->IsInHeap=false;
	while(temp!=NULL)
	{
		g._verteies[temp->Tag]->IsInHeap=false;
		for(int i=0;i<g._verCount;++i)
		{
			if(g._adj[temp->Tag][i]!=INT_MAX)
			{
				Relax(g,g._verteies[temp->Tag],g._verteies[i]);
				if(g._verteies[i]->IsInHeap)
				{
					heap.DecreaseKey((HeapNode<int>*)g._verteies[i]->Tag,g._verteies[i]->WeightEstimate);
				}
			}
		}
		temp=heap.ExtractMin();
	}
}