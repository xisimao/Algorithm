#pragma once
#include <limits.h>
//�������˷�
class MatrixChainMultiplication 
{
public:
	MatrixChainMultiplication(void);
	~MatrixChainMultiplication(void);
	void Order(int[],int);
	void MemoizedMatrixChain(int[],int);
	int LookUpChain(int**,int[],int,int);
};

