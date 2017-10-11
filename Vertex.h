#pragma once
#include <string>
#include "LinkedList.h"
using namespace std;



/**
 * 图中的顶点
 */
class Vertex
{
public:
	enum VertexColor
	{
		White,
		Gray,
		Black
	};
	Vertex()
		:Discover(0),Finish(0),Color(White),Pre(NULL),Text(""),Index(-1),Rank(0),ExcessFlow(0),Height(0),Current(NULL)
	{
		List=new LinkedList<Vertex*>;
	}
	~Vertex()
	{
		delete List;
	}
	/**
	 * 发现时间
	 */
	int Discover;
	/**
	 * 完成时间
	 */
	int Finish;
	/**
	 * 深度优先搜索时顶点的颜色
	 */
	VertexColor Color;
	/**
	 * 前序顶点
	 */
	Vertex* Pre;
	/**
	 * 描述
	 */
	string Text;
	/** 
	 * 顶点在顶点域中的序号
	 */
	int Index;
	/**
	 * 秩,用于Kruskal算法 
	 */
	int Rank;
	/**
	 * 是否在堆中，用于Prim算法
	 */
	int IsInHeap;
	/**
	 * 表示所有不在当前树中的结点能够连接到树中结点的最小变权重，用于Prim算法
	 */
	int Key;
	/**
	 * 用于保存对应的HeapNode指针，用于Prim算法
	 */
	void* Tag;
	/**
	 * 表示结点到源结点最短路径的估计值，用于单源最短路径算法
	 */
	int WeightEstimate;
	/**
	 * 超额流，最大流算法
	 */
	int ExcessFlow;
	/**
	 * 高度，最大流算法
	 */
	int Height;
	/**
	 * 邻接点链表 
	 */
	LinkedList<Vertex*>* List;
	/**
	 * 当前指向的邻接点，前置推送重贴标签算法
	 */
	LinkedListNode<Vertex*>* Current;
	bool operator == (const Vertex& right) const
	{
		return Index==right.Index;
	}
	bool operator != (const Vertex& right) const
	{
		return !(*this == right);
	}
	bool operator < (const Vertex& right) const
	{
		return Index<right.Index;
	}
	bool operator > (const Vertex& right) const
	{
		return right < *this;
	}
	bool operator <= (const Vertex& right) const
	{
		return !(right < *this);
	}
	bool operator >= (const Vertex& right) const
	{
		return !(*this < right);
	}
};


