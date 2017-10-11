#pragma once
#include "stdafx.h"
#include <algorithm>
using namespace std;

class SteelCutting
{
public:
	SteelCutting(void);
	~SteelCutting(void);
	int CutRod(int);
	int MemoizedCutRod(int);
	int BottomUpCutRot(int);

private:
	int _prices[11];
	int MemoizedCutRodAux(int,int[]);
};

