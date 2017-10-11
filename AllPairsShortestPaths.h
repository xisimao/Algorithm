#pragma once
#include "Graph.h"
#include "SingleSourceShortestPath.h"
#include <iostream>
using namespace std;
/**
 * 所有结点对的最短路径问题
 */
class AllPairsShortestPaths
{
public:
	AllPairsShortestPaths(void);
	~AllPairsShortestPaths(void);
	/**
	 * 自底向上计算最短路径权重
	 * @param g 图
	 */
	void SlowAllPairs(Graph& g);
	/**
	 * 重复平方法，自底向上计算最短路径权重
	 * @param g 图
	 */
	void RepeatSquare(Graph& g);
	/**
	 * 弗洛伊德算法,解决任意两点间的最短路径
	 * @param g 图
	 */
	void FloydWarshall(Graph& g);
	/**
	 * 判断对于所有结点i和j，是否包含一条从结点i到结点j的路径
	 * @param g 图
	 */
	void TransitiveClosure(Graph& g);
	/**
	 * 用于稀疏图的约翰算法,解决任意两点间的最短路径
	 * @param g 图
	 */
	void Johnson(Graph& g);
private:
	/**
	 * 将最近计算出的最短路径扩展，扩展的深度根据w的深度决定
	 * @param g 图
	 * @param current 当前已经计算出的最短路径矩阵
	 * @param extend 输入矩阵，这个矩阵可能是权重矩阵，相当于L1，也可能是已经计算出的最短路径矩阵
	 * @param next 输出的最短路径矩阵
	 */
	void Extend(Graph& g,int** current,int** extend,int** next);
};

