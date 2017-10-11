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
	 * ��� 
	 */
	Vertex* Start;
	/**
	 * �յ�
	 */
	Vertex* End;
	/**
	 * Ȩ��
	 */
	int Weight;
	/**
	 * ��ʾ�����Ѿ�ͨ������ֵ��������㷨
	 */
	int Flow;
	/**
	 * ��ʾ���ϲд�����ֵ�����ڱߵ�����ֵ=Flow+Capacity��������㷨
	 */
	int Capacity;
	/**
	 * �жϱ���ͼ��ԭʼ�߻�����������㷨�����ӵıߣ�������㷨
	 * ��������ڶ�ĳЩ�ض����ϵ�������������������ߵ�Flow��Capacity��ԭ�����û������
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

