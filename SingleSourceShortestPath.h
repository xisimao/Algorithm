#pragma once
#include "Graph.h"
#include "ElementaryGraphAlgorithms.h"
#include "FibonacciHeap.h"
/**
 * 单源最短路径
 */
class SingleSourceShortestPath
{
public:
	SingleSourceShortestPath(void);
	~SingleSourceShortestPath(void);
	/**
	 * 贝尔曼福特算法
	 * 边的权重可以为负值，可以存在环路，但是环路必须为正值
	 * @param g 图
	 * @param s 开始结点
	 * @return 返回true值当且仅当输入图不包含可以从源结点到达的权重为负值的环路
	 */
	bool BellmanFord(Graph& g,Vertex* s);
	/**
	 * 有向无环图（directed acyclic graph）的单源最短路径问题
	 * 边的权重可以为负值，但是必须没有环路
	 * @param g 图
	 * @param s 开始结点
	 */
	void DagShortestPaths(Graph& g,Vertex* s);
	/**
	 * 迪杰斯特拉算法
	 * 边的权重必须为正值，可以存在环路，但是环路必须为正值
	 * @param g 图
	 * @param s 开始结点
	 */
	void Dijkstra(Graph& g,Vertex* s);
private:
	/**
	 * 初始化结点状态
	 * @param g 图
	 * @param s 开始结点
	 */
	void Init(Graph& g,Vertex* s);
	/**
	 * 松弛
	 * @param g 图
	 * @param u 前置结点
	 * @param v 要松弛的结点，重新设置最小权重估算值
	 */
	void Relax(Graph& g,Vertex* u,Vertex *v);
};

