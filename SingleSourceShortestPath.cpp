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
	//�ڶ�ÿ���߽��е�1���ɳڵ�ʱ�������˴�s�������������Ϊ1����Щ��֦
	//Ҳ����˵���ҵ�����s������1������������Щ��������·��
	//��ÿ���߽��е�2���ɳڵ�ʱ�������˵�2��ε���֦������˵�ҵ��˾���2������������Щ��������·��
	//��Ϊ���·�����ֻ����|v|-1 ���ߣ����ԣ�ֻ��Ҫѭ��|v|-1 ��
	for(int i=0;i<g._verCount-1;++i)
	{
		for(int j=0;j<g._edgeCount;++j)
		{
			Relax(g,g._edges[j]->Start,g._edges[j]->End);
		}
	}
	//����Ƿ��л�·
	for(int i=0;i<g._edgeCount;++i)
	{
		if(g._edges[i]->End->WeightEstimate>g._edges[i]->Start->WeightEstimate+g._adj[g._edges[i]->Start->Index][g._edges[i]->End->Index])
		{
			//��������һ����Դ�����Ե����Ȩ��Ϊ��ֵ�Ļ�·
			return false;
		}

	}
	return true;
}

void SingleSourceShortestPath::DagShortestPaths(Graph& g,Vertex* s)
{
	ElementaryGraphAlgorithms el;
	//��������޻�ͼ�����ӽ��u�����v��һ��·������u����������Ĵ�����λ�ڽ��v��ǰ��
	el.TopologicalSort(g);
	Init(g,s);
	//�������ڽ�������ʾ��ͼ�����ʱ��Ϊ���Լ�
	//����Relaxִֻ����|E|��
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
	//���б�����δ���ӵ����·���еĽ��
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
	//ѡ�����·��������С�Ľ��u�����뷢���ı߽����ɳڣ����u����Ϊ�Ѿ����ӵ����·����
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