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
			//ÿ����Ȼ��n���߽��бȽϣ�����ֻ��������̵�Ȩ�أ�����ֻ��չ��һ����
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
	//��ǰ������Ľ��
	int** current=new int*[g._verCount];
	//���ڱ����´μ�����Ľ��
	int** next=new int*[g._verCount];
	for(int i=0;i<g._verCount;++i)
	{
		current[i]=new int[g._verCount];
		next[i]=new int[g._verCount];
	}
	//L1����Ȩ�ؾ���
	for(int i=0;i<g._verCount;++i)
	{
		for(int j=0;j<g._verCount;++j)
		{
			if(i==j)
			{
				current[i][j]=0;
				//����Ϊ�˼������û���ٴζ���һ����չ��Ϊ0�ľ��󣬶�ֱ������ͼ�е��ڽӵ��򣬵�����Ҫ����i����jʱΪ0
				g._adj[i][j]=0;
			}
			else
			{
				current[i][j]=g._adj[i][j];
			}
		}
	}

	//ÿ����չһ���ߣ�һ����Ҫ��չ��|V|-1���ߣ���ʼ�Ѿ���1��	
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
				cout<<"�� ";
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
	//��ǰ������Ľ��
	int** current=new int*[g._verCount];
	//���ڱ����´μ�����Ľ��
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
	//ÿ����չ2��m�η����ߣ�ֻ������2����
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
	//dk[i][j]�ӽ��i�����j�������м���ȫ��ȡ�Լ���{1-k}��һ�����·����Ȩ�أ��������ж�Ӧ���Ϊ{0~k-1}
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
	//ǰ�����prec[i][j]��ʾ·��i-j�н��j��ǰ�����
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
	//d��ʼʱ���ӽ��i�����j��·����û���κ��м���
	//pre��ʼ��ʱ���i��jֱ����������j��ǰ�����Ϊi
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
	//k��ʾ��ǰ���Եĵ�����
	//���k�����·�����м�������·��Ȩ��Ϊi--k--j
	//��k=0ʱ����������һ���е�������������iֱ������k��kֱ������j����ʱ�ɳ�ʼ����dc�и���
	//�Դ����ƶ�i--k��k--j��Ȩ�ؿ�����k-1��ѭ���п����ҵ�
	//����n�������Ҫn��ѭ��
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
				//��ʾͨ��k����Ϊ�м䲻�����·�������Դ˴�ѭ�������ϴν����ǰ��Ҳ����
				if(dc[i][j]<=t)
				{
					dn[i][j]=dc[i][j];
					pren[i][j]=prec[i][j];
				}
				//��k��Ϊ�м���ʱ����ʱ����i-k-j·���н��j��ǰ����Ӧ����k-j��j��ǰ�����
				//��Ϊk-j��i-j����·��������j��ǰ������ǲ����
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
				cout<<"��  ";
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
				//����i��j�Ƿ����ӵ��ж�Ϊi-j�Ƿ����ӻ���i-k���Ӳ���j-k�����ӵ�
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
//��Ҫ˼���ǽ���Ȩ�ر�Ϊ��ֵ��������ÿ���������ʹ��Dijkstra�㷨
void AllPairsShortestPaths::Johnson(Graph& g)
{
	//����һ�����s��������s������һ�����Ȩ��Ϊ0
	//����s��ʼ�����·������������ڸ�Ȩ�أ���s��ÿ���������·��Ϊ0������Ϊ��Ȩ��ֵ������i-j=-1����s-j=s-i-j=-1
	//�����·��Ϊÿ������hֵ�����в���ʽh[i]+w[i][j]>=h[j]
	//��s-i-jΪ���·��ʱ������ȡ���ڣ�����ȡ���ڣ���ʾs-i�����·�� + i-j��Ȩ�ش���s-j�����·��
	//����w[i][j]+h[i]-h[j]>=0���Ϳ������ô�ʽ�Ӷ�Ȩ�����¸�ֵ��֤��Ϊ��ֵ

	//����s������ʱͼ
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

	//����BellmanFord�㷨���������s��ÿ���������·��Ȩ�أ��͵õ�h��ֵ
	Graph graph;
	graph.Init(tempVerteies,tempVerCount,tempEdges,tempEdgeCount);
	SingleSourceShortestPath ss;


	//���ڱ����Ӧÿ������һ��ֵ�����ֵ���뱣֤����w[i][j]+h[i]-h[j]>=0
	int* h=new int[tempVerCount];


	if(ss.BellmanFord(graph,s))
	{
		//����hֵ�õ���ֵ��Ȩ��
		for(int i=0;i<tempVerCount;++i)
		{
			h[i]=tempVerteies[i]->WeightEstimate;
		}
		for(int i=0;i<tempEdgeCount;++i)
		{
			tempEdges[i]->Weight=tempEdges[i]->Weight+h[tempEdges[i]->Start->Index]-h[tempEdges[i]->End->Index];
		}
		//��������ԭ��g�еĶ�����Ÿı䣬���ұߵ�Ȩ�ظı䣬������Ҫ��������g�Ķ���ͱ�
		g.Init(&tempVerteies[1],g._verCount,&tempEdges[g._verCount],g._edgeCount);

		//���ڱ������·���ľ�����
		int** result=new int*[g._verCount];
		for(int i=0;i<g._verCount;++i)
		{
			result[i]=new int[g._verCount];
		}
		//����Dijkstra�㷨�����ζ�ÿ�������㵥Դ���·��
		for(int i=0;i<g._verCount;++i)
		{
			ss.Dijkstra(g,g._verteies[i]);
			for(int j=0;j<g._verCount;++j)
			{
				//�ָ�ԭ����Ȩ��
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