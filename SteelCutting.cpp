#include "StdAfx.h"
#include "SteelCutting.h"
#include <stdlib.h> 
#include <math.h>

SteelCutting::SteelCutting(void)
{
	_prices[0]=0;
	_prices[1]=1;
	_prices[2]=5;
	_prices[3]=8;
	_prices[4]=9;
	_prices[5]=10;
	_prices[6]=17;
	_prices[7]=17;
	_prices[8]=20;
	_prices[9]=24;
	_prices[10]=30;

}


SteelCutting::~SteelCutting(void)
{
}
//暴力求解法
int SteelCutting::CutRod(int length)
{
	if(length==0)
	{
		return 0;
	}
	int value=-1;
	for(int i=1;i<length+1;++i)
	{
		value=max(value,_prices[i]+CutRod(length-i));
	}
	return value;
}
//带备忘的自顶向下法
int SteelCutting::MemoizedCutRod(int length)
{
	int values[11];
	for(int i=0;i<11;++i)
	{
		values[i]=-1;
	}
	return MemoizedCutRodAux(length,values);

}
int SteelCutting::MemoizedCutRodAux(int length,int values[])
{
	if(values[length]>=0)
	{
		return values[length];
	}
	int value=0;
	if(length==0)
	{
		value=0;
	}
	else
	{
		value=-1;
		for(int i=1;i<=length;++i)
		{
			value=max(value,_prices[i]+MemoizedCutRodAux(length-i,values));
		}
	}
	values[length]=value;
	return value;
}
//自底向上法
int SteelCutting::BottomUpCutRot(int length)
{
	int values[11];
	for(int i=0;i<11;++i)
	{
		values[i]=-1;
	}
	values[0]=0;
	for(int j=1;j<=length;++j)
	{
		int value=-1;
		for(int i=1;i<=j;++i)
		{
			value=max(value,_prices[i]+values[j-i]);
		}
		values[j]=value;
	}
	return values[length];

}