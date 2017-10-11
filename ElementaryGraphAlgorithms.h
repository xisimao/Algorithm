#pragma once
#include "Graph.h"
#include "InsertionSort.h"
/**
 * ����ͼ�㷨
 */
class ElementaryGraphAlgorithms
{
public:
	ElementaryGraphAlgorithms(void);
	~ElementaryGraphAlgorithms(void);
	/**
	 * �����������
	 * @param g ͼ
	 * @param vertex ��ʼ����
	 */
	void BFS(Graph& g,Vertex* vertex);
	/**
	 * �����������
	 * @param g ͼ
	 */
	void DFS(Graph& g);
	/**
	 * ��������
	 * @param g ͼ
	 */
	void TopologicalSort(Graph& g);
	/**
	 * �ֽ�ǿ��ͨ����
	 * @param g ͼ
	 */
	void StronglyConnectedComponents(Graph& g);
private:
	/**
	 * ��ǰ�������������ʱ���
	 */
	int _time;
	/**
	 * ��ͼ����ת��
	 * @param g ͼ
	 */
	void Transpose(Graph& g);
	/**
	 * �ݹ������ڽӶ���
	 * @param g ͼ
	 * @param white ��ɫ����
	 */
	void Visit(Graph& g,Vertex* white);
};

