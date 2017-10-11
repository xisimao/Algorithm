#include "StdAfx.h"
#include "ElementaryGraphAlgorithms.h"


ElementaryGraphAlgorithms::ElementaryGraphAlgorithms(void)
	:_time(0)
{
}


ElementaryGraphAlgorithms::~ElementaryGraphAlgorithms(void)
{
}

//先从一个结点开始，搜索其所有的邻接点，随后搜索邻接点的邻接点
void ElementaryGraphAlgorithms::BFS(Graph& g,Vertex* vertex)
{
	//初始化顶点
	for (int i=0;i<g._verCount;++i)
	{
		if(g._verteies[i]!=vertex)
		{
			g._verteies[i]->Color=Vertex::White;
			g._verteies[i]->Discover=INT_MAX;
			g._verteies[i]->Pre=NULL;
		}
	}
	//刷新第一个顶点的属性
	vertex->Color=Vertex::Gray;
	vertex->Discover=0;
	vertex->Pre=NULL;
	//用来放置灰色顶点的队列，因为灰色顶点表示它周围可能存在白色结点
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
				//邻接白色顶点置为灰色，并加入队列
				if(white->Color==Vertex::White)
				{
					white->Color=Vertex::Gray;
					white->Discover=gray->Discover+1;
					white->Pre=gray;
					queue.Enqueue(white);
				}
			}

		}
		//对于搜索完所有邻接顶点后置为黑色
		gray->Color=Vertex::Black;
	}
}
//搜索结点能到达的所有点，随后搜索尚未搜索到的结点
void ElementaryGraphAlgorithms::DFS(Graph& g)
{
	if(g._verteies==NULL||g._adj==NULL)
	{
		throw exception("尚未初始化");
	}
	//初始化顶点
	for(int i=0;i<g._verCount;++i)
	{
		if(g._verteies[i]==NULL)
		{
			throw exception("有顶点为空");
		}
		g._verteies[i]->Color=Vertex::White;
		g._verteies[i]->Pre=NULL;
	}
	//初始化时间戳
	_time=0;
	//递归搜索所有白色结点
	for(int i=0;i<g._verCount;++i)
	{
		if(g._verteies[i]->Color==Vertex::White)
		{
			Visit(g,g._verteies[i]);
		}
	}
}
//递归搜索连接的结点
void ElementaryGraphAlgorithms::Visit(Graph& g,Vertex* white)
{
	//增加时间戳
	_time+=1;
	//设置访问的顶点属性
	white->Discover=_time;
	white->Color=Vertex::Gray;
	//递归访问所有邻接的白色顶点
	for(int j=0;j<g._verCount;++j)
	{
		if(g._adj[white->Index][j]!=INT_MAX)
		{
			//邻接白色顶点
			Vertex* adjWhite=g._verteies[j];
			if(adjWhite->Color==Vertex::White)
			{
				adjWhite->Pre=white;
				Visit(g,adjWhite);
			}
		}
	}
	//当全部邻接顶点搜索完成后置为黑色，并设置结束时间戳
	white->Color=Vertex::Black;
	_time+=1;
	white->Finish=_time;
}
//这里需要降序排序，所以取反
int Compare(Vertex* v1,Vertex* v2)
{
	return v2->Finish-v1->Finish;
}
void ElementaryGraphAlgorithms::TopologicalSort(Graph& g)
{
	//深度优先搜索
	DFS(g);

	//根据结束时间戳降序排序，插入排序
	InsertionSort<Vertex*>is;
	is.Sort(g._verteies,g._verCount,Compare);

	//因为顶点在顶点域的序号变了，所以邻接顶点域矩阵也需要变化
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
	//更新每个顶点在顶点域中的序号
	for(int i=0;i<g._verCount;++i)
	{
		g._verteies[i]->Index=i;
	}
}

void ElementaryGraphAlgorithms::StronglyConnectedComponents(Graph& g)
{
	//拓扑排序
	TopologicalSort(g);
	//转置邻接顶点域
	Transpose(g);
	//深度优先搜索
	DFS(g);
	//之后所有前置顶点为空的都是强连通分量的顶点
}

void ElementaryGraphAlgorithms::Transpose(Graph& g)
{
	//创建临时矩阵
	int **temp=new int *[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		temp[i]=new int[g._verCount];
		for(int j=0;j<g._verCount;++j)
		{
			temp[i][j]=g._adj[j][i];
		}
	}
	//删除原矩阵并替换
	for(int i=0;i<g._verCount;++i)
	{
		delete[] g._adj[i];
	}
	delete[] g._adj;
	g._adj=temp;
}

