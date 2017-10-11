#pragma once

/**
 * 点
 */
class Point 
{
public:
	/**
	 * 点在直线的位置
	 */
	enum PointInLine
	{
		Left=0,
		Right=1
	};
	static Point* BasePoint;
	Point()
		:flag(true)
	{
		
	}
	/**
	 * x坐标
	 */
	int X;
	/**
	 * y坐标
	 */
	int Y;
	/**
	 * 点在直线中的相对位置
	 */
	PointInLine Location;
	/**
	 * 用于记录点所在的直线指针
	 */
	void* ParentLine;
	bool flag;
	bool operator == (const Point& right) const
	{
		return X==right.X&&Location==right.Location&&Y==right.Y;
	}
	bool operator != (const Point& right) const
	{
		return !(*this == right);
	}
	/**
	 * 排序的比较方式依次为点的x坐标，左右位置，y坐标
	 * 用于AnySegmentsIntersect方法
	 * @param right 点
	 * @return 小于
	 */
	bool operator < (const Point& right) const
	{
		return X<right.X||(X==right.X&&Location<right.Location)||(X==right.X&&Location==right.Location&&Y<right.Y);
	}
	bool operator > (const Point& right) const
	{
		return right < *this;
	}
	bool operator <= (const Point& right) const
	{
		return !(right < *this);
	}
	bool operator >= (const Point& right) const
	{
		return !(*this < right);
	}
};

