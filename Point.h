#pragma once

/**
 * ��
 */
class Point 
{
public:
	/**
	 * ����ֱ�ߵ�λ��
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
	 * x����
	 */
	int X;
	/**
	 * y����
	 */
	int Y;
	/**
	 * ����ֱ���е����λ��
	 */
	PointInLine Location;
	/**
	 * ���ڼ�¼�����ڵ�ֱ��ָ��
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
	 * ����ıȽϷ�ʽ����Ϊ���x���꣬����λ�ã�y����
	 * ����AnySegmentsIntersect����
	 * @param right ��
	 * @return С��
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

