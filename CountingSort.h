#pragma once
//计数排序，只适合n个输入元素的每一个都是在0到k区间的一个整数，其中k为某个整数.
class CountingSort
{
public:
	CountingSort(void);
	~CountingSort(void);
	void Sort(int data[],int result[],int length,int max);
};

