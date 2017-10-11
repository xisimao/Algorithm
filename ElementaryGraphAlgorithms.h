#pragma once
#include "Graph.h"
#include "InsertionSort.h"
/**
 * 基本图算法
 */
class ElementaryGraphAlgorithms
{
public:
	ElementaryGraphAlgorithms(void);
	~ElementaryGraphAlgorithms(void);
	/**
	 * 广度优先搜索
	 * @param g 图
	 * @param vertex 开始顶点
	 */
	void BFS(Graph& g,Vertex* vertex);
	/**
	 * 深度优先搜索
	 * @param g 图
	 */
	void DFS(Graph& g);
	/**
	 * 拓扑排序
	 * @param g 图
	 */
	void TopologicalSort(Graph& g);
	/**
	 * 分解强联通分量
	 * @param g 图
	 */
	void StronglyConnectedComponents(Graph& g);
private:
	/**
	 * 当前深度优先搜索的时间戳
	 */
	int _time;
	/**
	 * 对图进行转置
	 * @param g 图
	 */
	void Transpose(Graph& g);
	/**
	 * 递归搜索邻接顶点
	 * @param g 图
	 * @param white 白色顶点
	 */
	void Visit(Graph& g,Vertex* white);
};

