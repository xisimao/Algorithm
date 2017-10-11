#pragma once
#include "BuckedSort.h"

class RadixSort
{
public:
	RadixSort(void);
	~RadixSort(void);
	void Sort(int[],int length);
	void Test();
private:
	static int GetOneIndex(int value);
	static int GetTenIndex(int value);
	static int GetHundredIndex(int value);
};

