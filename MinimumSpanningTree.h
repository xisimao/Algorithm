#pragma once
#include "Graph.h"
#include "FibonacciHeap.h"
#include "InsertionSort.h"
/**
 * ��С����������
 * һ���� n ��������ͨͼ����������ԭͼ�ļ�С��ͨ��ͼ���Ұ���ԭͼ�е����� n ����㣬�����б���ͼ��ͨ�����ٵı�
 */
class MinimumSpanningTree
{
public:
	MinimumSpanningTree(void);
	~MinimumSpanningTree(void);
	/**
	 *  ��³˹�����㷨��С������
	 * @param g ͼ
	 * @param list ���
	 */
	void Kruskal(Graph& g,Edge* list[]);
	/**
	 * ����ķ�㷨��С������
	 * @param g ͼ
	 * @param v ��ʼ�Ķ���
	 */
	void Prim(Graph& g,Vertex* v);
private:
	/**
	 * ����һ���¼���
	 * @param v ����
	 */
	void MakeSet(Vertex* v);
	/**
	 * ������������
	 * @param x ����1
	 * @param y ����2
	 */
	void Link(Vertex* x,Vertex* y);
	/**
	 * ���ظ����
	 * @param v ����
	 */
	Vertex* FindSet(Vertex* v);
	/**
	 * ���������Ϻϲ�Ϊһ������
	 * @param x ������1
	 * @param x ������2
	 */
	void Union(Vertex* x,Vertex* y);
};

