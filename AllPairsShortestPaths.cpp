#include "StdAfx.h"
#include "AllPairsShortestPaths.h"


AllPairsShortestPaths::AllPairsShortestPaths(void)
{
}


AllPairsShortestPaths::~AllPairsShortestPaths(void)
{
}
void AllPairsShortestPaths::Extend(Graph& g,int** current,int** extend,int** next)
{
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			next[i][j]=INT_MAX;
			//每次虽然和n条边进行比较，但是只会留下最短的权重，所以只扩展了一条边
			for(int k=0;k<g._verCount;++k)
			{
				if(current[i][k]!=INT_MAX&&extend[k][j]!=INT_MAX)
				{
					next[i][j]=min(next[i][j],current[i][k]+extend[k][j]);
				}
			}
		}
	}
}
void AllPairsShortestPaths::SlowAllPairs(Graph& g)
{
	//当前计算出的结果
	int** current=new int*[g._verCount];
	//用于保存下次计算出的结果
	int** next=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		current[i]=new int[g._verCount];
		next[i]=new int[g._verCount];
	}
	//L1等于权重矩阵
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(i==j)
			{
				current[i][j]=0;
				//这里为了简单起见，没有再次定义一个扩展边为0的矩阵，而直接用了图中的邻接点域，但是需要设置i等于j时为0
				g._adj[i][j]=0;
			}
			else
			{
				current[i][j]=g._adj[i][j];
			}
		}
	}

	//每次扩展一条边，一共需要扩展到|V|-1条边，初始已经有1条	
	for(int m=1;m<g._verCount-1;++m)
	{
		Extend(g,current,g._adj,next);
		int** temp=next;
		next=current;
		current=temp;
	}
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(current[i][j]==INT_MAX)
			{
				cout<<"∞ ";
			}
			else
			{
				cout<<current[i][j]<<"  ";
			}
		}
		cout<<endl;
	}

	for(int i=0;i<g._verCount;++i)
	{
		delete[] current[i];
		delete[] next[i];
	}
	delete[] current;
	delete[] next;
}
void AllPairsShortestPaths::RepeatSquare(Graph& g)
{
	//当前计算出的结果
	int** current=new int*[g._verCount];
	//用于保存下次计算出的结果
	int** next=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		current[i]=new int[g._verCount];
		next[i]=new int[g._verCount];
		for(int j=0;j<g._verCount;++j)
		{
			current[i][j]=g._adj[i][j];
		}
	}
	//每次扩展2的m次方条边，只适用于2的幂
	for(int m=0;m<g._verCount-2;m+=2)
	{
		Extend(g,current,current,next);
		int** temp=next;
		next=current;
		current=temp;
	}
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			cout<<current[i][j]<<"  ";
		}
		cout<<endl;
	}
	for(int i=0;i<g._verCount;++i)
	{
		delete[] current[i];
		delete[] next[i];
	}
	delete[] current;
	delete[] next;
}

void AllPairsShortestPaths::FloydWarshall(Graph& g)
{
	//dk[i][j]从结点i到结点j的所有中间结点全部取自集合{1-k}的一条最短路径的权重，在数组中对应序号为{0~k-1}
	int** dc=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		dc[i]=new int[g._verCount];
	}
	int** dn=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		dn[i]=new int[g._verCount];
	}
	//前序矩阵，prec[i][j]表示路径i-j中结点j的前驱结点
	int** prec=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		prec[i]=new int[g._verCount];
	}
	int** pren=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		pren[i]=new int[g._verCount];
	}
	//d初始时，从结点i到结点j的路径将没有任何中间结点
	//pre初始化时如果i和j直接相连，则j的前驱结点为i
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			dc[i][j]=g._adj[i][j];
			dn[i][j]=INT_MAX;
			if(i==j||g._adj[i][j]==INT_MAX)
			{
				prec[i][j]=-1;
			}
			else
			{
				prec[i][j]=i;
			}
		}
	}
	//k表示当前尝试的点的序号
	//如果k是最短路径的中间点则最短路径权重为i--k--j
	//当k=0时，对于增加一个中点的情况，比如是i直接连到k，k直接连到j，此时由初始化的dc中给出
	//以此类推而i--k和k--j的权重可以在k-1次循环中可以找到
	//增加n个结点需要n次循环
	for(int k=0;k<g._verCount;++k)
	{
		for(int i=0;i<g._verCount;++i)
		{
			for(int j=0;j<g._verCount;++j)
			{
				int t=0;
				if(dc[i][k]==INT_MAX||dc[k][j]==INT_MAX)
				{
					t=INT_MAX;
				}
				else
				{
					t=dc[i][k]+dc[k][j];
				}
				//表示通过k点作为中间不是最短路径，所以此次循环保持上次结果，前序也不变
				if(dc[i][j]<=t)
				{
					dn[i][j]=dc[i][j];
					pren[i][j]=prec[i][j];
				}
				//当k点为中间结点时，此时对于i-k-j路径中结点j的前驱，应等于k-j中j的前驱结点
				//因为k-j是i-j的子路径，所以j的前驱结点是不变的
				else
				{
					dn[i][j]=t;
					pren[i][j]=prec[k][j];
				}
			}
		}
		int** temp=dc;
		dc=dn;
		dn=temp;

		temp=prec;
		prec=pren;
		pren=temp;
	}

	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(dc[i][j]==INT_MAX)
			{
				cout<<"∞  ";
			}
			else
			{
				cout<<dc[i][j]<<"  ";
			}
		}
		cout<<endl;
	}
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(prec[i][j]==-1)
			{
				cout<<"NIL  ";
			}
			else
			{
				cout<<prec[i][j]<<"  ";
			}
		}
		cout<<endl;
	}
	for(int i=0;i<g._verCount;++i)
	{
		delete[] dc[i];
		delete[] dn[i];
	}
	delete[] dc;
	delete[] dn;
}

