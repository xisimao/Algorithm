#pragma once
#include "Graph.h"
#include "SingleSourceShortestPath.h"
#include <iostream>
using namespace std;
/**
 * ���н��Ե����·������
 */
class AllPairsShortestPaths
{
public:
	AllPairsShortestPaths(void);
	~AllPairsShortestPaths(void);
	/**
	 * �Ե����ϼ������·��Ȩ��
	 * @param g ͼ
	 */
	void SlowAllPairs(Graph& g);
	/**
	 * �ظ�ƽ�������Ե����ϼ������·��Ȩ��
	 * @param g ͼ
	 */
	void RepeatSquare(Graph& g);
	/**
	 * ���������㷨,����������������·��
	 * @param g ͼ
	 */
	void FloydWarshall(Graph& g);
	/**
	 * �ж϶������н��i��j���Ƿ����һ���ӽ��i�����j��·��
	 * @param g ͼ
	 */
	void TransitiveClosure(Graph& g);
	/**
	 * ����ϡ��ͼ��Լ���㷨,����������������·��
	 * @param g ͼ
	 */
	void Johnson(Graph& g);
private:
	/**
	 * ���������������·����չ����չ����ȸ���w����Ⱦ���
	 * @param g ͼ
	 * @param current ��ǰ�Ѿ�����������·������
	 * @param extend �������������������Ȩ�ؾ����൱��L1��Ҳ�������Ѿ�����������·������
	 * @param next ��������·������
	 */
	void Extend(Graph& g,int** current,int** extend,int** next);
};

