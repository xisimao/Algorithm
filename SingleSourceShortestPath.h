#pragma once
#include "Graph.h"
#include "ElementaryGraphAlgorithms.h"
#include "FibonacciHeap.h"
/**
 * ��Դ���·��
 */
class SingleSourceShortestPath
{
public:
	SingleSourceShortestPath(void);
	~SingleSourceShortestPath(void);
	/**
	 * �����������㷨
	 * �ߵ�Ȩ�ؿ���Ϊ��ֵ�����Դ��ڻ�·�����ǻ�·����Ϊ��ֵ
	 * @param g ͼ
	 * @param s ��ʼ���
	 * @return ����trueֵ���ҽ�������ͼ���������Դ�Դ��㵽���Ȩ��Ϊ��ֵ�Ļ�·
	 */
	bool BellmanFord(Graph& g,Vertex* s);
	/**
	 * �����޻�ͼ��directed acyclic graph���ĵ�Դ���·������
	 * �ߵ�Ȩ�ؿ���Ϊ��ֵ�����Ǳ���û�л�·
	 * @param g ͼ
	 * @param s ��ʼ���
	 */
	void DagShortestPaths(Graph& g,Vertex* s);
	/**
	 * �Ͻ�˹�����㷨
	 * �ߵ�Ȩ�ر���Ϊ��ֵ�����Դ��ڻ�·�����ǻ�·����Ϊ��ֵ
	 * @param g ͼ
	 * @param s ��ʼ���
	 */
	void Dijkstra(Graph& g,Vertex* s);
private:
	/**
	 * ��ʼ�����״̬
	 * @param g ͼ
	 * @param s ��ʼ���
	 */
	void Init(Graph& g,Vertex* s);
	/**
	 * �ɳ�
	 * @param g ͼ
	 * @param u ǰ�ý��
	 * @param v Ҫ�ɳڵĽ�㣬����������СȨ�ع���ֵ
	 */
	void Relax(Graph& g,Vertex* u,Vertex *v);
};