void AllPairsShortestPaths::TransitiveClosure(Graph& g)
{
	int** tc=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		tc[i]=new int[g._verCount];
	}
	int** tn=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		tn[i]=new int[g._verCount];
	}
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(i==j||g._adj[i][j]!=INT_MAX)
			{
				tc[i][j]=1;
			}
			else
			{
				tc[i][j]=0;
			}
		}
	}

	for(int k=0;k<g._verCount;++k)
	{
		for(int i=0;i<g._verCount;++i)
		{
			for(int j=0;j<g._verCount;++j)
			{
				//对于i和j是否连接的判断为i-j是否连接或者i-k连接并且j-k是连接的
				tn[i][j]=tc[i][j]|(tc[i][k]&tc[k][j]);
			}
		}
		int** temp=tc;
		tc=tn;
		tn=temp;		
	}

	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			cout<<tc[i][j]<<"  ";
		}
		cout<<endl;
	}
	for(int i=0;i<g._verCount;++i)
	{
		delete[] tc[i];
		delete[] tn[i];
	}
	delete[] tc;
	delete[] tn;
}
//主要思想是将负权重变为正值，随后对于每个结点依次使用Dijkstra算法
void AllPairsShortestPaths::Johnson(Graph& g)
{
	//增加一个结点s，并设置s到任意一个结点权重为0
	//对于s起始的最短路径，如果不存在负权重，则s到每个结点的最短路径为0，否则为负权重值，例如i-j=-1，则s-j=s-i-j=-1
	//设最短路径为每个结点的h值，则有不等式h[i]+w[i][j]>=h[j]
	//当s-i-j为最短路径时不等于取等于，否则取大于，表示s-i的最短路径 + i-j的权重大于s-j的最短路径
	//所以w[i][j]+h[i]-h[j]>=0，就可以利用此式子对权重重新负值保证均为正值

	//增加s结点的临时图
	Vertex** tempVerteies=new Vertex*[g._verCount+1];
	Vertex* s=new Vertex;
	s->Text="s";
	tempVerteies[0]=s;
	for(int i=0;i<g._verCount;++i)
	{
		tempVerteies[i+1]=g._verteies[i];
	}

	Edge** tempEdges=new Edge*[g._edgeCount+g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		Edge* edge=new Edge;
		edge->Start=s;
		edge->End=g._verteies[i];
		edge->Weight=0;
		tempEdges[i]=edge;
	}
	for(int i=0;i<g._edgeCount;++i)
	{
		tempEdges[i+g._verCount]=g._edges[i];
	}

	int tempVerCount=g._verCount+1;
	int tempEdgeCount=g._edgeCount+g._verCount;

	//利用BellmanFord算法，可以算出s到每个结点的最短路径权重，就得到h的值
	Graph graph;
	graph.Init(tempVerteies,tempVerCount,tempEdges,tempEdgeCount);
	SingleSourceShortestPath ss;


	//用于保存对应每个结点的一个值，这个值必须保证满足w[i][j]+h[i]-h[j]>=0
	int* h=new int[tempVerCount];


	if(ss.BellmanFord(graph,s))
	{
		//利用h值得到正值的权重
		for(int i=0;i<tempVerCount;++i)
		{
			h[i]=tempVerteies[i]->WeightEstimate;
		}
		for(int i=0;i<tempEdgeCount;++i)
		{
			tempEdges[i]->Weight=tempEdges[i]->Weight+h[tempEdges[i]->Start->Index]-h[tempEdges[i]->End->Index];
		}
		//这里由于原先g中的顶点序号改变，并且边的权重改变，所以需要重新设置g的顶点和边
		g.Init(&tempVerteies[1],g._verCount,&tempEdges[g._verCount],g._edgeCount);

		//用于保存最短路径的矩阵结果
		int** result=new int*[g._verCount];
		for(int i=0;i<g._verCount;++i)
		{
			result[i]=new int[g._verCount];
		}
		//利用Dijkstra算法，依次对每个结点计算单源最短路径
		for(int i=0;i<g._verCount;++i)
		{
			ss.Dijkstra(g,g._verteies[i]);
			for(int j=0;j<g._verCount;++j)
			{
				//恢复原来的权重
				result[i][j]=g._verteies[j]->WeightEstimate+h[j+1]-h[i+1];
			}
		}
		for(int i=0;i<g._verCount;++i)
		{
			for(int j=0;j<g._verCount;++j)
			{
				cout<<result[i][j]<<"  ";
			}
			cout<<endl;
		}
		for(int i=0;i<g._verCount;++i)
		{
			delete[] result[i];
		}
		delete[] result;
	}
	memset(tempVerteies,0,sizeof(Vertex*));
	delete[] tempVerteies;

	memset(tempEdges,0,sizeof(Edge*));
	delete[] tempEdges;

	delete s;

}