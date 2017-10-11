#include "StdAfx.h"
#include "ElementaryGraphAlgorithms.h"


ElementaryGraphAlgorithms::ElementaryGraphAlgorithms(void)
	:_time(0)
{
}


ElementaryGraphAlgorithms::~ElementaryGraphAlgorithms(void)
{
}

//�ȴ�һ����㿪ʼ�����������е��ڽӵ㣬��������ڽӵ���ڽӵ�
void ElementaryGraphAlgorithms::BFS(Graph& g,Vertex* vertex)
{
	//��ʼ������
	for (int i=0;i<g._verCount;++i)
	{
		if(g._verteies[i]!=vertex)
		{
			g._verteies[i]->Color=Vertex::White;
			g._verteies[i]->Discover=INT_MAX;
			g._verteies[i]->Pre=NULL;
		}
	}
	//ˢ�µ�һ�����������
	vertex->Color=Vertex::Gray;
	vertex->Discover=0;
	vertex->Pre=NULL;
	//�������û�ɫ����Ķ��У���Ϊ��ɫ�����ʾ����Χ���ܴ��ڰ�ɫ���
	Queue_<Vertex*> queue;
	queue.Enqueue(vertex);
	while(!queue.Empty())
	{
		Vertex* gray=queue.Dequeue();
		for(int j=0;j<g._verCount;++j)
		{
			if(g._adj[gray->Index][j]!=INT_MAX)
			{
				Vertex* white=g._verteies[j];
				//�ڽӰ�ɫ������Ϊ��ɫ�����������
				if(white->Color==Vertex::White)
				{
					white->Color=Vertex::Gray;
					white->Discover=gray->Discover+1;
					white->Pre=gray;
					queue.Enqueue(white);
				}
			}

		}
		//���������������ڽӶ������Ϊ��ɫ
		gray->Color=Vertex::Black;
	}
}
//��������ܵ�������е㣬���������δ�������Ľ��
void ElementaryGraphAlgorithms::DFS(Graph& g)
{
	if(g._verteies==NULL||g._adj==NULL)
	{
		throw exception("��δ��ʼ��");
	}
	//��ʼ������
	for(int i=0;i<g._verCount;++i)
	{
		if(g._verteies[i]==NULL)
		{
			throw exception("�ж���Ϊ��");
		}
		g._verteies[i]->Color=Vertex::White;
		g._verteies[i]->Pre=NULL;
	}
	//��ʼ��ʱ���
	_time=0;
	//�ݹ��������а�ɫ���
	for(int i=0;i<g._verCount;++i)
	{
		if(g._verteies[i]->Color==Vertex::White)
		{
			Visit(g,g._verteies[i]);
		}
	}
}
//�ݹ��������ӵĽ��
void ElementaryGraphAlgorithms::Visit(Graph& g,Vertex* white)
{
	//����ʱ���
	_time+=1;
	//���÷��ʵĶ�������
	white->Discover=_time;
	white->Color=Vertex::Gray;
	//�ݹ���������ڽӵİ�ɫ����
	for(int j=0;j<g._verCount;++j)
	{
		if(g._adj[white->Index][j]!=INT_MAX)
		{
			//�ڽӰ�ɫ����
			Vertex* adjWhite=g._verteies[j];
			if(adjWhite->Color==Vertex::White)
			{
				adjWhite->Pre=white;
				Visit(g,adjWhite);
			}
		}
	}
	//��ȫ���ڽӶ���������ɺ���Ϊ��ɫ�������ý���ʱ���
	white->Color=Vertex::Black;
	_time+=1;
	white->Finish=_time;
}
//������Ҫ������������ȡ��
int Compare(Vertex* v1,Vertex* v2)
{
	return v2->Finish-v1->Finish;
}
void ElementaryGraphAlgorithms::TopologicalSort(Graph& g)
{
	//�����������
	DFS(g);

	//���ݽ���ʱ����������򣬲�������
	InsertionSort<Vertex*>is;
	is.Sort(g._verteies,g._verCount,Compare);

	//��Ϊ�����ڶ��������ű��ˣ������ڽӶ��������Ҳ��Ҫ�仯
	int **temp=new int *[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		temp[i]=new int[g._verCount];
		for(int j=0;j<g._verCount;++j)
		{
			temp[i][j]=g._adj[g._verteies[i]->Index][g._verteies[j]->Index];
		}
	}
	for(int i=0;i<g._verCount;++i)
	{
		delete[] g._adj[i];
	}
	delete[] g._adj;
	g._adj=temp;
	//����ÿ�������ڶ������е����
	for(int i=0;i<g._verCount;++i)
	{
		g._verteies[i]->Index=i;
	}
}

void ElementaryGraphAlgorithms::StronglyConnectedComponents(Graph& g)
{
	//��������
	TopologicalSort(g);
	//ת���ڽӶ�����
	Transpose(g);
	//�����������
	DFS(g);
	//֮������ǰ�ö���Ϊ�յĶ���ǿ��ͨ�����Ķ���
}

void ElementaryGraphAlgorithms::Transpose(Graph& g)
{
	//������ʱ����
	int **temp=new int *[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		temp[i]=new int[g._verCount];
		for(int j=0;j<g._verCount;++j)
		{
			temp[i][j]=g._adj[j][i];
		}
	}
	//ɾ��ԭ�����滻
	for(int i=0;i<g._verCount;++i)
	{
		delete[] g._adj[i];
	}
	delete[] g._adj;
	g._adj=temp;
}

