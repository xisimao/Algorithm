#pragma once
#include <string>
#include "LinkedList.h"
using namespace std;



/**
 * ͼ�еĶ���
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
	 * ����ʱ��
	 */
	int Discover;
	/**
	 * ���ʱ��
	 */
	int Finish;
	/**
	 * �����������ʱ�������ɫ
	 */
	VertexColor Color;
	/**
	 * ǰ�򶥵�
	 */
	Vertex* Pre;
	/**
	 * ����
	 */
	string Text;
	/** 
	 * �����ڶ������е����
	 */
	int Index;
	/**
	 * ��,����Kruskal�㷨 
	 */
	int Rank;
	/**
	 * �Ƿ��ڶ��У�����Prim�㷨
	 */
	int IsInHeap;
	/**
	 * ��ʾ���в��ڵ�ǰ���еĽ���ܹ����ӵ����н�����С��Ȩ�أ�����Prim�㷨
	 */
	int Key;
	/**
	 * ���ڱ����Ӧ��HeapNodeָ�룬����Prim�㷨
	 */
	void* Tag;
	/**
	 * ��ʾ��㵽Դ������·���Ĺ���ֵ�����ڵ�Դ���·���㷨
	 */
	int WeightEstimate;
	/**
	 * ��������������㷨
	 */
	int ExcessFlow;
	/**
	 * �߶ȣ�������㷨
	 */
	int Height;
	/**
	 * �ڽӵ����� 
	 */
	LinkedList<Vertex*>* List;
	/**
	 * ��ǰָ����ڽӵ㣬ǰ������������ǩ�㷨
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


