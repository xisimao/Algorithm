#pragma once
#include <algorithm>
//LCS
class LongestCommonSubSequence
{
public:
	LongestCommonSubSequence(void);
	~LongestCommonSubSequence(void);
	void LCSLength(char[],int,char[],int);
	void Print(int**,char[],int,int);
};

