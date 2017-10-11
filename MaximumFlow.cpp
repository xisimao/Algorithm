#include "StdAfx.h"
#include "MaximumFlow.h"


MaximumFlow::MaximumFlow(void)
{
}


MaximumFlow::~MaximumFlow(void)
{
}

int MaximumFlow::EdmondsKarp(Graph& g,Vertex* s,Vertex* t)
{
	//初始化各边流的值
	for(int i=0;i<g._edgeCount;++i)
	{
		g._edges[i]->Flow=0;
	}

	ElementaryGraphAlgorithms ega;
	//记录当前流的值
	int sumFlow=0;
	while(true)
	{
		//广度优先搜索
		ega.BFS(g,s);
		//PrintPath(g,s,t);
		//cout<<endl;

		//如果源结点到汇点没有路径，则当前流就是最大流
		if(t->Pre==NULL)
		{
			return sumFlow;
		}
		//当前路径上各边可通过流的最小残存容量，也就是这边路径上可以通过的流的最大值
		int minCapacity=INT_MAX;

		//循环找出minFlow
		Vertex* temp=t;
		while(temp->Pre!=NULL)
		{
			Edge* edge=g._edgeMatrix[temp->Pre->Index][temp->Index];
			if(edge!=NULL&&edge->Capacity<minCapacity)
			{
				minCapacity=edge->Capacity;
			}
			temp=temp->Pre;
		}
		sumFlow+=minCapacity;

		//循环修改各边的当前通过流和残存容量
		temp=t;
		while(temp->Pre!=NULL)
		{
			Edge* edge=g._edgeMatrix[temp->Pre->Index][temp->Index];
			edge->Flow+=minCapacity;
			edge->Capacity-=minCapacity;
			//反向边
			Edge* reverseEdge=g._edgeMatrix[temp->Index][temp->Pre->Index];
			//只有在edge为原始边的情况下，反向边可能为空
			if(reverseEdge==NULL)
			{
				reverseEdge=new Edge;
				reverseEdge->Start=edge->End;
				reverseEdge->End=edge->Start;
				reverseEdge->Original=false;
				g.AddEdge(reverseEdge);
			}
			reverseEdge->Flow=edge->Capacity;
			reverseEdge->Capacity=edge->Flow;
			//如果原始边的残存流量为空，则去掉该边
			if(edge->Capacity==0)
			{
				g.RemoveEdge(edge);
			}
			temp=temp->Pre;
		}
		
		//for(int i=0;i<g._edgeCount;++i)
		//{
		//	cout<<g._edges[i]->Start->Text<<"-"<<g._edges[i]->End->Text<<"  "<<g._edges[i]->Capacity<<endl;
		//}
		//cout<<endl;
	}

	
}
//推送操作不会创建任何许可边，但是有可能导致边(u,v)成为非许可边，可能新增的边(v,u)因为u.h=v.h+1，所以不是许可边
void MaximumFlow::Push(Graph& g,Vertex* u,Vertex* v)
{
	Edge* edge=g._edgeMatrix[u->Index][v->Index];
	//找到可以通过边的流量
	int flow=min(u->ExcessFlow,edge->Capacity);
	if(flow==0)
	{
		return;
	}
	Edge* reverseEdge=g._edgeMatrix[v->Index][u->Index];
	if(reverseEdge==NULL)
	{
		reverseEdge=new Edge;
		reverseEdge->Start=edge->End;
		reverseEdge->End=edge->Start;
		reverseEdge->Original=false;
		g.AddEdge(reverseEdge);
	}
	//推送流，改变顶点和边的属性
	edge->Flow+=flow;
	edge->Capacity-=flow;
	reverseEdge->Flow=edge->Capacity;
	reverseEdge->Capacity=edge->Flow;
	u->ExcessFlow-=flow;
	v->ExcessFlow+=flow;
	if(edge->Original&&edge->Capacity==0)
	{
		g.RemoveEdge(edge);
	}
	cout<<u->Text<<" push "<<v->Text<<" "<<flow<<endl;

}
//重贴标签后，将至少存在一条从结点u发出的许可边，但不存在进入结点u的许可边，只有在其他结点重贴标签时，才可能出现进入u的许可边
void MaximumFlow::Relabel(Graph& g,Vertex* u)
{
	int min=INT_MAX;
	//查找邻接点的最小高度
	LinkedListNode<Vertex*>* v=u->List->GetFirst();
	while(v!=NULL)
	{
		if(v->Key->Height<min)
		{
			min=v->Key->Height;
		}
		v=v->Next;
	}
	if(min==INT_MAX)
	{
		return;
	}
	u->Height=min+1;
	cout<<u->Text<<" h: "<<u->Height<<endl;
}
void MaximumFlow::InitializePreflow(Graph& g,Vertex* s)
{
	for(int i=0;i<g._verCount;++i)
	{
		g._verteies[i]->Height=0;
		g._verteies[i]->ExcessFlow=0;
	}
	for(int i=0;i<g._edgeCount;++i)
	{
		g._edges[i]->Flow=0;
	}
	//源结点高度为顶点数
	s->Height=g._verCount;
	//所有与源结点连接的所有顶点，将起当前通过的流设置为最大值

	LinkedListNode<Vertex*>* v= s->List->GetFirst();
	while(v!=NULL)
	{
		//设置两个顶点和边的属性
		Edge* edge=g._edgeMatrix[s->Index][v->Key->Index];
		edge->Flow=edge->Capacity;
		edge->Capacity=0;
		v->Key->ExcessFlow=edge->Flow;
		s->ExcessFlow-=edge->Flow;

		//添加反向边
		Edge* temp=new Edge;
		temp->Start=edge->End;
		temp->End=edge->Start;
		temp->Capacity=edge->Flow;
		temp->Flow=0;
		temp->Original=false;
		g.AddEdge(temp);
		v=v->Next;
	}
}
int MaximumFlow::GenericPushRelabel(Graph& g,Vertex* s,Vertex* t)
{
	InitializePreflow(g,s);
	//用于记录当前所有有超额流大于0的顶点的队列
	Queue_<Vertex*> queue;
	for(int i=1;i<g._verCount-1;++i)
	{
		if(g._verteies[i]->ExcessFlow>0)
		{
			queue.Enqueue(g._verteies[i]);
		}
	}
	
	while(!queue.Empty())
	{
		
		Vertex* u=queue.Peek();
		//表示顶点u的高度小于或等于所有邻接顶点
		bool smallOrEqualAll=true;
		//循环顶点u每个邻接顶点，判断是否推送以及是否应该重贴标签
		LinkedListNode<Vertex*>* v=u->List->GetFirst();
		while(v!=NULL)
		{
			
			//当顶点u高度比v高度大1，则满足推送条件
			if(u->Height==v->Key->Height+1)
			{

				Push(g,u,v->Key);
				//如果顶点v的超额流大于0则添加到队列中
				if(v->Key!=s&&v->Key!=t&&v->Key->ExcessFlow>0)
				{
					queue.Enqueue(v->Key);
				}
				Edge* edge=g._edgeMatrix[u->Index][v->Key->Index];
				//如果边不存在，说明容量为0已经被删除，对于删除的边，需要忽略这条边在重贴标签中的影响
				if(edge!=NULL)
				{
					smallOrEqualAll=false;
				}
			}
			else if(u->Height>v->Key->Height)
			{
				smallOrEqualAll=false;
			}
		
			v=v->Next;
		}
		//表示顶点u的高度小于或等于所有邻接顶点则重贴标签
		if(smallOrEqualAll)
		{
			Relabel(g,u);
		}
		//如果结点在一次循环后不能重贴标签说明它的残存容量为0，否则它就需要继续贴标签来让残存容量流走
		else
		{
			u=queue.Dequeue();
		}
	}
	return t->ExcessFlow;
}
void MaximumFlow::Discharge(Graph& g,Vertex* u)
{
	while(u->ExcessFlow>0)
	{
		LinkedListNode<Vertex*>* v=u->Current;
		//因为初始化时Current为First，所以当触发v==NULL时，说明没有可以推送的结点，但是仍然有超额流，所以需要继续重贴标签
		if(v==NULL)
		{
			Relabel(g,u);
			u->Current=u->List->GetFirst();
		}
		//推送流
		else if(u->Height==v->Key->Height+1)
		{
			Push(g,u,v->Key);
			u->Current=v->Next;
		}
		//都不满足就继续检查后面的结点
		else
		{
			u->Current=v->Next;
		}
	}
}

int MaximumFlow::RelabelToFront(Graph& g,Vertex* s,Vertex* t)
{
	InitializePreflow(g,s);
	Queue_<Vertex*> queue;
	for(int i=1;i<g._verCount-1;++i)
	{
		g._verteies[i]->Current=g._verteies[i]->List->GetFirst();
		queue.Enqueue(g._verteies[i]);
	}

	while(!queue.Empty())
	{
		Vertex* u=queue.Dequeue();
		int oldHeight=u->Height;
		Discharge(g,u);
		//如果高度改变说明对u重贴标签，所以可能有从结点u发出的许可边
		//一旦后后续结点的流流入u则u的超额流又将大于0，而u又存在许可边，所以可以继续执行算法，所以需要把u加入到队列中
		if(u->Height>oldHeight)
		{
			queue.Enqueue(u);
		}
	}
	return t->ExcessFlow;
}
