#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "Point.h"
#include "Line.h"
#include "RedBlackTree.h"
#include "InsertionSort.h"
#include "Stack_.h"

using namespace std;



class Geometry
{
public:
	Geometry(void);
	~Geometry(void);
	/**
	 * ����������ֱ�ߵĲ��
	 * @param x0 ���ӵ�x����
	 * @param y0 ���ӵ�y����
	 * @param x1 ֱ��1x����
	 * @param y1 ֱ��1y����
	 * @param x2 ֱ��2x����
	 * @param y2 ֱ��2y����
	 * @return ����0ʱֱ��p0-p1λ��ֱ��p0-p2˳ʱ�뷽��С��0��ʱ�뷽��Ϊ0ʱ����ֱ�߹���
	 */
	int CrossProducts(Point p0,Point p1,Point p2);
	/**
	 * �����������ߵ�ֱ�ߣ�����һ��ֱ�ߵĵ��Ƿ�����һ��ֱ����
	 * @param line ֱ��
	 * @param p ��
	 * @return �Ƿ���
	 */
	bool OnSegment(Line line,Point p);
	/**
	 * ����ֱ���Ƿ��ཻ
	 * @param l1 ֱ��1
	 * @param l2 ֱ��2
	 * @return �Ƿ��ཻ
	 */
	bool SegmentsIntersect(Line l1,Line l2);
	/**
	 * һ��ֱ���У��Ƿ����ཻ��ֱ��
	 * @param s ֱ������
	 * @param length ���鳤��
	 * @return �Ƿ����ཻ��ֱ��
	 */
	bool AnySegmentsIntersect(Line* s[],int length);	
	void GrahamScan(Point* points[],int length);
};

