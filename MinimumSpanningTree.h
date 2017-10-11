#pragma once
#include "Graph.h"
#include "FibonacciHeap.h"
#include "InsertionSort.h"
/**
 * 最小生成树问题
 * 一个有 n 个结点的连通图的生成树是原图的极小连通子图，且包含原图中的所有 n 个结点，并且有保持图连通的最少的边
 */
class MinimumSpanningTree
{
public:
	MinimumSpanningTree(void);
	~MinimumSpanningTree(void);
	/**
	 *  克鲁斯卡尔算法最小生成树
	 * @param g 图
	 * @param list 结果
	 */
	void Kruskal(Graph& g,Edge* list[]);
	/**
	 * 普里姆算法最小生成树
	 * @param g 图
	 * @param v 开始的顶点
	 */
	void Prim(Graph& g,Vertex* v);
private:
	/**
	 * 建立一个新集合
	 * @param v 顶点
	 */
	void MakeSet(Vertex* v);
	/**
	 * 连接两个顶点
	 * @param x 顶点1
	 * @param y 顶点2
	 */
	void Link(Vertex* x,Vertex* y);
	/**
	 * 返回根结点
	 * @param v 顶点
	 */
	Vertex* FindSet(Vertex* v);
	/**
	 * 将两个集合合并为一个集合
	 * @param x 根顶点1
	 * @param x 根顶点2
	 */
	void Union(Vertex* x,Vertex* y);
};

