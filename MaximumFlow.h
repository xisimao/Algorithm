#pragma once
#include "Graph.h"
#include "Queue_.h"
#include "ElementaryGraphAlgorithms.h"
#include <algorithm>
/**
 * �����
 */
class MaximumFlow
{
public:
	MaximumFlow(void);
	~MaximumFlow(void);
	/**
	 * �����ɿ����㷨��ʹ�ù�������������Դ�Դ��㵽����·�������������
	 * @param g ͼ
	 * @param s Դ���
	 * @param t ���
	 * @return �����ֵ
	 */
	int EdmondsKarp(Graph& g,Vertex* s,Vertex* t);
	/**
	 * ����������ǩ�㷨
	 * @param g ͼ
	 * @param s Դ���
	 * @param t ���
	 * @return �����ֵ
	 */
	int GenericPushRelabel(Graph& g,Vertex* s,Vertex* t);
	int RelabelToFront(Graph& g,Vertex* s,Vertex* t);
private:
	void Push(Graph& g,Vertex* u,Vertex* v);
	void Relabel(Graph& g,Vertex* u);
	/**
	 * ��ʼ��Ԥ��
	 * @param g ͼ
	 * @param s Դ���
	 */
	void InitializePreflow(Graph& g,Vertex* s);
	void Discharge(Graph& g,Vertex* u);
};

