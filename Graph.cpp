#include "StdAfx.h"
#include "Graph.h"



Graph::Graph(void)
	:_verCount(0),_adj(NULL),_verteies(NULL)
{
}


Graph::~Graph(void)
{
	for(int i=0;i<_verCount;++i)
	{
		_verteies[i]=NULL;
	}
	delete[] _verteies;
	for(int i=0;i<_edgeCount;++i)
	{
		_edges[i]=NULL;
	}
	delete[] _edges;
	for(int i=0;i<_verCount;++i)
	{
		delete[] _adj[i];
		delete[] _edgeMatrix[i];
	}
	delete[] _adj;
	delete[] _edgeMatrix;
}

void Graph::Init(Vertex* verteies[],int verCount,Edge* edges[],int edgeCount)
{
	if(verteies==NULL||edges==NULL)
	{
		throw exception("参数为空");
	}
	_verCount=verCount;
	_edgeCount=edgeCount;
	_verteies=new Vertex*[_verCount];
	_edges=new Edge*[_edgeCount];
	_adj=new int*[_verCount];
	_edgeMatrix=new Edge**[_verCount];

	for(int i=0;i<_verCount;++i)
	{
		_verteies[i]=verteies[i];
		_verteies[i]->Index=i;
	}

	for(int i=0;i<_edgeCount;++i)
	{
		_edges[i]=edges[i];
	}

	for(int i=0;i<_verCount;++i)
	{
		_adj[i]=new int[_verCount];
		_edgeMatrix[i]=new Edge*[_verCount];
		//对于没有连接的结点，权重为∞
		for(int j=0;j<_verCount;++j)
		{
			_adj[i][j]=INT_MAX;
			_edgeMatrix[i][j]=NULL;
		}
	}

	for(int i=0;i<_edgeCount;++i)
	{
		_adj[_edges[i]->Start->Index][_edges[i]->End->Index]=_edges[i]->Weight;
		_edgeMatrix[_edges[i]->Start->Index][_edges[i]->End->Index]=_edges[i];
		_edges[i]->Start->List->AddLast(_edges[i]->End);
	}
}

void Graph::AddEdge(Edge* edge)
{
	Edge** temp=new Edge*[_edgeCount+1];
	for(int i=0;i<_edgeCount;++i)
	{
		temp[i]=_edges[i];
		_edges[i]=NULL;
	}
	temp[_edgeCount]=edge;
	delete[] _edges;
	_adj[edge->Start->Index][edge->End->Index]=edge->Weight;
	_edgeMatrix[edge->Start->Index][edge->End->Index]=edge;
	edge->Start->List->AddLast(edge->End);
	_edges=temp;
	_edgeCount+=1;
}
void Graph::RemoveEdge(Edge* edge)
{
	int index=0;
	for(int i=0;i<_edgeCount;++i)
	{
		if(_edges[i]==edge)
		{
			for(int j=i+1;j<_edgeCount;++j)
			{
				_edges[j-1]=_edges[j];
			}
			_edgeCount-=1;
			_adj[edge->Start->Index][edge->End->Index]=INT_MAX;
			_edgeMatrix[edge->Start->Index][edge->End->Index]=NULL;
			edge->Start->List->Remove(edge->Start->List->Search(edge->End));
			return;
		}
	}

}



