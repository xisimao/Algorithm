#pragma once
#include <limits.h>
#include "Vertex.h"
#include "Queue_.h"
#include "Edge.h"
#include "InsertionSort.h"

/**
 * 图的基本操作
 */
class Graph
{
public:
	Graph(void);
	~Graph(void);
	/**
	 * 初始化图
	 * @param verteies 顶点域
	 * @param adj 邻接点域
	 * @param count 顶点数量
	 */
	void Init(Vertex* verteies[],int verCount,Edge* edges[],int edgeCount);
	/**
	 * 添加边
	 */
	void AddEdge(Edge* edge);
	/**
	 * 删除边
	 */
	void RemoveEdge(Edge* edge);
	/**
	 * 边集合的数量
	 */
	int _edgeCount;
	/**
	 * 顶点集合的数量
	 */
	int _verCount;
	/**
	 * 邻接点域
	 */
	int** _adj;
	/**
	 * 邻接点域，用于快速找到边
	 */
	Edge*** _edgeMatrix;
	/**
	 * 顶点集
	 */
	Vertex** _verteies;
	/**
	 * 边集
	 */
	Edge** _edges;
	
};

