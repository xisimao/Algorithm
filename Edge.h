#pragma once
#include "Vertex.h"
class Edge
{
public:
	Edge()
		:Start(NULL),End(NULL),Weight(0),Flow(0),Original(true)
	{

	}
	/**
	 * 起点 
	 */
	Vertex* Start;
	/**
	 * 终点
	 */
	Vertex* End;
	/**
	 * 权重
	 */
	int Weight;
	/**
	 * 表示边上已经通过流的值，最大流算法
	 */
	int Flow;
	/**
	 * 表示边上残存容量值，对于边的容量值=Flow+Capacity，最大流算法
	 */
	int Capacity;
	/**
	 * 判断边是图中原始边还是在最大流算法中增加的边，最大流算法
	 * 反向边用于对某些特定边上的流量进行缩减，反向边的Flow和Capacity和原边正好互相调换
	 */
	bool Original;

	bool operator == (const Edge& right) const
	{
		return Weight==right.Weight;
	}
	bool operator != (const Edge& right) const
	{
		return !(*this == right);
	}
	bool operator < (const Edge& right) const
	{
		return Weight<right.Weight;
	}
	bool operator > (const Edge& right) const
	{
		return right < *this;
	}
	bool operator <= (const Edge& right) const
	{
		return !(right < *this);
	}
	bool operator >= (const Edge& right) const
	{
		return !(*this < right);
	}
};

