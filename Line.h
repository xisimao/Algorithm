#pragma once
#include <string>
#include "Point.h"

using namespace std;
/**
 * 直线
 */
class Line
{
public:
	/**
	 * 扫除线的x坐标
	 */
    static int SwapX;
	/**
	 * 点1
	 */
	Point P1;
	/**
	 * 点2
	 */
	Point P2;
	/**
	 * 直线的标记
	 */
	string Text;

	bool operator == (const Line& right) const
	{
		return P1.X==right.P1.X&&
			   P1.Y==right.P1.Y&&
			   P2.X==right.P2.X&&
			   P2.Y==right.P2.Y;
	}
	bool operator != (const Line& right) const
	{
		return !(*this == right);
	}
	/**
	 * 利用直线在扫除线x坐标位置上y的坐标来比较
	 * @param right 直线
	 * @return 小于
	 */
	bool operator < (const Line& right) const
	{
		/*int s1=abs(P2.X-P1.X);
		int s2=abs(right.P2.X-right.P1.X);
		int t1,t2;
		if(P1.Y>P2.Y)
		{
		t1=P1.Y-abs((Line::TestX-P1.X)/(P2.X-P1.X)*(P1.Y-P2.Y));
		}
		else
		{
		t1=P1.Y+abs((Line::TestX-P1.X)/(P2.X-P1.X)*(P1.Y-P2.Y));
		}
		if(right.P1.Y>right.P2.Y)
		{
		t2=right.P1.Y-abs((Line::TestX-right.P1.X)/(right.P2.X-right.P1.X)*(right.P1.Y-right.P2.Y));
		}
		else
		{
		t2=right.P2.Y+abs((Line::TestX-right.P1.X)/(right.P2.X-right.P1.X)*(right.P1.Y-right.P2.Y));
		}*/

		int t1,t2;
		if(P1.Y>P2.Y)
		{
			t1=abs(P1.Y*(P2.X-P1.X)*(right.P2.X-right.P1.X))-abs((Line::SwapX-P1.X)*(P1.Y-P2.Y)*(right.P2.X-right.P1.X));
		}
		else
		{
			t1=abs(P1.Y*(P2.X-P1.X)*(right.P2.X-right.P1.X))+abs((Line::SwapX-P1.X)*(P1.Y-P2.Y)*(right.P2.X-right.P1.X));
		}
		if(right.P1.Y>right.P2.Y)
		{
			t2=abs(right.P1.Y*(P2.X-P1.X)*(right.P2.X-right.P1.X))-abs((Line::SwapX-right.P1.X)*(right.P1.Y-right.P2.Y)*(P2.X-P1.X));
		}
		else
		{
			t2=abs(right.P1.Y*(P2.X-P1.X)*(right.P2.X-right.P1.X))+abs((Line::SwapX-right.P1.X)*(right.P1.Y-right.P2.Y)*(P2.X-P1.X));
		}
		return t1<t2;
	}
	bool operator > (const Line& right) const
	{
		return right < *this;
	}
	bool operator <= (const Line& right) const
	{
		return !(right < *this);
	}
	bool operator >= (const Line& right) const
	{
		return !(*this < right);
	}
};