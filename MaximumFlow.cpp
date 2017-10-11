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
	//��ʼ����������ֵ
	for(int i=0;i<g._edgeCount;++i)
	{
		g._edges[i]->Flow=0;
	}

	ElementaryGraphAlgorithms ega;
	//��¼��ǰ����ֵ
	int sumFlow=0;
	while(true)
	{
		//�����������
		ega.BFS(g,s);
		//PrintPath(g,s,t);
		//cout<<endl;

		//���Դ��㵽���û��·������ǰ�����������
		if(t->Pre==NULL)
		{
			return sumFlow;
		}
		//��ǰ·���ϸ��߿�ͨ��������С�д�������Ҳ�������·���Ͽ���ͨ�����������ֵ
		int minCapacity=INT_MAX;

		//ѭ���ҳ�minFlow
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

		//ѭ���޸ĸ��ߵĵ�ǰͨ�����Ͳд�����
		temp=t;
		while(temp->Pre!=NULL)
		{
			Edge* edge=g._edgeMatrix[temp->Pre->Index][temp->Index];
			edge->Flow+=minCapacity;
			edge->Capacity-=minCapacity;
			//�����
			Edge* reverseEdge=g._edgeMatrix[temp->Index][temp->Pre->Index];
			//ֻ����edgeΪԭʼ�ߵ�����£�����߿���Ϊ��
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
			//���ԭʼ�ߵĲд�����Ϊ�գ���ȥ���ñ�
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
//���Ͳ������ᴴ���κ���ɱߣ������п��ܵ��±�(u,v)��Ϊ����ɱߣ����������ı�(v,u)��Ϊu.h=v.h+1�����Բ�����ɱ�
void MaximumFlow::Push(Graph& g,Vertex* u,Vertex* v)
{
	Edge* edge=g._edgeMatrix[u->Index][v->Index];
	//�ҵ�����ͨ���ߵ�����
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
	//���������ı䶥��ͱߵ�����
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
//������ǩ�󣬽����ٴ���һ���ӽ��u��������ɱߣ��������ڽ�����u����ɱߣ�ֻ�����������������ǩʱ���ſ��ܳ��ֽ���u����ɱ�
void MaximumFlow::Relabel(Graph& g,Vertex* u)
{
	int min=INT_MAX;
	//�����ڽӵ����С�߶�
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
	//Դ���߶�Ϊ������
	s->Height=g._verCount;
	//������Դ������ӵ����ж��㣬����ǰͨ����������Ϊ���ֵ

	LinkedListNode<Vertex*>* v= s->List->GetFirst();
	while(v!=NULL)
	{
		//������������ͱߵ�����
		Edge* edge=g._edgeMatrix[s->Index][v->Key->Index];
		edge->Flow=edge->Capacity;
		edge->Capacity=0;
		v->Key->ExcessFlow=edge->Flow;
		s->ExcessFlow-=edge->Flow;

		//��ӷ����
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
	//���ڼ�¼��ǰ�����г���������0�Ķ���Ķ���
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
		//��ʾ����u�ĸ߶�С�ڻ���������ڽӶ���
		bool smallOrEqualAll=true;
		//ѭ������uÿ���ڽӶ��㣬�ж��Ƿ������Լ��Ƿ�Ӧ��������ǩ
		LinkedListNode<Vertex*>* v=u->List->GetFirst();
		while(v!=NULL)
		{
			
			//������u�߶ȱ�v�߶ȴ�1����������������
			if(u->Height==v->Key->Height+1)
			{

				Push(g,u,v->Key);
				//�������v�ĳ���������0����ӵ�������
				if(v->Key!=s&&v->Key!=t&&v->Key->ExcessFlow>0)
				{
					queue.Enqueue(v->Key);
				}
				Edge* edge=g._edgeMatrix[u->Index][v->Key->Index];
				//����߲����ڣ�˵������Ϊ0�Ѿ���ɾ��������ɾ���ıߣ���Ҫ������������������ǩ�е�Ӱ��
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
		//��ʾ����u�ĸ߶�С�ڻ���������ڽӶ�����������ǩ
		if(smallOrEqualAll)
		{
			Relabel(g,u);
		}
		//��������һ��ѭ������������ǩ˵�����Ĳд�����Ϊ0������������Ҫ��������ǩ���òд���������
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
		//��Ϊ��ʼ��ʱCurrentΪFirst�����Ե�����v==NULLʱ��˵��û�п������͵Ľ�㣬������Ȼ�г�������������Ҫ����������ǩ
		if(v==NULL)
		{
			Relabel(g,u);
			u->Current=u->List->GetFirst();
		}
		//������
		else if(u->Height==v->Key->Height+1)
		{
			Push(g,u,v->Key);
			u->Current=v->Next;
		}
		//��������ͼ���������Ľ��
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
		//����߶ȸı�˵����u������ǩ�����Կ����дӽ��u��������ɱ�
		//һ�����������������u��u�ĳ������ֽ�����0����u�ִ�����ɱߣ����Կ��Լ���ִ���㷨��������Ҫ��u���뵽������
		if(u->Height>oldHeight)
		{
			queue.Enqueue(u);
		}
	}
	return t->ExcessFlow;
}
