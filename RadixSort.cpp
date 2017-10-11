#include "StdAfx.h"
#include "RadixSort.h"



RadixSort::RadixSort(void)
{
}


RadixSort::~RadixSort(void)
{
}

void RadixSort::Sort(int data[],int length)
{
	BuckedSort<int> bs;
	bs.Sort(data,length,RadixSort::GetOneIndex);;
	bs.Sort(data,length,RadixSort::GetTenIndex);
	bs.Sort(data,length,RadixSort::GetHundredIndex);
}

int RadixSort::GetOneIndex(int value)
{
	return value%10;
}
int RadixSort::GetTenIndex(int value)
{
	return value/10%10;
}

int RadixSort::GetHundredIndex(int value)
{
	return value/100%10;
}
