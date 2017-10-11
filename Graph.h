#pragma once
#include <limits.h>
#include "Vertex.h"
#include "Queue_.h"
#include "Edge.h"
#include "InsertionSort.h"

/**
 * ͼ�Ļ�������
 */
class Graph
{
public:
	Graph(void);
	~Graph(void);
	/**
	 * ��ʼ��ͼ
	 * @param verteies ������
	 * @param adj �ڽӵ���
	 * @param count ��������
	 */
	void Init(Vertex* verteies[],int verCount,Edge* edges[],int edgeCount);
	/**
	 * ��ӱ�
	 */
	void AddEdge(Edge* edge);
	/**
	 * ɾ����
	 */
	void RemoveEdge(Edge* edge);
	/**
	 * �߼��ϵ�����
	 */
	int _edgeCount;
	/**
	 * ���㼯�ϵ�����
	 */
	int _verCount;
	/**
	 * �ڽӵ���
	 */
	int** _adj;
	/**
	 * �ڽӵ������ڿ����ҵ���
	 */
	Edge*** _edgeMatrix;
	/**
	 * ���㼯
	 */
	Vertex** _verteies;
	/**
	 * �߼�
	 */
	Edge** _edges;
	
};

