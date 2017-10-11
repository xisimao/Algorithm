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
	 * 求两个连接直线的叉积
	 * @param x0 连接点x坐标
	 * @param y0 连接点y坐标
	 * @param x1 直线1x坐标
	 * @param y1 直线1y坐标
	 * @param x2 直线2x坐标
	 * @param y2 直线2y坐标
	 * @return 大于0时直线p0-p1位于直线p0-p2顺时针方向，小于0逆时针方向，为0时两条直线共线
	 */
	int CrossProducts(Point p0,Point p1,Point p2);
	/**
	 * 对于两条共线的直线，其中一条直线的点是否在另一条直线上
	 * @param line 直线
	 * @param p 点
	 * @return 是否共线
	 */
	bool OnSegment(Line line,Point p);
	/**
	 * 两条直线是否相交
	 * @param l1 直线1
	 * @param l2 直线2
	 * @return 是否相交
	 */
	bool SegmentsIntersect(Line l1,Line l2);
	/**
	 * 一组直线中，是否有相交的直线
	 * @param s 直线数组
	 * @param length 数组长度
	 * @return 是否有相交的直线
	 */
	bool AnySegmentsIntersect(Line* s[],int length);	
	void GrahamScan(Point* points[],int length);
};

