#pragma once
#include "Graph.h"
#include "Queue_.h"
#include "ElementaryGraphAlgorithms.h"
#include <algorithm>
/**
 * 最大流
 */
class MaximumFlow
{
public:
	MaximumFlow(void);
	~MaximumFlow(void);
	/**
	 * 爱德蒙卡普算法，使用广度优先搜索可以从源结点到汇点的路径来计算最大流
	 * @param g 图
	 * @param s 源结点
	 * @param t 汇点
	 * @return 最大流值
	 */
	int EdmondsKarp(Graph& g,Vertex* s,Vertex* t);
	/**
	 * 推送重贴标签算法
	 * @param g 图
	 * @param s 源结点
	 * @param t 汇点
	 * @return 最大流值
	 */
	int GenericPushRelabel(Graph& g,Vertex* s,Vertex* t);
	int RelabelToFront(Graph& g,Vertex* s,Vertex* t);
private:
	void Push(Graph& g,Vertex* u,Vertex* v);
	void Relabel(Graph& g,Vertex* u);
	/**
	 * 初始化预流
	 * @param g 图
	 * @param s 源结点
	 */
	void InitializePreflow(Graph& g,Vertex* s);
	void Discharge(Graph& g,Vertex* u);
};

